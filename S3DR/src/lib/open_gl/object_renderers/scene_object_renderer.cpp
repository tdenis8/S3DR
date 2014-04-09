#include "scene_object_renderer.hpp"

#include <glm/gtc/type_ptr.hpp>

SceneObjectRenderer::SceneObjectRenderer():
	program(nullptr)
{

}

SceneObjectRenderer::~SceneObjectRenderer(){
	
}

void SceneObjectRenderer::ActivateProgram(){
	glUseProgram(program->ProgramObject());
}

void SceneObjectRenderer::DeactivateProgram(){
	glUseProgram(0);
}

Program & SceneObjectRenderer::ProgramRef(){
	return *program;
}
