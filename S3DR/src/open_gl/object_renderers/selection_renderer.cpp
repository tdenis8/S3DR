#include "selection_renderer.hpp"

#include "../object_adapters/scene_object_adapter.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <functional>

#include "shaders/include/selection_VS.hpp"
#include "shaders/include/selection_FS.hpp"

SelectionRenderer::SelectionRenderer():
	SceneObjectRenderer()
{
	InitProgram();
}

SelectionRenderer::~SelectionRenderer(){
	
}

void SelectionRenderer::InitProgram() {
	std::vector<Shader> shaderList;
    shaderList.push_back(Shader(selection_VS_vert, GL_VERTEX_SHADER));
    shaderList.push_back(Shader(selection_FS_frag, GL_FRAGMENT_SHADER));
    program.reset(new Program(shaderList));
}

void SelectionRenderer::SetModelToClipMatrixPA(const glm::mat4 & model_to_clip_matrix){
	GLuint model_to_world_uniform = program->Uniform("modelToClipMatrix");
	glUniformMatrix4fv(model_to_world_uniform, 1, GL_FALSE, glm::value_ptr(model_to_clip_matrix));
}

void SelectionRenderer::SetSceneObjectKeyPA(int scene_object_key){
	GLuint segment_index_uniform = program->Uniform("SceneObjectKey");
	glUniform1ui(segment_index_uniform, scene_object_key);
}

void SelectionRenderer::SetEntryIndexPA(int entry_index){
	GLuint draw_index_uniform = program->Uniform("EntryIndex");
	glUniform1ui(draw_index_uniform, entry_index);
}

void SelectionRenderer::AttachSceneObjectAdapter(SceneObjectAdapter * scene_object_adapter){
	int priority = scene_object_adapter->Priority();
	scene_object_adapters[priority].push_back(scene_object_adapter);
} 

void SelectionRenderer::DetachSceneObjectAdapter(SceneObjectAdapter * scene_object_adapter){
	int priority = scene_object_adapter->Priority();
	for(auto it=scene_object_adapters[priority].begin(); it!=scene_object_adapters[priority].end(); it++){
		if((*it)->Key() == scene_object_adapter->Key()){
			scene_object_adapters[priority].erase(it);
			break;
		}
	}
}

void SelectionRenderer::Reset(){
	scene_object_adapters[0].clear();
	scene_object_adapters[1].clear();
	scene_object_adapters[2].clear();
}

void SelectionRenderer::Render(const glm::mat4 & view, const glm::mat4 & projection, int priority){    
	if(scene_object_adapters[priority].size() == 0){
		return;
	}
	                  
	std::function<void(int)> set_scene_object_key = std::bind(&SelectionRenderer::SetSceneObjectKeyPA, this, std::placeholders::_1);
	std::function<void(int)> set_entry_index = std::bind(&SelectionRenderer::SetEntryIndexPA, this, std::placeholders::_1);
	
	glm::mat4 world_to_clip = projection * view;
 	ActivateProgram();
	for(auto scene_object_adapter: scene_object_adapters[priority]){
		SetModelToClipMatrixPA(world_to_clip * scene_object_adapter->ModelMatrixRef());
		scene_object_adapter->SelectionRender(set_scene_object_key, set_entry_index);
	}
	DeactivateProgram();
}