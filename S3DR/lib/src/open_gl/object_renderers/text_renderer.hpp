#ifndef _TEXT_RENDERER_H_
#define _TEXT_RENDERER_H_

#include "scene_object_renderer.hpp"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <vector>

class TextAdapter;

class TextRenderer : public SceneObjectRenderer
{
    public:
    TextRenderer();
    TextRenderer(const TextRenderer &) = delete;
    TextRenderer &operator=(const TextRenderer &) = delete;
    ~TextRenderer();

    void SetWidthHeight(int width, int height);

    void AttachTextAdapter(TextAdapter *text_adapter);
    void DetachTextAdapter(TextAdapter *text_adapter);
    void Reset();

    void Render();

    private:
    static std::vector<Shader> GetShaderList();

    void SetModelToClipMatrixPA(const glm::mat4 &model_to_clip_matrix);

    glm::mat4 projection_matrix_;
    std::vector<TextAdapter *> text_adapters_;
};

#endif