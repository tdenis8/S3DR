#include "open_gl_view_adapter.hpp"

#include "utility/custom_exp.hpp"

#include "view/view.hpp"

OpenGLInitazer::OpenGLInitazer()
{
    glewExperimental = GL_TRUE;
    // Initialize GLEW
    if(glewInit() != GLEW_OK)
    {
        std::string error = std::string("*** Failed to initialize GLEW");
        throw CustomExp(error);
    }

    if(!GLEW_VERSION_3_3)
    {
        std::string error("*** OpenGL 3.3 API is not available.");
        throw CustomExp(error);
    }

    // Common settings
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClearDepthf(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1.0f);
    glEnable(GL_DEPTH_CLAMP);

    glEnable(GL_MULTISAMPLE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

OpenGLViewAdapter::OpenGLViewAdapter(View &view) try : ViewAdapter(view),
                                                       Observer(),
                                                       scene_settings_(),
                                                       scene_renderer_(scene_settings_),
                                                       lights_handler_(scene_renderer_, camera_),
                                                       selection_set_(view.GetSelectionSet()),
                                                       model_handler_(nullptr)
{
    view_.Observe(
        ViewEvent::ATTACH_MODEL, std::bind(&OpenGLViewAdapter::AttachModel, this, std::placeholders::_1), this);

    view_.Observe(
        ViewEvent::DETACH_MODEL, std::bind(&OpenGLViewAdapter::DetachModel, this, std::placeholders::_1), this);

    view_.Observe(
        ViewEvent::WINDOW_RESIZE, std::bind(&OpenGLViewAdapter::WindowResize, this, std::placeholders::_1), this);

    // View settings changes
    view_.Observe(ViewEvent::VIEWER_SETTINGS_CHANGE,
                  std::bind(&OpenGLViewAdapter::ViewerSettingsChange, this, std::placeholders::_1),
                  this);

    // Selections
    selection_set_.Observe(SelectionSetEvent::CALCULATE_SELECTION,
                           std::bind(&OpenGLViewAdapter::CalculateSelection, this, std::placeholders::_1),
                           this);
}
catch(CustomExp e)
{
    throw e;
}

OpenGLViewAdapter::~OpenGLViewAdapter()
{
    view_.RemoveObservers(this);
    selection_set_.RemoveObservers(this);
}

void OpenGLViewAdapter::AttachModel(const EventInfo &info)
{
    const AttachModelInfo &am_info = dynamic_cast<const AttachModelInfo &>(info);
    model_handler_.reset(new ModelHandler(am_info.ModelRef(), scene_renderer_));
}

void OpenGLViewAdapter::DetachModel(const EventInfo &info)
{
    model_handler_.reset();
}

void OpenGLViewAdapter::WindowResize(const EventInfo &info)
{
    const WindowResizeInfo &wr_info = dynamic_cast<const WindowResizeInfo &>(info);
    scene_settings_.SetWidthHeight(wr_info.Width(), wr_info.Height());
}

void OpenGLViewAdapter::ViewerSettingsChange(const EventInfo &info)
{
    scene_settings_.SetBackgroundColor(view_settings_.background_color);
}

void OpenGLViewAdapter::CalculateSelection(const EventInfo &info)
{
    if(!model_handler_)
    {
        return;
    }

    const SelectionInfo &s_info = dynamic_cast<const SelectionInfo &>(info);
    scene_renderer_.SelectionRender();
    SelectionTexture &selection_texture = scene_renderer_.GetSelectionTexture();
    selection_set_.SetSelectionData(selection_texture.GetSelectionData(s_info.X(), s_info.Y()));
}

void OpenGLViewAdapter::Render()
{
    if(model_handler_)
    {
        scene_renderer_.Render(camera_.GetViewMatrix(), camera_.GetProjectionMatrix());
    }
}

float OpenGLViewAdapter::ScreenDepthAt(int x, int y) const
{
    return scene_renderer_.ScreenDepthAt(x, y);
}