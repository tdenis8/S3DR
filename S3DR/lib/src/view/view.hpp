#ifndef _VIEW_H_
#define _VIEW_H_

#include "utility/subject.hpp"

#include "mouse_events_dispatcher.hpp"
#include "keyboard_events_dispatcher.hpp"
#include "lights_manager.hpp"

#include "camera.hpp"
#include "selection_set.hpp"

#include <glm/glm.hpp>
#include <memory>

// Forward declarations
class Model;
class Operator;
class ViewAdapter;

enum class ViewEvent : unsigned int
{
    ATTACH_MODEL,
    DETACH_MODEL,
    WINDOW_RESIZE,
    // View settings changes
    VIEWER_SETTINGS_CHANGE
};

struct ViewSettings
{
    glm::vec3 background_color = glm::vec3(1.0, 1.0, 0.0);
};

class AttachModelInfo : public EventInfo
{
    public:
    AttachModelInfo(Model& model) : EventInfo(), model(model)
    {
    }

    Model& ModelRef() const
    {
        return model;
    }

    private:
    Model& model;
};

class WindowResizeInfo : public EventInfo
{
    public:
    WindowResizeInfo(int width, int height) : EventInfo(), width(width), height(height)
    {
    }

    const int& Width() const
    {
        return width;
    }
    const int& Height() const
    {
        return height;
    }

    private:
    int width;
    int height;
};

class View : public Subject<ViewEvent>, public MouseEventsDispatcher, public KeyboardEventsDispatcher
{
    friend class CameraOperator;
    friend class ViewAdapter;

    public:
    View();
    View(const View&) = delete;
    View& operator=(const View&) = delete;
    virtual ~View();

    void AttachModel(Model* model);
    void DetachModel();
    Model* GetModel();

    void AttachOperator(Operator* opr);
    void DetachOperator();
    Operator* GetOperator();

    void Redraw();

    void WindowResize(int width, int height);
    void SetBackgroundColor(const glm::vec3& background_color);

    SelectionSet& GetSelectionSet();

    protected:
    Camera& GetCamera();
    ViewSettings& GetViewSettings();

    float ScreenDepthAt(int x, int y) const;

    private:
    Camera camera_;
    LightsManager lights_manager_;
    ViewSettings view_settings_;
    SelectionSet selection_set_;

    std::unique_ptr<ViewAdapter> view_adapter_;

    Model* model_;
    Operator* operator_;
};

#endif