#include "text_renderer.hpp"

#include "../object_adapters/text_adapter.hpp"

#include "shaders/include/line_object_VS.hpp"
#include "shaders/include/line_object_FS.hpp"

#include <glm/gtc/type_ptr.hpp>

TextRenderer::TextRenderer():
	SceneObjectRenderer()
{
	InitProgram();
}

TextRenderer::~TextRenderer(){

}

void TextRenderer::InitProgram() {
	std::vector<Shader> shaderList;
    shaderList.push_back(Shader(line_object_VS_vert, GL_VERTEX_SHADER));
    shaderList.push_back(Shader(line_object_FS_frag, GL_FRAGMENT_SHADER));
    program.reset(new Program(shaderList));
}

void TextRenderer::SetModelToClipMatrixPA(const glm::mat4 & model_to_clip_matrix){
	GLuint model_to_clip_uniform = program->Uniform("modelToClipMatrix");
	glUniformMatrix4fv(model_to_clip_uniform, 1, GL_FALSE, glm::value_ptr(model_to_clip_matrix));
}

void TextRenderer::AttachTextAdapter(TextAdapter * text_adapter){
	int priority = text_adapter->GetPriority();
	text_adapters[priority].push_back(text_adapter);
}

void TextRenderer::DetachTextAdapter(TextAdapter * text_adapter){
	int priority = text_adapter->GetPriority();
	for(auto it=text_adapters[priority].begin(); it!=text_adapters[priority].end(); it++){
		if((*it)->GetKey() == text_adapter->GetKey()){
			text_adapters[priority].erase(it);
			break;
		}
	}
}

void TextRenderer::Reset(){
	text_adapters[0].clear();
	text_adapters[1].clear();
	text_adapters[2].clear();
}

void TextRenderer::Render(const glm::mat4 & view, const glm::mat4 & projection, int priority){
	if(text_adapters[priority].size() == 0){
		return;
	}

 	ActivateProgram();
 	glm::mat4 world_to_clip = projection * view;
	for(auto text_adapter: text_adapters[priority]){
		SetModelToClipMatrixPA(world_to_clip * text_adapter->GetModelMatrix());
		text_adapter->Render();
	}
	DeactivateProgram();
}
