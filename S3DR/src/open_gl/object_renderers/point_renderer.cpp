#include "point_renderer.hpp"

#include "../object_adapters/point_adapter.hpp"

#include "shaders/include/point_object_VS.hpp"
#include "shaders/include/point_object_FS.hpp"

#include <glm/gtc/type_ptr.hpp>

PointRenderer::PointRenderer():
	SceneObjectRenderer()
{
	InitProgram();
}

PointRenderer::~PointRenderer(){

}

void PointRenderer::InitProgram() {
	std::vector<Shader> shaderList;
    shaderList.push_back(Shader(point_object_VS_vert, GL_VERTEX_SHADER));
    shaderList.push_back(Shader(point_object_FS_frag, GL_FRAGMENT_SHADER));
    program.reset(new Program(shaderList));
}

void PointRenderer::SetModelToClipMatrixPA(const glm::mat4 & model_to_clip_matrix){
	GLuint model_to_clip_uniform = program->Uniform("modelToClipMatrix");
	glUniformMatrix4fv(model_to_clip_uniform, 1, GL_FALSE, glm::value_ptr(model_to_clip_matrix));
}

void PointRenderer::AttachPointAdapter(PointAdapter * point_adapter){
	int priority = point_adapter->Priority();
	point_adapters[priority].push_back(point_adapter);
}

void PointRenderer::DetachPointAdapter(PointAdapter * point_adapter){
	int priority = point_adapter->Priority();
	for(auto it=point_adapters[priority].begin(); it!=point_adapters[priority].end(); it++){
		if((*it)->Key() == point_adapter->Key()){
			point_adapters[priority].erase(it);
			break;
		}
	}
}

void PointRenderer::Reset(){
	point_adapters[0].clear();
	point_adapters[1].clear();
	point_adapters[2].clear();
}

void PointRenderer::Render(const glm::mat4 & view, const glm::mat4 & projection, int priority){
	if(point_adapters[priority].size() == 0){
		return;
	}

 	ActivateProgram();
 	glm::mat4 world_to_clip = projection * view;
	for(auto point_adapter: point_adapters[priority]){
		SetModelToClipMatrixPA(world_to_clip * point_adapter->ModelMatrixRef());
		point_adapter->Render();
	}
	DeactivateProgram();
}
