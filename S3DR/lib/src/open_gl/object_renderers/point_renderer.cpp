#include "point_renderer.hpp"

#include "../object_adapters/point_adapter.hpp"

#include "shaders/include/point_object_VS.hpp"
#include "shaders/include/point_object_FS.hpp"

#include <glm/gtc/type_ptr.hpp>

PointRenderer::PointRenderer() : SceneObjectRenderer(PointRenderer::GetShaderList())
{
}

PointRenderer::~PointRenderer()
{
}

std::vector<Shader> PointRenderer::GetShaderList()
{
    std::vector<Shader> shader_list;
    shader_list.push_back(Shader(point_object_VS_vert, GL_VERTEX_SHADER));
    shader_list.push_back(Shader(point_object_FS_frag, GL_FRAGMENT_SHADER));
    return shader_list;
}

void PointRenderer::SetModelToClipMatrixPA(const glm::mat4& model_to_clip_matrix)
{
    GLuint model_to_clip_uniform = program_.GetUniform("modelToClipMatrix");
    glUniformMatrix4fv(model_to_clip_uniform, 1, GL_FALSE, glm::value_ptr(model_to_clip_matrix));
}

void PointRenderer::AttachPointAdapter(PointAdapter* point_adapter)
{
    int priority = point_adapter->GetPriority();
    point_adapters_[priority].push_back(point_adapter);
}

void PointRenderer::DetachPointAdapter(PointAdapter* point_adapter)
{
    int priority = point_adapter->GetPriority();
    for(auto it = point_adapters_[priority].begin(); it != point_adapters_[priority].end(); it++)
    {
        if((*it)->GetKey() == point_adapter->GetKey())
        {
            point_adapters_[priority].erase(it);
            break;
        }
    }
}

void PointRenderer::Reset()
{
    point_adapters_[0].clear();
    point_adapters_[1].clear();
    point_adapters_[2].clear();
}

void PointRenderer::Render(const glm::mat4& view, const glm::mat4& projection, int priority)
{
    if(point_adapters_[priority].size() == 0)
    {
        return;
    }

    ActivateProgram();
    glm::mat4 world_to_clip = projection * view;
    for(auto point_adapter : point_adapters_[priority])
    {
        SetModelToClipMatrixPA(world_to_clip * point_adapter->GetModelMatrix());
        point_adapter->Render();
    }
    DeactivateProgram();
}
