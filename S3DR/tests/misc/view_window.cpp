#include "view_window.hpp"

#include "utility/custom_exp.hpp"

#include "operator/camera_operator.hpp"
#include "view/view.hpp"

#include "combined_operator.hpp"
#include "open_gl_context.hpp"

#include <memory>
#include <iostream>
void ViewWindow(Model * model, const std::string & title) {
        OpenGLContext gl_context(title);
        std::unique_ptr<View> view{new View()};
        view->AttachModel(model);
        view->SetBackgroundColor(glm::vec3(0.9, 0.9, 0.9));

        std::unique_ptr<CombinedOperator> combined_operator{new CombinedOperator(*view)};
        view->AttachOperator(combined_operator.get());
        
        gl_context.SetMouseButtonCallback(std::bind(&View::OnMouseButton, view.get(), std::placeholders::_1, std::placeholders::_2));
        gl_context.SetMousePosCallback(std::bind(&View::OnMouseMove, view.get(), std::placeholders::_1, std::placeholders::_2));
        gl_context.SetMouseWheelCallback(std::bind(&View::OnMouseWheel, view.get(), std::placeholders::_1));
        gl_context.SetKeyboardCallback(std::bind(&View::OnKeyboardKey, view.get(), std::placeholders::_1, std::placeholders::_2));
        gl_context.SetWindowSizeCallback(std::bind(&View::WindowResize, view.get(), std::placeholders::_1, std::placeholders::_2));

        // Enters into loop
        gl_context.Redraw(std::bind(&View::Redraw, view.get()));

        view->DetachModel();
}

void ViewWindow(Model * model, const std::string & title, std::function<void(void)> cb_function){
        OpenGLContext gl_context(title);
        std::unique_ptr<View> view{new View()};
        view->AttachModel(model);
        view->SetBackgroundColor(glm::vec3(0.8, 0.8, 0.8));

        std::unique_ptr<CameraOperator> camera_operator{new CameraOperator(*view)};
        view->AttachOperator(camera_operator.get());
        
        gl_context.SetMouseButtonCallback(std::bind(&View::OnMouseButton, view.get(), std::placeholders::_1, std::placeholders::_2));
        gl_context.SetMousePosCallback(std::bind(&View::OnMouseMove, view.get(), std::placeholders::_1, std::placeholders::_2));
        gl_context.SetMouseWheelCallback(std::bind(&View::OnMouseWheel, view.get(), std::placeholders::_1));
        gl_context.SetKeyboardCallback(std::bind(&View::OnKeyboardKey, view.get(), std::placeholders::_1, std::placeholders::_2));
        gl_context.SetWindowSizeCallback(std::bind(&View::WindowResize, view.get(), std::placeholders::_1, std::placeholders::_2));

        auto view_redraw = std::bind(&View::Redraw, view.get());
        // Enters into loop
        gl_context.Redraw([&]() { cb_function(); view_redraw(); } );

        view->DetachModel();
}