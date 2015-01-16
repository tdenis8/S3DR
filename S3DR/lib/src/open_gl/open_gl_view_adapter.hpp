#ifndef _OPEN_GL_VIEW_ADAPTER_H_
#define _OPEN_GL_VIEW_ADAPTER_H_

#include "utility/subject.hpp"

#include "view/view_adapter.hpp"
#include "view/selection_set.hpp"
#include "view/camera.hpp"

#include "scene_settings.hpp"
#include "scene_renderer.hpp"
#include "lights_handler.hpp"
#include "model_handler.hpp"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <memory>
#include <vector>

class OpenGLInitazer
{
    public:
    OpenGLInitazer();
};

class OpenGLViewAdapter : public ViewAdapter, Observer
{
    public:
    OpenGLViewAdapter() = delete;
    explicit OpenGLViewAdapter(View &view);
    OpenGLViewAdapter(const OpenGLViewAdapter &) = delete;
    OpenGLViewAdapter(OpenGLViewAdapter &&) = delete;
    OpenGLViewAdapter &operator=(const OpenGLViewAdapter &) = delete;
    OpenGLViewAdapter &operator=(OpenGLViewAdapter &&) = delete;
    virtual ~OpenGLViewAdapter();

    void Render();
    float ScreenDepthAt(int x, int y) const;

    private:
    void AttachModel(const EventInfo &info);
    void DetachModel(const EventInfo &info);
    void WindowResize(const EventInfo &info);
    void ViewerSettingsChange(const EventInfo &info);
    void CalculateSelection(const EventInfo &info);

    OpenGLInitazer open_gl_initazer_;
    SceneSettings scene_settings_;
    SceneRenderer scene_renderer_;
    LightsHandler lights_handler_;

    SelectionSet &selection_set_;

    std::unique_ptr<ModelHandler> model_handler_;
};

#endif