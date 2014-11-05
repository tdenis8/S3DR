#ifndef _TEXTURE_SHELL_RENDERER_H_
#define _TEXTURE_SHELL_RENDERER_H_

#include "scene_object_renderer.hpp"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <vector>

class TextureShellAdapter;

class TextureShellRenderer : public SceneObjectRenderer
{
public:
    TextureShellRenderer();
    TextureShellRenderer(const TextureShellRenderer &) = delete;
    TextureShellRenderer &operator=(const TextureShellRenderer &) = delete;
    ~TextureShellRenderer();

    void AttachTextureShellAdapter(TextureShellAdapter *texture_shell_adapter);
    void DetachTextureShellAdapter(TextureShellAdapter *texture_shell_adapter);
    void Reset();

    void Render(const glm::mat4 &view, const glm::mat4 &projection, int priority);

private:
    void InitProgram();

    void SetModelToCameraMatrixPA(const glm::mat4 &model_to_camera_matrix);
    void SetCameraToClipMatrixPA(const glm::mat4 &camera_to_clip);
    void SetNormalModelToCameraMatrixPA(const glm::mat3 &normal_model_to_camera_matrix);

    std::vector<TextureShellAdapter *> texture_shell_adapters[3];
};

#endif