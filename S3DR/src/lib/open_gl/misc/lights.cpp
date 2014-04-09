#include "lights.hpp"

Lights::Lights(){
	lights_block.ambient_intensity = glm::vec4(0.2, 0.2, 0.2, 1);
	lights_block.attenuation = 0.01;
	lights_block.number_of_lights = 0;
}
        
Lights::~Lights(){

}

const LightsBlock & Lights::LightsBlockRef(){
	return lights_block;
}

const LightsBlock & Lights::LightsBlockInCameraSpace(const glm::mat4 & view_matrix){
	LightsBlock camera_space_lights_block =  lights_block;

	for(int i=0; i<lights_block.number_of_lights; ++i){
		glm::vec4 camera_light_pos = view_matrix * glm::vec4(glm::vec3(lights_block.lights[i].light_pos), 1.0);
		camera_light_pos[3] = 1.0;
		camera_space_lights_block.lights[i].light_pos = camera_light_pos;
			
	}

	return camera_space_lights_block;
}

bool Lights::PushLightToScene(const Light & light){
	if(lights_block.number_of_lights < MAX_NUMBER_OF_LIGHTS){
		lights_block.lights[lights_block.number_of_lights++] = light;
		return true;
	}
	return false;
}

bool Lights::PopLightFromScene(Light & light){
	if(lights_block.number_of_lights>0){
		light = lights_block.lights[lights_block.number_of_lights--];
		return true;
	}
	return false;
}