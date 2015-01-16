#include "lights_handler.hpp"

#include "view/camera.hpp"

#include <iostream>
LightsHandler::LightsHandler(SceneRenderer &scene_renderer, Camera &camera)
    : Observer(), scene_renderer_(scene_renderer), camera_(camera)
{
    InitUBOs();
    ConnectUBOsAndPrograms();
    UpdateDirectionalLightBlock();
    UpdatePointLightsBlock();

    camera_.Observe(
        CameraEvents::VIEW_CHANGED, std::bind(&LightsHandler::ViewChanged, this, std::placeholders::_1), this);

    // To init
    ViewChanged(EventInfo());
}

LightsHandler::~LightsHandler()
{
    camera_.RemoveObservers(this);
}

void LightsHandler::ViewChanged(const EventInfo &info)
{
    UpdateCameraPositionInWorld(camera_.GetCameraPositionInWorld());
}

void LightsHandler::InitUBOs()
{
    // Directional light UBO
    glGenBuffers(1, &directional_light_ubo_);
    glBindBuffer(GL_UNIFORM_BUFFER, directional_light_ubo_);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(DirectionalLight), NULL, GL_STREAM_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, directional_light_ubo_);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    // Point lights UBO
    glGenBuffers(1, &point_lights_ubo_);
    glBindBuffer(GL_UNIFORM_BUFFER, point_lights_ubo_);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(PointLight) * NUM_POINT_LIGHTS, NULL, GL_STREAM_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 1, point_lights_ubo_);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void LightsHandler::ConnectUBOsAndPrograms()
{
    Program &material_shell_renderer_program = scene_renderer_.GetMaterialShellRenderer().GetProgram();

    {
        GLuint unifomr_block_index = material_shell_renderer_program.GetUniformBlock("DirectionalLightBlock");
        glUniformBlockBinding(material_shell_renderer_program.ProgramObject(), unifomr_block_index, 0);
    }
    {
        GLuint unifomr_block_index = material_shell_renderer_program.GetUniformBlock("PointLightsBlock");
        glUniformBlockBinding(material_shell_renderer_program.ProgramObject(), unifomr_block_index, 1);
    }
}

void LightsHandler::UpdateDirectionalLightBlock()
{
    directional_light_.direction = glm::vec3(1, 1, 1);
    directional_light_.ambient = glm::vec3(0.1, 0.2, 0.2);
    directional_light_.diffuse = glm::vec3(1, 1, 1);
    directional_light_.specular = glm::vec3(0.3, 0.3, 0.3);

    glBindBuffer(GL_UNIFORM_BUFFER, directional_light_ubo_);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(directional_light_), &directional_light_);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void LightsHandler::UpdatePointLightsBlock()
{
    point_lights_[0].position = glm::vec3(5, 5, 5);
    point_lights_[0].ambient = glm::vec3(0.2, 0.2, 0.2);
    point_lights_[0].diffuse = glm::vec3(1, 1, 1);
    point_lights_[0].specular = glm::vec3(0.3, 0.3, 0.3);

    point_lights_[1].position = glm::vec3(-10, -6, 5);
    point_lights_[1].ambient = glm::vec3(0.3, 0.3, 0.3);
    point_lights_[1].diffuse = glm::vec3(1, 1, 1);
    point_lights_[1].specular = glm::vec3(0.4, 0.4, 0.4);

    glBindBuffer(GL_UNIFORM_BUFFER, point_lights_ubo_);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(PointLight) * NUM_POINT_LIGHTS, &point_lights_);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void LightsHandler::UpdateCameraPositionInWorld(const glm::vec3 &cam_position)
{
    scene_renderer_.GetMaterialShellRenderer().ActivateProgram();
    GLuint projection_uniform = scene_renderer_.GetMaterialShellRenderer().GetProgram().GetUniform("camera_pos");
    glUniform3f(projection_uniform, cam_position.x, cam_position.y, cam_position.z);
}

void LightsHandler::AttachLightObject(Light *light_object)
{
    light_objects_.push_back(light_object);
}

void LightsHandler::DetachLightObject(Light *light_object)
{
}

void LightsHandler::Reset()
{
}