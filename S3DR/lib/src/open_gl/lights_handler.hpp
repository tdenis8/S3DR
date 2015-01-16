#ifndef _LIGHTS_HANDLER_H_
#define _LIGHTS_HANDLER_H_

#include "view/light.hpp"

#include "scene_renderer.hpp"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <vector>

class Camera;

#define NUM_POINT_LIGHTS 6

// In shader we use vec3, in hire we use vec4 for padding (std140)
struct DirectionalLight
{
    glm::vec3 direction;
    float padding_after_direction;
    glm::vec3 ambient;
    float padding_after_ambient;
    glm::vec3 diffuse;
    float padding_after_diffuse;
    glm::vec3 specular;
};

struct PointLight
{
    glm::vec3 position;
    float padding_after_position;
    glm::vec3 ambient;
    float padding_after_ambient;
    glm::vec3 diffuse;
    float padding_after_diffuse;
    glm::vec3 specular;

    float constant = 1.0;
    float linear = 0.009;
    float quadratic = 0.0032;
    float padding_after_linear_quadratic[2];
};

class LightsHandler : Observer
{
    public:
    LightsHandler(SceneRenderer &scene_renderer, Camera &camera);
    ~LightsHandler();
    LightsHandler(const LightsHandler &) = delete;
    LightsHandler &operator=(const LightsHandler &) = delete;

    void AttachLightObject(Light *light_object);
    void DetachLightObject(Light *light_object);

    void Reset();

    private:
    void ViewChanged(const EventInfo &info);

    void InitUBOs();
    void ConnectUBOsAndPrograms();

    void UpdateDirectionalLightBlock();
    void UpdatePointLightsBlock();
    void UpdateCameraPositionInWorld(const glm::vec3 &cam_pos);

    SceneRenderer &scene_renderer_;
    Camera &camera_;

    GLuint directional_light_ubo_;
    DirectionalLight directional_light_;

    GLuint point_lights_ubo_;
    PointLight point_lights_[NUM_POINT_LIGHTS];

    std::vector<Light *> light_objects_;
};

#endif