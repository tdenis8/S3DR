#include "texture_shell_renderer.hpp"

#include "../object_adapters/texture_shell_adapter.hpp"

#include "shaders/include/texture_shell_object_VS.hpp"
#include "shaders/include/texture_shell_object_FS.hpp"

#include <glm/gtc/type_ptr.hpp>

TextureShellRenderer::TextureShellRenderer():
	SceneObjectRenderer()
{
	InitProgram();
}

TextureShellRenderer::~TextureShellRenderer(){

}

void TextureShellRenderer::InitProgram() {
	std::vector<Shader> shaderList;
    shaderList.push_back(Shader(texture_shell_object_VS_vert, GL_VERTEX_SHADER));
    shaderList.push_back(Shader(texture_shell_object_FS_frag, GL_FRAGMENT_SHADER));
    program.reset(new Program(shaderList));
}

void TextureShellRenderer::SetModelToCameraMatrixPA(const glm::mat4 & model_to_camera_matrix){
	GLuint model_to_camera_uniform = program->Uniform("modelToCameraMatrix");
	glUniformMatrix4fv(model_to_camera_uniform, 1, GL_FALSE, glm::value_ptr(model_to_camera_matrix));
}

void TextureShellRenderer::SetCameraToClipMatrixPA(const glm::mat4 & camera_to_clip){
	GLuint camera_to_clip_uiform = program->Uniform("cameraToClipMatrix");
	glUniformMatrix4fv(camera_to_clip_uiform, 1, GL_FALSE, glm::value_ptr(camera_to_clip));
}

void TextureShellRenderer::SetNormalModelToCameraMatrixPA(const glm::mat3 & normal_model_to_camera_matrix){
	GLuint normal_model_to_camera_uniform = program->Uniform("normalModelToCameraMatrix");
	glUniformMatrix3fv(normal_model_to_camera_uniform, 1, GL_FALSE, glm::value_ptr(normal_model_to_camera_matrix));
}

void TextureShellRenderer::AttachTextureShellAdapter(TextureShellAdapter * texture_shell_adapter){
	int priority = texture_shell_adapter->Priority();
	texture_shell_adapters[priority].push_back(texture_shell_adapter);
}

void TextureShellRenderer::DetachTextureShellAdapter(TextureShellAdapter * texture_shell_adapter){
	int priority = texture_shell_adapter->Priority();
	for(auto it=texture_shell_adapters[priority].begin(); it!=texture_shell_adapters[priority].end(); it++){
		if((*it)->Key() == texture_shell_adapter->Key()){
			texture_shell_adapters[priority].erase(it);
			break;
		}
	}
}

void TextureShellRenderer::Reset(){
	texture_shell_adapters[0].clear();
	texture_shell_adapters[1].clear();
	texture_shell_adapters[2].clear();
}

void TextureShellRenderer::Render(const glm::mat4 & view, const glm::mat4 & projection, int priority){
	if(texture_shell_adapters[priority].size() == 0){
		return;
	}
 	ActivateProgram();
 	SetCameraToClipMatrixPA(projection);
	for(auto texture_shell_adapter: texture_shell_adapters[priority]){
		glm::mat4 model_to_camera_matrix = view * texture_shell_adapter->ModelMatrixRef();
		SetModelToCameraMatrixPA(model_to_camera_matrix);
		glm::mat3 normMatrix(view*texture_shell_adapter->ModelMatrixRef());
		normMatrix = glm::transpose(glm::inverse(normMatrix));
		SetNormalModelToCameraMatrixPA(normMatrix);
		texture_shell_adapter->Render();
	}
	DeactivateProgram();
}
