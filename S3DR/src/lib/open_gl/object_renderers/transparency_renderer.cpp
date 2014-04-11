#include "transparency_renderer.hpp"

#include "../techniques/dual_depth_peeling.hpp"
#include "../object_adapters/shell_adapter.hpp"

#include "shaders/include/DDPInitVS.hpp"
#include "shaders/include/DDPInitFS.hpp"

#include "shaders/include/DDPPeelVS.hpp"
#include "shaders/include/DDPPeelFS.hpp"

#include "shaders/include/DDPBlendVS.hpp"
#include "shaders/include/DDPBlendFS.hpp"

#include "shaders/include/DDPFinalVS.hpp"
#include "shaders/include/DDPFinalFS.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <iostream>

TransparencyRenderer::TransparencyRenderer():
	SceneObjectRenderer(),
    init_program(nullptr),
    peel_program(nullptr),
    blend_program(nullptr),
    final_program(nullptr),
    dual_depth_peeling(nullptr)
{
	InitPrograms();
	dual_depth_peeling.reset(new DualDepthPeeling(*this));
}

TransparencyRenderer::~TransparencyRenderer(){

}

void TransparencyRenderer::InitPrograms(){
	{
	std::vector<Shader> shaderList;
    shaderList.push_back(Shader(DDPInitVS_vert, GL_VERTEX_SHADER));
    shaderList.push_back(Shader(DDPInitFS_frag, GL_FRAGMENT_SHADER));

    init_program.reset(new Program(shaderList));
	}
	{
	std::vector<Shader> shaderList;
    shaderList.push_back(Shader(DDPPeelVS_vert, GL_VERTEX_SHADER));
    shaderList.push_back(Shader(DDPPeelFS_frag, GL_FRAGMENT_SHADER));

    peel_program.reset(new Program(shaderList));
	}
	{
	std::vector<Shader> shaderList;
    shaderList.push_back(Shader(DDPBlendVS_vert, GL_VERTEX_SHADER));
    shaderList.push_back(Shader(DDPBlendFS_frag, GL_FRAGMENT_SHADER));

    blend_program.reset(new Program(shaderList));
	}
	{
	std::vector<Shader> shaderList;
    shaderList.push_back(Shader(DDPFinalVS_vert, GL_VERTEX_SHADER));
    shaderList.push_back(Shader(DDPFinalFS_frag, GL_FRAGMENT_SHADER));

    final_program.reset(new Program(shaderList));
	}
}

void TransparencyRenderer::SetModelToClipMatrixPA(const glm::mat4 & model_to_clip_matrix){
	GLuint model_to_world_uniform = program->Uniform("modelToClipMatrix");
	glUniformMatrix4fv(model_to_world_uniform, 1, GL_FALSE, glm::value_ptr(model_to_clip_matrix));
}

void TransparencyRenderer::SetModelToCameraMatrixPA(const glm::mat4 & model_to_camera_matrix){
	GLuint model_to_camera_uniform = program->Uniform("modelToCameraMatrix");
	glUniformMatrix4fv(model_to_camera_uniform, 1, GL_FALSE, glm::value_ptr(model_to_camera_matrix));
}

void TransparencyRenderer::SetNormalModelToCameraMatrixPA(const glm::mat3 & normal_model_to_camera_matrix){
	GLuint normal_model_to_camera_uniform = program->Uniform("normalModelToCameraMatrix");
	glUniformMatrix3fv(normal_model_to_camera_uniform, 1, GL_FALSE, glm::value_ptr(normal_model_to_camera_matrix));
}

void TransparencyRenderer::ActivateProgram(DDPPassType type){
	if(type == DDPPassType::INIT){
		program = init_program;
	}
	else if(type == DDPPassType::PEEL){
		program = peel_program;
	}
	else if(type == DDPPassType::BLEND){
		program = blend_program;
	}
	else if(type == DDPPassType::FINAL){
		program = final_program;
	}

	glUseProgram(program->ProgramObject());
}

void TransparencyRenderer::DeactivateProgram(){
	glUseProgram(0);
}

void TransparencyRenderer::BindTexture(GLenum target, std::string texname, GLuint texid, int texunit)
{
	glActiveTexture(GL_TEXTURE0 + texunit);
	glBindTexture(target, texid);
	
	GLint linked;
	glGetProgramiv(program->ProgramObject(), GL_LINK_STATUS, &linked);
	if (linked != GL_TRUE) {
		std::cerr << "Error: setTextureUnit needs program to be linked." << std::endl;
		exit(1);
	}
	GLint id = glGetUniformLocation(program->ProgramObject(), texname.c_str());
	if (id == -1) {
		std::cerr << "Warning: Invalid texture " << texname << std::endl;
		return;
	}
	glUniform1i(id, texunit);

	glActiveTexture(GL_TEXTURE0);
}

void TransparencyRenderer::SetAlphaPA(float alpha){
	GLuint alpha_uniform = program->Uniform("alpha");
	glUniform1f(alpha_uniform, alpha);
}

void TransparencyRenderer::AttachShellAdapter(ShellAdapter * shell_adapter){
	int priority = shell_adapter->GetPriority();
	shell_adapters[priority].push_back(shell_adapter);
}

void TransparencyRenderer::Reset(){
	shell_adapters[0].clear();
	shell_adapters[1].clear();
	shell_adapters[2].clear();
}

void TransparencyRenderer::SetWidthHeight(int width, int height){
	dual_depth_peeling->SetWidthHeight(width, height);
}

void TransparencyRenderer::SetBackgroundColor(const glm::vec4 & background_color){
	dual_depth_peeling->SetBackgroundColor(background_color);
}

void TransparencyRenderer::Render(const glm::mat4 & view, const glm::mat4 & projection,  int priority){
	if(shell_adapters[priority].size() == 0){
		return;
	}
	
 	glm::mat4 world_to_clip = projection * view;
	for(auto shell_adapter: shell_adapters[priority]){
		glm::mat4 model_to_clip_matrix = world_to_clip * shell_adapter->GetModelMatrix();
		glm::mat4 model_to_camera_matrix = view * shell_adapter->GetModelMatrix();
		ActivateProgram(DDPPassType::INIT);
		SetModelToClipMatrixPA(model_to_clip_matrix);
		DeactivateProgram();

		ActivateProgram(DDPPassType::PEEL);
		SetModelToClipMatrixPA(model_to_clip_matrix);
		SetModelToCameraMatrixPA(model_to_camera_matrix);
		glm::mat3 normMatrix(model_to_camera_matrix);
		normMatrix = glm::transpose(glm::inverse(normMatrix));
		SetNormalModelToCameraMatrixPA(normMatrix);
		SetAlphaPA(0.8);
		DeactivateProgram();

		dual_depth_peeling->Render(std::bind(&ShellAdapter::Render, shell_adapter));
	}
}