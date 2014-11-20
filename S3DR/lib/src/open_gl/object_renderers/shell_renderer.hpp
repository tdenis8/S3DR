#ifndef _SHELL_RENDERER_H_
#define _SHELL_RENDERER_H_

#include "scene_object_renderer.hpp"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <vector>

class ShellAdapter;

class ShellRenderer : public SceneObjectRenderer
{
    public:
    ShellRenderer();
    ShellRenderer(const ShellRenderer &) = delete;
    ShellRenderer &operator=(const ShellRenderer &) = delete;
    ~ShellRenderer();

    void AttachShellAdapter(ShellAdapter *shell_adapter);
    void DetachShellAdapter(ShellAdapter *shell_adapter);
    void Reset();

    void Render(const glm::mat4 &view, const glm::mat4 &projection, int priority);

    private:
    static std::vector<Shader> GetShaderList();

    void SetModelToCameraMatrixPA(const glm::mat4 &model_to_camera_matrix);
    void SetCameraToClipMatrixPA(const glm::mat4 &camera_to_clip);
    void SetNormalModelToCameraMatrixPA(const glm::mat3 &normal_model_to_camera_matrix);
    void SetMaterialColorPA(const glm::vec4 &color);
    void SetMaterialStatusPA(int status);

    std::vector<ShellAdapter *> shell_adapters_[3];
};

#endif