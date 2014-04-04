#include "line_renderer.hpp"

#include "../object_adapters/line_adapter.hpp"

#include "shaders/include/line_object_VS.hpp"
#include "shaders/include/line_object_FS.hpp"

#include <glm/gtc/type_ptr.hpp>

LineRenderer::LineRenderer():
	SceneObjectRenderer()
{
	InitProgram();
}

LineRenderer::~LineRenderer(){

}

void LineRenderer::InitProgram() {
	std::vector<Shader> shaderList;
    shaderList.push_back(Shader(line_object_VS_vert, GL_VERTEX_SHADER));
    shaderList.push_back(Shader(line_object_FS_frag, GL_FRAGMENT_SHADER));
    program.reset(new Program(shaderList));
}

void LineRenderer::SetModelToClipMatrixPA(const glm::mat4 & model_to_clip_matrix){
	GLuint model_to_clip_uniform = program->Uniform("modelToClipMatrix");
	glUniformMatrix4fv(model_to_clip_uniform, 1, GL_FALSE, glm::value_ptr(model_to_clip_matrix));
}

void LineRenderer::AttachLineAdapter(LineAdapter * line_adapter){
	int priority = line_adapter->Priority();
	line_adapters[priority].push_back(line_adapter);
}

void LineRenderer::DetachLineAdapter(LineAdapter * line_adapter){
	int priority = line_adapter->Priority();
	for(auto it=line_adapters[priority].begin(); it!=line_adapters[priority].end(); it++){
		if((*it)->Key() == line_adapter->Key()){
			line_adapters[priority].erase(it);
			break;
		}
	}
}

void LineRenderer::Reset(){
	line_adapters[0].clear();
	line_adapters[1].clear();
	line_adapters[2].clear();
}

void LineRenderer::Render(const glm::mat4 & view, const glm::mat4 & projection, int priority){
	if(line_adapters[priority].size() == 0){
		return;
	}

 	ActivateProgram();
 	glm::mat4 world_to_clip = projection * view;
	for(auto line_adapter: line_adapters[priority]){
		SetModelToClipMatrixPA(world_to_clip * line_adapter->ModelMatrixRef());
		line_adapter->Render();
	}
	DeactivateProgram();
}
