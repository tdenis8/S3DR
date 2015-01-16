#include "view.hpp"

#include "utility/custom_exp.hpp"

#include "model/model.hpp"
#include "operator/operator.hpp"
#include "view_adapter.hpp"
#include "open_gl/open_gl_view_adapter.hpp"

View::View()
    : Subject()
    , MouseEventsDispatcher()
    , KeyboardEventsDispatcher()
    , camera_()
    , lights_manager_()
    , view_settings_()
    , selection_set_()
    , view_adapter_(nullptr)
    , model_(nullptr)
    , operator_(nullptr)
{
    try
    {
        view_adapter_.reset(new OpenGLViewAdapter(*this));
    }
    catch(CustomExp e)
    {
        throw e;
    }

    // Inform observers to set default width and height
    Emit(ViewEvent::WINDOW_RESIZE, WindowResizeInfo(800, 600));

    // Inform observers to apply all viewer settings
    Emit(ViewEvent::VIEWER_SETTINGS_CHANGE);
}

View::~View()
{
}

Camera& View::GetCamera()
{
    return camera_;
}

ViewSettings& View::GetViewSettings()
{
    return view_settings_;
}

void View::AttachModel(Model* model)
{
    if(model == nullptr)
    {
        return;
    }
    if(model_ != nullptr)
    {
        DetachModel();
    }
    model_ = model;
    Emit(ViewEvent::ATTACH_MODEL, AttachModelInfo(*model_));
}

void View::DetachModel()
{
    if(model_ != nullptr)
    {
        model_ = nullptr;
    }
    Emit(ViewEvent::DETACH_MODEL);
}

Model* View::GetModel()
{
    return model_;
}

void View::AttachOperator(Operator* opr)
{
    operator_ = opr;
    MouseEventsDispatcher::AttachOperator(operator_);
    KeyboardEventsDispatcher::AttachOperator(operator_);
}

void View::DetachOperator()
{
    operator_ = nullptr;
    MouseEventsDispatcher::DetachOperator();
    KeyboardEventsDispatcher::DetachOperator();
}

Operator* View::GetOperator()
{
    return operator_;
}

void View::Redraw()
{
    if(view_adapter_)
    {
        view_adapter_->Render();
    }
}

void View::WindowResize(int width, int height)
{
    camera_.SetAspectRatio(width, height);
    Emit(ViewEvent::WINDOW_RESIZE, WindowResizeInfo(width, height));
}

void View::SetBackgroundColor(const glm::vec3& background_color)
{
    view_settings_.background_color = background_color;
    Emit(ViewEvent::VIEWER_SETTINGS_CHANGE);
}

SelectionSet& View::GetSelectionSet()
{
    return selection_set_;
}

float View::ScreenDepthAt(int x, int y) const
{
    return view_adapter_->ScreenDepthAt(x, y);
}