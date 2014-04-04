#ifndef _LIGHTS_H_
#define _LIGHTS_H_

#include <glm/glm.hpp>

#define MAX_NUMBER_OF_LIGHTS 8

struct Light {
    glm::vec4 light_pos;
    glm::vec4 light_intensity;
};

struct LightsBlock {
    glm::vec4 ambient_intensity;
    float attenuation;
    unsigned int number_of_lights;
    float padding[2];
    Light lights[MAX_NUMBER_OF_LIGHTS];
};

class Lights { 
    public:
		Lights();
        ~Lights();
        Lights(const Lights &)=delete;
        Lights & operator=(const Lights &)=delete;
    
        const LightsBlock & LightsBlockRef();
        const LightsBlock & LightsBlockInCameraSpace(const glm::mat4 & view_matrix);

        bool PushLightToScene(const Light & light);
        bool PopLightFromScene(Light & light);

    private:
        LightsBlock lights_block;

};
    
#endif