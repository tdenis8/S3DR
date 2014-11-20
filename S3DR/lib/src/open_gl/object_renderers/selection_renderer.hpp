#ifndef _SELECT_RENDERER_HPP_
#define _SELECT_RENDERER_HPP_

#include "scene_object_renderer.hpp"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <vector>

class SceneObjectAdapter;

class SelectionRenderer : public SceneObjectRenderer
{
    public:
    SelectionRenderer();
    SelectionRenderer(const SelectionRenderer &) = delete;
    SelectionRenderer &operator=(const SelectionRenderer &) = delete;
    ~SelectionRenderer();

    void AttachSceneObjectAdapter(SceneObjectAdapter *scene_object_adapter);
    void DetachSceneObjectAdapter(SceneObjectAdapter *scene_object_adapter);
    void Reset();

    void Render(const glm::mat4 &view, const glm::mat4 &projection, int priority);

    private:
    static std::vector<Shader> GetShaderList();

    void SetModelToClipMatrixPA(const glm::mat4 &model_to_clip_matrix);
    void SetSceneObjectKeyPA(int scene_object_key);
    void SetEntryIndexPA(int entry_index);

    std::vector<SceneObjectAdapter *> scene_object_adapters_[3];
};

#endif