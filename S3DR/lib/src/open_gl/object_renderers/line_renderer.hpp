#ifndef _LINE_RENDERER_H_
#define _LINE_RENDERER_H_

#include "scene_object_renderer.hpp"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <vector>

class LineAdapter;

class LineRenderer : public SceneObjectRenderer
{
public:
    LineRenderer();
    LineRenderer(const LineRenderer &) = delete;
    LineRenderer &operator=(const LineRenderer &) = delete;
    ~LineRenderer();

    void AttachLineAdapter(LineAdapter *line_adapter);
    void DetachLineAdapter(LineAdapter *line_adapter);
    void Reset();

    void Render(const glm::mat4 &view, const glm::mat4 &projection, int priority);

private:
    void InitProgram();

    void SetModelToClipMatrixPA(const glm::mat4 &model_to_clip_matrix);

    std::vector<LineAdapter *> line_adapters[3];
};

#endif