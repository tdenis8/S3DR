#ifndef _SCENE_RENDERER_H_
#define _SCENE_RENDERER_H_

#include "object_renderers/material_shell_renderer.hpp"
#include "object_renderers/texture_shell_renderer.hpp"
#include "object_renderers/transparency_renderer.hpp"
#include "object_renderers/line_renderer.hpp"
#include "object_renderers/point_renderer.hpp"
#include "object_renderers/selection_renderer.hpp"
#include "object_renderers/text_renderer.hpp"

#include "misc/selection_texture.hpp"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <GL/glew.h>

class SceneSettings;

class SceneRenderer : Observer
{
   public:
   SceneRenderer() = delete;
   explicit SceneRenderer(SceneSettings& scene_settings);
   SceneRenderer(const SceneRenderer&) = delete;
   SceneRenderer(SceneRenderer&&) = delete;
   SceneRenderer& operator=(const SceneRenderer&) = delete;
   SceneRenderer& operator=(SceneRenderer&&) = delete;
   virtual ~SceneRenderer();

   // TODO: insted of  view and projection send cmera data struct
   void Render(const glm::mat4& view, const glm::mat4& projection);
   void SelectionRender();

   MaterialShellRenderer& GetMaterialShellRenderer();
   TextureShellRenderer& GetTextureShellRenderer();
   LineRenderer& GetLineRenderer();
   PointRenderer& GetPointRenderer();
   SelectionRenderer& GetSelectionRenderer();
   TextRenderer& GetTextRenderer();

   SelectionTexture& GetSelectionTexture();

   float ScreenDepthAt(int x, int y) const;

   void Reset();

   private:
   void WidthHeightChanged(const EventInfo& info);
   void BackgroundColorChanged(const EventInfo& info);
   void LightsChanged(const EventInfo& info);

   glm::mat4 view_matrix_;
   glm::mat4 projection_matrix_;

   SceneSettings& scene_settings_;

   // Renderers
   MaterialShellRenderer material_shell_renderer_;
   TextureShellRenderer texture_shell_renderer_;
   LineRenderer line_renderer_;
   PointRenderer point_renderer_;
   SelectionRenderer selection_renderer_;
   TextRenderer text_renderer_;

   // Misc
   SelectionTexture selection_texture_;
};

#endif