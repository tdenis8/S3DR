#include "material_shell_renderer.hpp"

#include "../object_adapters/material_shell_adapter.hpp"

#include "shaders/include/material_shell_object_VS.hpp"
#include "shaders/include/material_shell_object_FS.hpp"

#include <glm/gtc/type_ptr.hpp>

MaterialShellRenderer::MaterialShellRenderer() : SceneObjectRenderer(MaterialShellRenderer::GetShaderList())
{
}

MaterialShellRenderer::~MaterialShellRenderer()
{
}

std::vector<Shader> MaterialShellRenderer::GetShaderList()
{
   std::vector<Shader> shader_list;
   shader_list.push_back(Shader(material_shell_object_VS_vert, GL_VERTEX_SHADER, "material_shell_object_VS"));
   shader_list.push_back(Shader(material_shell_object_FS_frag, GL_FRAGMENT_SHADER, "material_shell_object_FS"));
   return shader_list;
}

void MaterialShellRenderer::SetModelMatrixPA(const glm::mat4& model)
{
   GLuint model_uniform = program_.GetUniform("model");
   glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(model));
}

void MaterialShellRenderer::SetProjectionViewMatrixPA(const glm::mat4& projection_view)
{
   GLuint projection_view_uniform = program_.GetUniform("projection_view");
   glUniformMatrix4fv(projection_view_uniform, 1, GL_FALSE, glm::value_ptr(projection_view));
}

void MaterialShellRenderer::SetNormalModelMatrixPA(const glm::mat3& normal_model)
{
   GLuint normal_model_uniform = program_.GetUniform("normal_model");
   glUniformMatrix3fv(normal_model_uniform, 1, GL_FALSE, glm::value_ptr(normal_model));
}

void MaterialShellRenderer::AttachMaterialShellAdapter(MaterialShellAdapter* shell_adapter)
{
   int priority = shell_adapter->GetPriority();
   material_shell_adapters_[priority].push_back(shell_adapter);
   shell_adapter->SetProgram(&program_);
}

void MaterialShellRenderer::DetachMaterialShellAdapter(MaterialShellAdapter* shell_adapter)
{
   int priority = shell_adapter->GetPriority();
   for (auto it = material_shell_adapters_[priority].begin(); it != material_shell_adapters_[priority].end(); it++)
   {
      if ((*it)->GetKey() == shell_adapter->GetKey())
      {
         material_shell_adapters_[priority].erase(it);
         break;
      }
   }
}

void MaterialShellRenderer::Reset()
{
   material_shell_adapters_[0].clear();
   material_shell_adapters_[1].clear();
   material_shell_adapters_[2].clear();
}

void MaterialShellRenderer::Render(const glm::mat4& view, const glm::mat4& projection, int priority)
{
   if (material_shell_adapters_[priority].size() == 0)
   {
      return;
   }

   ActivateProgram();

   SetProjectionViewMatrixPA(projection * view);
   for (auto material_shell_adapter : material_shell_adapters_[priority])
   {
      glm::mat4 model = material_shell_adapter->GetModelMatrix();
      SetModelMatrixPA(model);
      glm::mat3 normal_model = glm::transpose(glm::inverse(glm::mat3(model)));
      SetNormalModelMatrixPA(normal_model);
      material_shell_adapter->Render();
   }

   DeactivateProgram();
}
