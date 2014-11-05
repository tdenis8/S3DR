#include "open_gl_context.hpp"

#include "utility/custom_exp.hpp"

#include <iostream>
#include <string>

/// Callback functions
void ErrorCallback(int error, const char* description)
{
    std::cerr << "GLFW error: " << description << std::endl;
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    OpenGLContext* open_gl_context = static_cast<OpenGLContext*>(glfwGetWindowUserPointer(window));
    if(!open_gl_context->mouse_button_callback)
    {
        return;
    }
    open_gl_context->mouse_button_callback(button, action);
}

void MousePosCallback(GLFWwindow* window, double x, double y)
{
    OpenGLContext* open_gl_context = static_cast<OpenGLContext*>(glfwGetWindowUserPointer(window));
    if(!open_gl_context->mouse_pos_callback)
    {
        return;
    }
    open_gl_context->mouse_pos_callback(x, y);
}

void MouseWheelCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    OpenGLContext* open_gl_context = static_cast<OpenGLContext*>(glfwGetWindowUserPointer(window));
    if(!open_gl_context->mouse_wheel_callback)
    {
        return;
    }
    open_gl_context->mouse_wheel_callback(yoffset);
}

void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    OpenGLContext* open_gl_context = static_cast<OpenGLContext*>(glfwGetWindowUserPointer(window));
    if(!open_gl_context->keyboard_callback)
    {
        return;
    }
    open_gl_context->keyboard_callback(key, action);
}

void WindowSizeCallback(GLFWwindow* window, int width, int height)
{
    OpenGLContext* open_gl_context = static_cast<OpenGLContext*>(glfwGetWindowUserPointer(window));
    if(!open_gl_context->windows_size_callback)
    {
        return;
    }
    open_gl_context->windows_size_callback(width, height);
}

/// OpenGLContext class
OpenGLContext::OpenGLContext() : OpenGLContext("OpenGLContext")
{
}

OpenGLContext::OpenGLContext(const std::string& title) : glfw_window(nullptr)
{
    InitGLFW(800, 600, title);
    InitGLFWCallbacks();
}

OpenGLContext::~OpenGLContext()
{
    if(glfw_window)
    {
        glfwDestroyWindow(glfw_window);
    }
    glfwTerminate();
}

void OpenGLContext::InitGLFW(unsigned int width, unsigned int height, const std::string& title)
{
    glfwSetErrorCallback(ErrorCallback);

    if(!glfwInit())
    {
        std::string error("*** Failed to initialize GLFW.");
        throw CustomExp(error);
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);

    glfw_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if(!glfw_window)
    {
        std::string error("*** Failed to open GLFW window.");
        throw CustomExp(error);
    }

    glfwMakeContextCurrent(glfw_window);
}

void OpenGLContext::InitGLFWCallbacks()
{
    glfwSetWindowUserPointer(glfw_window, this);
    glfwSetMouseButtonCallback(glfw_window, MouseButtonCallback);
    glfwSetCursorPosCallback(glfw_window, MousePosCallback);
    glfwSetScrollCallback(glfw_window, MouseWheelCallback);
    glfwSetKeyCallback(glfw_window, KeyboardCallback);
    glfwSetWindowSizeCallback(glfw_window, WindowSizeCallback);
}

void OpenGLContext::Loop()
{
    while(!glfwWindowShouldClose(glfw_window))
    {
        redraw_callback();
        glfwSwapBuffers(glfw_window);
        glfwPollEvents();
    }
}
