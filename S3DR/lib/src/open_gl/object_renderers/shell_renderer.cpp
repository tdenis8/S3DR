#include "shell_renderer.hpp"

#include "../object_adapters/shell_adapter.hpp"

#include "shaders/include/shell_object_VS.hpp"
#include "shaders/include/shell_object_FS.hpp"

#include <glm/gtc/type_ptr.hpp>

ShellRenderer::ShellRenderer() : SceneObjectRenderer(ShellRenderer::GetShaderList())
{
}

ShellRenderer::~ShellRenderer()
{
}

std::vector<Shader> ShellRenderer::GetShaderList()
{
    std::vector<Shader> shader_list;
    shader_list.push_back(Shader(shell_object_VS_vert, GL_VERTEX_SHADER));
    shader_list.push_back(Shader(shell_object_FS_frag, GL_FRAGMENT_SHADER));
    return shader_list;
}

void ShellRenderer::SetModelToCameraMatrixPA(const glm::mat4& model_to_camera_matrix)
{
    GLuint model_to_camera_uniform = program_.GetUniform("modelToCameraMatrix");
    glUniformMatrix4fv(model_to_camera_uniform, 1, GL_FALSE, glm::value_ptr(model_to_camera_matrix));
}

void ShellRenderer::SetCameraToClipMatrixPA(const glm::mat4& camera_to_clip)
{
    GLuint camera_to_clip_uniform = program_.GetUniform("cameraToClipMatrix");
    glUniformMatrix4fv(camera_to_clip_uniform, 1, GL_FALSE, glm::value_ptr(camera_to_clip));
}

void ShellRenderer::SetNormalModelToCameraMatrixPA(const glm::mat3& normal_model_to_camera_matrix)
{
    GLuint normal_model_to_camera_uniform = program_.GetUniform("normalModelToCameraMatrix");
    glUniformMatrix3fv(normal_model_to_camera_uniform, 1, GL_FALSE, glm::value_ptr(normal_model_to_camera_matrix));
}

void ShellRenderer::SetMaterialColorPA(const glm::vec4& color)
{
    GLuint material_color_uniform = program_.GetUniform("material_color");
    glUniform4fv(material_color_uniform, 1, glm::value_ptr(color));
}

void ShellRenderer::SetMaterialStatusPA(int status)
{
    GLuint material_status_uniform = program_.GetUniform("material_status");
    glUniform1i(material_status_uniform, status);
}

void ShellRenderer::AttachShellAdapter(ShellAdapter* shell_adapter)
{
    int priority = shell_adapter->GetPriority();
    shell_adapters_[priority].push_back(shell_adapter);
}

void ShellRenderer::DetachShellAdapter(ShellAdapter* shell_adapter)
{
    int priority = shell_adapter->GetPriority();
    for(auto it = shell_adapters_[priority].begin(); it != shell_adapters_[priority].end(); it++)
    {
        if((*it)->GetKey() == shell_adapter->GetKey())
        {
            shell_adapters_[priority].erase(it);
            break;
        }
    }
}

void ShellRenderer::Reset()
{
    shell_adapters_[0].clear();
    shell_adapters_[1].clear();
    shell_adapters_[2].clear();
}

void ShellRenderer::Render(const glm::mat4& view, const glm::mat4& projection, int priority)
{
    if(shell_adapters_[priority].size() == 0)
    {
        return;
    }
    ActivateProgram();
    SetCameraToClipMatrixPA(projection);
    for(auto shell_adapter : shell_adapters_[priority])
    {
        glm::mat4 model_to_camera_matrix = view * shell_adapter->GetModelMatrix();
        SetModelToCameraMatrixPA(model_to_camera_matrix);
        glm::mat3 normMatrix(view * shell_adapter->GetModelMatrix());
        normMatrix = glm::transpose(glm::inverse(normMatrix));
        SetNormalModelToCameraMatrixPA(normMatrix);

        int status = shell_adapter->MaterialStatus();
        SetMaterialStatusPA(status);
        if(status == 1)
        {
            SetMaterialColorPA(shell_adapter->MaterialColor());
        }

        shell_adapter->Render();
    }
    DeactivateProgram();
}
