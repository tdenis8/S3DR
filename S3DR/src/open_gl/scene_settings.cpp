#include "scene_settings.hpp"

#include <GL/glew.h>

SceneSettings::SceneSettings():
	Subject(),
	width(-1),
	height(-1),
	background_color(glm::vec3(0,0,0))
{
	Light light1{glm::vec4(0,10,10,1), 	 glm::vec4(1.0,1.0,1.0,1.0)};
	Light light2{glm::vec4(0,-10,-10,1), glm::vec4(1.0,1.0,1.0,1.0)};
	PushLightToScene(light1);
	PushLightToScene(light2);
}

SceneSettings::~SceneSettings(){

}

void SceneSettings::SetWidthHeight(int width, int height){
	this->width = width;
	this->height = height;
	glViewport(0, 0, (GLsizei) width, (GLsizei) height);
	Emit(SceneSettingsEvents::WIDTH_HEIGHT_CHANGED);
}

int SceneSettings::Width(){
	return width;
}

int SceneSettings::Height(){
	return height;
}

void SceneSettings::SetBackgroundColor(const glm::vec3 & color){
	background_color = color;
	glClearColor(background_color.x, background_color.y, background_color.z, 0.0f);
	Emit(SceneSettingsEvents::BACKGROUND_COLOR_CHANGED);
}

const glm::vec3 & SceneSettings::BackgroundColor(){
	return background_color;
}

bool SceneSettings::PushLightToScene(const Light & light){
	bool rv = lights.PushLightToScene(light);
	Emit(SceneSettingsEvents::LIGHTS_CHANGED);
	return rv;
}

const LightsBlock & SceneSettings::LightsBlockInCameraSpace(const glm::mat4 & view_matrix){
	return lights.LightsBlockInCameraSpace(view_matrix);
}
