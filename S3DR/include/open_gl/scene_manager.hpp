#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

#include "object_renderers/shell_renderer.hpp"
#include "object_renderers/texture_shell_renderer.hpp"
#include "object_renderers/transparency_renderer.hpp"
#include "object_renderers/line_renderer.hpp"
#include "object_renderers/point_renderer.hpp"
#include "object_renderers/selection_renderer.hpp"
#include "techniques/selection_texture.hpp"

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <memory>

class SceneSettings;

class SceneManager {
    public:
        SceneManager(SceneSettings & scene_settings);
        SceneManager(const SceneManager &) = delete;
        SceneManager& operator=(const SceneManager&) = delete;
        virtual ~SceneManager();

        void Render(const glm::mat4 & view, const glm::mat4 & projection);
        void SelectionRender();

        ShellRenderer & ShellRendererRef();
        TextureShellRenderer & TextureShellRendererRef();
        TransparencyRenderer & TransparencyRendererRef();
        LineRenderer & LineRendererRef();
        PointRenderer & PointRendererRef();
        SelectionRenderer & SelectionRendererRef();

        SelectionTexture & SelectionTextureRef();

        float ScreenDepthAt(int x, int y) const;

    private:
        void InitOpenGL();
        void InitUBOs();
        void ConnectUBOsAndPrograms();

        void WidthHeightChanged(const EventInfo & info);
        void BackgroundColorChanged(const EventInfo & info);
        void LightsChanged(const EventInfo & info);

        void UpdateLightsPositons();

        SceneSettings & scene_settings;
        GLuint lights_UBO;

        glm::mat4 view_matrix;
        glm::mat4 projection_matrix;

        std::unique_ptr<ShellRenderer> shell_renderer;
        std::unique_ptr<TextureShellRenderer> texture_shell_renderer;
        std::unique_ptr<TransparencyRenderer> transparency_renderer;
        std::unique_ptr<LineRenderer> line_renderer;
        std::unique_ptr<PointRenderer> point_renderer;
        std::unique_ptr<SelectionRenderer> selection_renderer;

        std::unique_ptr<SelectionTexture> selection_texture;

        std::vector<unsigned int> observer_ids;
};

#endif