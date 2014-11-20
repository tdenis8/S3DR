#include "line_renderer.hpp"

#include "../object_adapters/line_adapter.hpp"

#include "shaders/include/line_object_VS.hpp"
#include "shaders/include/line_object_FS.hpp"

#include <glm/gtc/type_ptr.hpp>

LineRenderer::LineRenderer() : SceneObjectRenderer(LineRenderer::GetShaderList())
{
}

LineRenderer::~LineRenderer()
{
}

std::vector<Shader> LineRenderer::GetShaderList()
{
    std::vector<Shader> shader_list;
    shader_list.push_back(Shader(line_object_VS_vert, GL_VERTEX_SHADER));
    shader_list.push_back(Shader(line_object_FS_frag, GL_FRAGMENT_SHADER));
    return shader_list;
}

void LineRenderer::SetModelToClipMatrixPA(const glm::mat4& model_to_clip_matrix)
{
    GLuint model_to_clip_uniform = program_.GetUniform("modelToClipMatrix");
    glUniformMatrix4fv(model_to_clip_uniform, 1, GL_FALSE, glm::value_ptr(model_to_clip_matrix));
}

void LineRenderer::AttachLineAdapter(LineAdapter* line_adapter)
{
    int priority = line_adapter->GetPriority();
    line_adapters_[priority].push_back(line_adapter);
}

void LineRenderer::DetachLineAdapter(LineAdapter* line_adapter)
{
    int priority = line_adapter->GetPriority();
    for(auto it = line_adapters_[priority].begin(); it != line_adapters_[priority].end(); it++)
    {
        if((*it)->GetKey() == line_adapter->GetKey())
        {
            line_adapters_[priority].erase(it);
            break;
        }
    }
}

void LineRenderer::Reset()
{
    line_adapters_[0].clear();
    line_adapters_[1].clear();
    line_adapters_[2].clear();
}

void LineRenderer::Render(const glm::mat4& view, const glm::mat4& projection, int priority)
{
    if(line_adapters_[priority].size() == 0)
    {
        return;
    }

    ActivateProgram();
    glm::mat4 world_to_clip = projection * view;
    for(auto line_adapter : line_adapters_[priority])
    {
        SetModelToClipMatrixPA(world_to_clip * line_adapter->GetModelMatrix());
        line_adapter->Render();
    }
    DeactivateProgram();
}
