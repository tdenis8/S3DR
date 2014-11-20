#include "selection_renderer.hpp"

#include "../object_adapters/scene_object_adapter.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <functional>

#include "shaders/include/selection_VS.hpp"
#include "shaders/include/selection_FS.hpp"

SelectionRenderer::SelectionRenderer() : SceneObjectRenderer(SelectionRenderer::GetShaderList())
{
}

SelectionRenderer::~SelectionRenderer()
{
}

std::vector<Shader> SelectionRenderer::GetShaderList()
{
    std::vector<Shader> shader_list;
    shader_list.push_back(Shader(selection_VS_vert, GL_VERTEX_SHADER));
    shader_list.push_back(Shader(selection_FS_frag, GL_FRAGMENT_SHADER));
    return shader_list;
}

void SelectionRenderer::SetModelToClipMatrixPA(const glm::mat4& model_to_clip_matrix)
{
    GLuint model_to_world_uniform = program_.GetUniform("modelToClipMatrix");
    glUniformMatrix4fv(model_to_world_uniform, 1, GL_FALSE, glm::value_ptr(model_to_clip_matrix));
}

void SelectionRenderer::SetSceneObjectKeyPA(int scene_object_key)
{
    GLuint segment_index_uniform = program_.GetUniform("SceneObjectKey");
    glUniform1ui(segment_index_uniform, scene_object_key);
}

void SelectionRenderer::SetEntryIndexPA(int entry_index)
{
    GLuint draw_index_uniform = program_.GetUniform("EntryIndex");
    glUniform1ui(draw_index_uniform, entry_index);
}

void SelectionRenderer::AttachSceneObjectAdapter(SceneObjectAdapter* scene_object_adapter)
{
    int priority = scene_object_adapter->GetPriority();
    scene_object_adapters_[priority].push_back(scene_object_adapter);
}

void SelectionRenderer::DetachSceneObjectAdapter(SceneObjectAdapter* scene_object_adapter)
{
    int priority = scene_object_adapter->GetPriority();
    for(auto it = scene_object_adapters_[priority].begin(); it != scene_object_adapters_[priority].end(); it++)
    {
        if((*it)->GetKey() == scene_object_adapter->GetKey())
        {
            scene_object_adapters_[priority].erase(it);
            break;
        }
    }
}

void SelectionRenderer::Reset()
{
    scene_object_adapters_[0].clear();
    scene_object_adapters_[1].clear();
    scene_object_adapters_[2].clear();
}

void SelectionRenderer::Render(const glm::mat4& view, const glm::mat4& projection, int priority)
{
    if(scene_object_adapters_[priority].size() == 0)
    {
        return;
    }

    std::function<void(int)> set_scene_object_key =
        std::bind(&SelectionRenderer::SetSceneObjectKeyPA, this, std::placeholders::_1);
    std::function<void(int)> set_entry_index =
        std::bind(&SelectionRenderer::SetEntryIndexPA, this, std::placeholders::_1);

    glm::mat4 world_to_clip = projection * view;
    ActivateProgram();
    for(auto scene_object_adapter : scene_object_adapters_[priority])
    {
        SetModelToClipMatrixPA(world_to_clip * scene_object_adapter->GetModelMatrix());
        scene_object_adapter->SelectionRender(set_scene_object_key, set_entry_index);
    }
    DeactivateProgram();
}