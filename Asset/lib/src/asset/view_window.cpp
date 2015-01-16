#include "view_window.hpp"

#include "utility/custom_exp.hpp"

#include "operator/camera_operator.hpp"
#include "view/view.hpp"

#include "combined_operator.hpp"
#include "open_gl_context.hpp"

#include <memory>

// FPSCounter class
FPSCounter::FPSCounter(TextObject& text_object, unsigned int text_id) : text_object(text_object), text_id(text_id)
{
    last_time = glfwGetTime();
    num_frames = 0;
}

void FPSCounter::print()
{
    // Measure speed
    double currentTime = glfwGetTime();
    num_frames++;
    if(currentTime - last_time >= 1.0)
    {
        text_object.UpdateDynamicText(text_id, std::to_wstring(1000.0 / double(num_frames)) + L" ms/frame");
        num_frames = 0;
        last_time += 1.0;
    }
}

static void do_nothing()
{
}

void ViewWindow(Model& model, const std::string& title, bool show_fps_counter, const std::string& fps_counter_font_path)
{
    ViewWindow(model, title, do_nothing, show_fps_counter, fps_counter_font_path);
}

void ViewWindow(Model& model,
                const std::string& title,
                std::function<void(void)> cb_function,
                bool show_fps_counter,
                const std::string& fps_counter_font_path)
{
    OpenGLContext gl_context(title);
    std::unique_ptr<View> view(new View());
    view->AttachModel(&model);
    view->SetBackgroundColor(glm::vec3(0.8, 0.8, 0.8));

    std::unique_ptr<CameraOperator> camera_operator(new CameraOperator(*view));
    view->AttachOperator(camera_operator.get());

    gl_context.SetMouseButtonCallback(
        std::bind(&View::OnMouseButton, view.get(), std::placeholders::_1, std::placeholders::_2));
    gl_context.SetMousePosCallback(
        std::bind(&View::OnMouseMove, view.get(), std::placeholders::_1, std::placeholders::_2));
    gl_context.SetMouseWheelCallback(std::bind(&View::OnMouseWheel, view.get(), std::placeholders::_1));
    gl_context.SetKeyboardCallback(
        std::bind(&View::OnKeyboardKey, view.get(), std::placeholders::_1, std::placeholders::_2));
    gl_context.SetWindowSizeCallback(
        std::bind(&View::WindowResize, view.get(), std::placeholders::_1, std::placeholders::_2));

    // Enters into loop
    if(show_fps_counter and fps_counter_font_path.size() > 0)
    {
        std::unique_ptr<ModelManager> model_manager(new ModelManager(model));

        auto text_id = model_manager->GenerateTextObject(nullptr, "");
        TextObject& text_object = model_manager->GetTextObject(text_id);

        text_object.SetFontNameAndFontSize(fps_counter_font_path, 24);
        unsigned int fps_text_id = text_object.AddDynamicText(L"", glm::vec4(0, 0, 1, 0), 10, 30);

        FPSCounter fps_counter(text_object, fps_text_id);

        auto print_fps = std::bind(&FPSCounter::print, &fps_counter);
        auto view_redraw = std::bind(&View::Redraw, view.get());

        gl_context.Redraw([&]()
                          {
                              cb_function();
                              print_fps();
                              view_redraw();
                          });
    }
    else
    {
        auto view_redraw = std::bind(&View::Redraw, view.get());
        gl_context.Redraw([&]()
                          {
                              cb_function();
                              view_redraw();
                          });
    }

    view->DetachModel();
}
