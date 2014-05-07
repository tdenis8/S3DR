#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

#include "object_renderers/shell_renderer.hpp"
#include "object_renderers/texture_shell_renderer.hpp"
#include "object_renderers/transparency_renderer.hpp"
#include "object_renderers/line_renderer.hpp"
#include "object_renderers/point_renderer.hpp"
#include "object_renderers/selection_renderer.hpp"
#include "object_renderers/text_renderer.hpp"

#include "misc/selection_texture.hpp"

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <memory>

class SceneSettings;

class SceneManager : Observer
{
public:
    SceneManager() = delete;
    explicit SceneManager(SceneSettings& scene_settings);
    SceneManager(const SceneManager&) = delete;
    SceneManager(SceneManager&&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;
    SceneManager& operator=(SceneManager&&) = delete;
    virtual ~SceneManager();

    // TODO: insted of  view and projection send cmera data struct
    void Render(const glm::mat4& view, const glm::mat4& projection);
    void SelectionRender();

    ShellRenderer& GetShellRenderer();
    TextureShellRenderer& GetTextureShellRenderer();
    TransparencyRenderer& GetTransparencyRenderer();
    LineRenderer& GetLineRenderer();
    PointRenderer& GetPointRenderer();
    SelectionRenderer& GetSelectionRenderer();
    TextRenderer& GetTextRenderer();

    SelectionTexture& GetSelectionTexture();

    float ScreenDepthAt(int x, int y) const;

private:
    void InitUBOs();
    void ConnectUBOsAndPrograms();

    void WidthHeightChanged(const EventInfo& info);
    void BackgroundColorChanged(const EventInfo& info);
    void LightsChanged(const EventInfo& info);

    void UpdateLightsPositons();

    GLuint lights_UBO;
    glm::mat4 view_matrix;
    glm::mat4 projection_matrix;

    SceneSettings& scene_settings;

    // Renderers
    ShellRenderer shell_renderer;
    TextureShellRenderer texture_shell_renderer;
    TransparencyRenderer transparency_renderer;
    LineRenderer line_renderer;
    PointRenderer point_renderer;
    SelectionRenderer selection_renderer;
    TextRenderer text_renderer;

    // Misc
    SelectionTexture selection_texture;
};

#endif