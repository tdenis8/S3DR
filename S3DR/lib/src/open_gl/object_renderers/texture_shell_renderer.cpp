#include "texture_shell_renderer.hpp"

#include "../object_adapters/texture_shell_adapter.hpp"

#include "shaders/include/texture_shell_object_VS.hpp"
#include "shaders/include/texture_shell_object_FS.hpp"

#include <glm/gtc/type_ptr.hpp>

TextureShellRenderer::TextureShellRenderer() : SceneObjectRenderer(TextureShellRenderer::GetShaderList())
{
}

TextureShellRenderer::~TextureShellRenderer()
{
}

std::vector<Shader> TextureShellRenderer::GetShaderList()
{
    std::vector<Shader> shader_list;
    shader_list.push_back(Shader(texture_shell_object_VS_vert, GL_VERTEX_SHADER));
    shader_list.push_back(Shader(texture_shell_object_FS_frag, GL_FRAGMENT_SHADER));
    return shader_list;
}

void TextureShellRenderer::SetModelToCameraMatrixPA(const glm::mat4& model_to_camera_matrix)
{
    GLuint model_to_camera_uniform = program_.GetUniform("modelToCameraMatrix");
    glUniformMatrix4fv(model_to_camera_uniform, 1, GL_FALSE, glm::value_ptr(model_to_camera_matrix));
}

void TextureShellRenderer::SetCameraToClipMatrixPA(const glm::mat4& camera_to_clip)
{
    GLuint camera_to_clip_uiform = program_.GetUniform("cameraToClipMatrix");
    glUniformMatrix4fv(camera_to_clip_uiform, 1, GL_FALSE, glm::value_ptr(camera_to_clip));
}

void TextureShellRenderer::SetNormalModelToCameraMatrixPA(const glm::mat3& normal_model_to_camera_matrix)
{
    GLuint normal_model_to_camera_uniform = program_.GetUniform("normalModelToCameraMatrix");
    glUniformMatrix3fv(normal_model_to_camera_uniform, 1, GL_FALSE, glm::value_ptr(normal_model_to_camera_matrix));
}

void TextureShellRenderer::AttachTextureShellAdapter(TextureShellAdapter* texture_shell_adapter)
{
    int priority = texture_shell_adapter->GetPriority();
    texture_shell_adapters_[priority].push_back(texture_shell_adapter);
}

void TextureShellRenderer::DetachTextureShellAdapter(TextureShellAdapter* texture_shell_adapter)
{
    int priority = texture_shell_adapter->GetPriority();
    for(auto it = texture_shell_adapters_[priority].begin(); it != texture_shell_adapters_[priority].end(); it++)
    {
        if((*it)->GetKey() == texture_shell_adapter->GetKey())
        {
            texture_shell_adapters_[priority].erase(it);
            break;
        }
    }
}

void TextureShellRenderer::Reset()
{
    texture_shell_adapters_[0].clear();
    texture_shell_adapters_[1].clear();
    texture_shell_adapters_[2].clear();
}

void TextureShellRenderer::Render(const glm::mat4& view, const glm::mat4& projection, int priority)
{
    if(texture_shell_adapters_[priority].size() == 0)
    {
        return;
    }
    ActivateProgram();
    SetCameraToClipMatrixPA(projection);
    for(auto texture_shell_adapter : texture_shell_adapters_[priority])
    {
        glm::mat4 model_to_camera_matrix = view * texture_shell_adapter->GetModelMatrix();
        SetModelToCameraMatrixPA(model_to_camera_matrix);
        glm::mat3 normMatrix(view * texture_shell_adapter->GetModelMatrix());
        normMatrix = glm::transpose(glm::inverse(normMatrix));
        SetNormalModelToCameraMatrixPA(normMatrix);
        texture_shell_adapter->Render();
    }
    DeactivateProgram();
}
