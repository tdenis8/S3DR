#include "scene_renderer.hpp"

#include "utility/custom_exp.hpp"

#include "scene_settings.hpp"

#include <glm/gtc/type_ptr.hpp>

SceneRenderer::SceneRenderer(SceneSettings& scene_settings) try : Observer(), scene_settings_(scene_settings)
{
   // Set observers
   scene_settings_.Observe(SceneSettingsEvents::WIDTH_HEIGHT_CHANGED,
                           std::bind(&SceneRenderer::WidthHeightChanged, this, std::placeholders::_1), this);

   scene_settings_.Observe(SceneSettingsEvents::BACKGROUND_COLOR_CHANGED,
                           std::bind(&SceneRenderer::BackgroundColorChanged, this, std::placeholders::_1), this);
}
catch (CustomExp e)
{
   scene_settings.RemoveObservers(this);
   throw e;
}

SceneRenderer::~SceneRenderer()
{
   scene_settings_.RemoveObservers(this);
}

void SceneRenderer::WidthHeightChanged(const EventInfo& info)
{
   text_renderer_.SetWidthHeight(scene_settings_.Width(), scene_settings_.Height());
   selection_texture_.SetWidthHeight(scene_settings_.Width(), scene_settings_.Height());
}

void SceneRenderer::BackgroundColorChanged(const EventInfo& info)
{
}

void SceneRenderer::Render(const glm::mat4& view, const glm::mat4& projection)
{
   view_matrix_ = view;
   projection_matrix_ = projection;

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // // Priority 0 render
   // point_renderer->Render(view, projection, 0);
   // line_renderer->Render(view, projection, 0);
   // shell_renderer->Render(view, projection, 0);

   // Priority 1 render
   // glClear(GL_DEPTH_BUFFER_BIT);
   point_renderer_.Render(view, projection, 1);
   line_renderer_.Render(view, projection, 1);
   material_shell_renderer_.Render(view, projection, 1);
   texture_shell_renderer_.Render(view, projection, 1);
   glClear(GL_DEPTH_BUFFER_BIT);
   text_renderer_.Render();

   // // Priority 2 render
   // glClear(GL_DEPTH_BUFFER_BIT);
   // point_renderer->Render(view, projection, 2);
   // line_renderer->Render(view, projection, 2);
   // shell_renderer->Render(view, projection, 2);
}

void SceneRenderer::SelectionRender()
{
   selection_texture_.EnableWriting();
   glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

   // Priority 0 render
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   selection_renderer_.Render(view_matrix_, projection_matrix_, 0);
   // Priority 1 render
   glClear(GL_DEPTH_BUFFER_BIT);
   selection_renderer_.Render(view_matrix_, projection_matrix_, 1);
   // Priority 2 render
   glClear(GL_DEPTH_BUFFER_BIT);
   selection_renderer_.Render(view_matrix_, projection_matrix_, 2);

   selection_texture_.DisableWriting();
   glm::vec3 background_color = scene_settings_.BackgroundColor();
   glClearColor(background_color.x, background_color.y, background_color.z, 0.0f);
}

MaterialShellRenderer& SceneRenderer::GetMaterialShellRenderer()
{
   return material_shell_renderer_;
}

TextureShellRenderer& SceneRenderer::GetTextureShellRenderer()
{
   return texture_shell_renderer_;
}

LineRenderer& SceneRenderer::GetLineRenderer()
{
   return line_renderer_;
}

PointRenderer& SceneRenderer::GetPointRenderer()
{
   return point_renderer_;
}

SelectionRenderer& SceneRenderer::GetSelectionRenderer()
{
   return selection_renderer_;
}

TextRenderer& SceneRenderer::GetTextRenderer()
{
   return text_renderer_;
}

SelectionTexture& SceneRenderer::GetSelectionTexture()
{
   return selection_texture_;
}

float SceneRenderer::ScreenDepthAt(int x, int y) const
{
   float depth;
   glBindFramebuffer(GL_FRAMEBUFFER, 0);
   glReadPixels(x, y - 1, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
   return depth;
}

void SceneRenderer::Reset()
{
   material_shell_renderer_.Reset();
   texture_shell_renderer_.Reset();
   line_renderer_.Reset();
   point_renderer_.Reset();
   text_renderer_.Reset();

   selection_renderer_.Reset();
}