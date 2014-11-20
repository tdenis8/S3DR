#include "transparency_renderer.hpp"

#include "../object_adapters/shell_adapter.hpp"

#include "shaders/include/DDPInitVS.hpp"
#include "shaders/include/DDPInitFS.hpp"

#include "shaders/include/DDPPeelVS.hpp"
#include "shaders/include/DDPPeelFS.hpp"

#include "shaders/include/DDPBlendVS.hpp"
#include "shaders/include/DDPBlendFS.hpp"

#include "shaders/include/DDPFinalVS.hpp"
#include "shaders/include/DDPFinalFS.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <iostream>

TransparencyRenderer::TransparencyRenderer()
    : SceneObjectRenderer(TransparencyRenderer::GetEmptyShaderList())
    , init_program_(TransparencyRenderer::GetInitProgramShaderList())
    , peel_program_(TransparencyRenderer::GetPillProgramShaderList())
    , blend_program_(TransparencyRenderer::GetBlendProgramShaderList())
    , final_program_(TransparencyRenderer::GetFinalProgramShaderList())
    , dual_depth_peeling_(*this)
{
}

TransparencyRenderer::~TransparencyRenderer()
{
}

std::vector<Shader> TransparencyRenderer::GetEmptyShaderList()
{
    return std::vector<Shader>();
}

std::vector<Shader> TransparencyRenderer::GetInitProgramShaderList()
{
    std::vector<Shader> shader_list;
    shader_list.push_back(Shader(DDPInitVS_vert, GL_VERTEX_SHADER));
    shader_list.push_back(Shader(DDPInitFS_frag, GL_FRAGMENT_SHADER));
    return shader_list;
}

std::vector<Shader> TransparencyRenderer::GetPillProgramShaderList()
{
    std::vector<Shader> shader_list;
    shader_list.push_back(Shader(DDPPeelVS_vert, GL_VERTEX_SHADER));
    shader_list.push_back(Shader(DDPPeelFS_frag, GL_FRAGMENT_SHADER));
    return shader_list;
}

std::vector<Shader> TransparencyRenderer::GetBlendProgramShaderList()
{
    std::vector<Shader> shader_list;
    shader_list.push_back(Shader(DDPBlendVS_vert, GL_VERTEX_SHADER));
    shader_list.push_back(Shader(DDPBlendFS_frag, GL_FRAGMENT_SHADER));
    return shader_list;
}

std::vector<Shader> TransparencyRenderer::GetFinalProgramShaderList()
{
    std::vector<Shader> shader_list;
    shader_list.push_back(Shader(DDPFinalVS_vert, GL_VERTEX_SHADER));
    shader_list.push_back(Shader(DDPFinalFS_frag, GL_FRAGMENT_SHADER));
    return shader_list;
}

void TransparencyRenderer::SetModelToClipMatrixPA(const glm::mat4& model_to_clip_matrix)
{
    GLuint model_to_world_uniform = program_.GetUniform("modelToClipMatrix");
    glUniformMatrix4fv(model_to_world_uniform, 1, GL_FALSE, glm::value_ptr(model_to_clip_matrix));
}

void TransparencyRenderer::SetModelToCameraMatrixPA(const glm::mat4& model_to_camera_matrix)
{
    GLuint model_to_camera_uniform = program_.GetUniform("modelToCameraMatrix");
    glUniformMatrix4fv(model_to_camera_uniform, 1, GL_FALSE, glm::value_ptr(model_to_camera_matrix));
}

void TransparencyRenderer::SetNormalModelToCameraMatrixPA(const glm::mat3& normal_model_to_camera_matrix)
{
    GLuint normal_model_to_camera_uniform = program_.GetUniform("normalModelToCameraMatrix");
    glUniformMatrix3fv(normal_model_to_camera_uniform, 1, GL_FALSE, glm::value_ptr(normal_model_to_camera_matrix));
}

void TransparencyRenderer::ActivateProgram(DDPPassType type)
{
    if(type == DDPPassType::INIT)
    {
        program_ = init_program_;
    }
    else if(type == DDPPassType::PEEL)
    {
        program_ = peel_program_;
    }
    else if(type == DDPPassType::BLEND)
    {
        program_ = blend_program_;
    }
    else if(type == DDPPassType::FINAL)
    {
        program_ = final_program_;
    }

    glUseProgram(program_.ProgramObject());
}

void TransparencyRenderer::DeactivateProgram()
{
    glUseProgram(0);
}

void TransparencyRenderer::BindTexture(GLenum target, std::string texname, GLuint texid, int texunit)
{
    glActiveTexture(GL_TEXTURE0 + texunit);
    glBindTexture(target, texid);

    GLint linked;
    glGetProgramiv(program_.ProgramObject(), GL_LINK_STATUS, &linked);
    if(linked != GL_TRUE)
    {
        std::cerr << "Error: setTextureUnit needs program to be linked." << std::endl;
        exit(1);
    }
    GLint id = glGetUniformLocation(program_.ProgramObject(), texname.c_str());
    if(id == -1)
    {
        std::cerr << "Warning: Invalid texture " << texname << std::endl;
        return;
    }
    glUniform1i(id, texunit);

    glActiveTexture(GL_TEXTURE0);
}

void TransparencyRenderer::SetAlphaPA(float alpha)
{
    GLuint alpha_uniform = program_.GetUniform("alpha");
    glUniform1f(alpha_uniform, alpha);
}

void TransparencyRenderer::AttachShellAdapter(ShellAdapter* shell_adapter)
{
    int priority = shell_adapter->GetPriority();
    shell_adapters_[priority].push_back(shell_adapter);
}

void TransparencyRenderer::Reset()
{
    shell_adapters_[0].clear();
    shell_adapters_[1].clear();
    shell_adapters_[2].clear();
}

void TransparencyRenderer::SetWidthHeight(int width, int height)
{
    dual_depth_peeling_.SetWidthHeight(width, height);
}

void TransparencyRenderer::SetBackgroundColor(const glm::vec4& background_color)
{
    dual_depth_peeling_.SetBackgroundColor(background_color);
}

void TransparencyRenderer::Render(const glm::mat4& view, const glm::mat4& projection, int priority)
{
    if(shell_adapters_[priority].size() == 0)
    {
        return;
    }

    glm::mat4 world_to_clip = projection * view;
    for(auto shell_adapter : shell_adapters_[priority])
    {
        glm::mat4 model_to_clip_matrix = world_to_clip * shell_adapter->GetModelMatrix();
        glm::mat4 model_to_camera_matrix = view * shell_adapter->GetModelMatrix();
        ActivateProgram(DDPPassType::INIT);
        SetModelToClipMatrixPA(model_to_clip_matrix);
        DeactivateProgram();

        ActivateProgram(DDPPassType::PEEL);
        SetModelToClipMatrixPA(model_to_clip_matrix);
        SetModelToCameraMatrixPA(model_to_camera_matrix);
        glm::mat3 normMatrix(model_to_camera_matrix);
        normMatrix = glm::transpose(glm::inverse(normMatrix));
        SetNormalModelToCameraMatrixPA(normMatrix);
        SetAlphaPA(0.8);
        DeactivateProgram();

        dual_depth_peeling_.Render(std::bind(&ShellAdapter::Render, shell_adapter));
    }
}