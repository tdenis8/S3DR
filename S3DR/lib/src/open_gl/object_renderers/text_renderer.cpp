#include "text_renderer.hpp"

#include "../object_adapters/text_adapter.hpp"

#include "shaders/include/text_object_VS.hpp"
#include "shaders/include/text_object_FS.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

TextRenderer::TextRenderer() : SceneObjectRenderer(TextRenderer::GetShaderList())
{
}

TextRenderer::~TextRenderer()
{
}

std::vector<Shader> TextRenderer::GetShaderList()
{
   std::vector<Shader> shader_list;
   shader_list.push_back(Shader(text_object_VS_vert, GL_VERTEX_SHADER, "text_object_VS"));
   shader_list.push_back(Shader(text_object_FS_frag, GL_FRAGMENT_SHADER, "text_object_FS"));
   return shader_list;
}

void TextRenderer::SetModelToClipMatrixPA(const glm::mat4& model_to_clip_matrix)
{
   GLuint model_to_clip_uniform = program_.GetUniform("modelToClipMatrix");
   glUniformMatrix4fv(model_to_clip_uniform, 1, GL_FALSE, glm::value_ptr(model_to_clip_matrix));
}

void TextRenderer::SetWidthHeight(int width, int height)
{
   projection_matrix_ = glm::ortho(0.f, (float)width, (float)height, 0.f, -1.f, 1.f);
}

void TextRenderer::AttachTextAdapter(TextAdapter* text_adapter)
{
   text_adapters_.push_back(text_adapter);
}

void TextRenderer::DetachTextAdapter(TextAdapter* text_adapter)
{
   for (auto it = text_adapters_.begin(); it != text_adapters_.end(); it++)
   {
      if ((*it)->GetKey() == text_adapter->GetKey())
      {
         text_adapters_.erase(it);
         break;
      }
   }
}

void TextRenderer::Reset()
{
   text_adapters_.clear();
}

void TextRenderer::Render()
{
   if (text_adapters_.size() == 0)
   {
      return;
   }
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   ActivateProgram();
   glUniform1i(glGetUniformLocation(program_.ProgramObject(), "text_texture"), 0);
   for (auto text_adapter : text_adapters_)
   {
      SetModelToClipMatrixPA(projection_matrix_ * text_adapter->GetModelMatrix());
      text_adapter->Render();
   }

   DeactivateProgram();
}
