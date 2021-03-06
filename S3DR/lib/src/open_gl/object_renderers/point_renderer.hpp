#ifndef _POINT_RENDERER_H_
#define _POINT_RENDERER_H_

#include "scene_object_renderer.hpp"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <vector>

class PointAdapter;

class PointRenderer : public SceneObjectRenderer
{
    public:
    PointRenderer();
    PointRenderer(const PointRenderer &) = delete;
    PointRenderer &operator=(const PointRenderer &) = delete;
    ~PointRenderer();

    void AttachPointAdapter(PointAdapter *point_adapter);
    void DetachPointAdapter(PointAdapter *point_adapter);
    void Reset();

    void Render(const glm::mat4 &view, const glm::mat4 &projection, int priority);

    private:
    static std::vector<Shader> GetShaderList();

    void SetModelToClipMatrixPA(const glm::mat4 &model_to_clip_matrix);

    std::vector<PointAdapter *> point_adapters_[3];
};

#endif