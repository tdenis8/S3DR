#ifndef _OPEN_GL_CONTEST_H_
#define _OPEN_GL_CONTEST_H_

#include <GLFW/glfw3.h>

#include <utility>
#include <functional>
#include <string>

class OpenGLContext
{
    public:
    OpenGLContext();
    OpenGLContext(const std::string& title);
    ~OpenGLContext();

    template <typename T>
    void Redraw(T&& func)
    {
        redraw_callback = std::forward<T>(func);
        Loop();
    }

    template <typename T>
    void SetMouseButtonCallback(T&& func)
    {
        mouse_button_callback = std::forward<T>(func);
    }

    template <typename T>
    void SetMousePosCallback(T&& func)
    {
        mouse_pos_callback = std::forward<T>(func);
    }

    template <typename T>
    void SetMouseWheelCallback(T&& func)
    {
        mouse_wheel_callback = std::forward<T>(func);
    }

    template <typename T>
    void SetKeyboardCallback(T&& func)
    {
        keyboard_callback = std::forward<T>(func);
    }

    template <typename T>
    void SetWindowSizeCallback(T&& func)
    {
        windows_size_callback = std::forward<T>(func);
    }

    private:
    void InitGLFW(unsigned int width, unsigned int height, const std::string& title);
    void InitGLFWCallbacks();
    void Loop();

    friend void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    friend void MousePosCallback(GLFWwindow* window, double x, double y);
    friend void MouseWheelCallback(GLFWwindow* window, double xoffset, double yoffset);
    friend void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    friend void WindowSizeCallback(GLFWwindow* window, int width, int height);

    GLFWwindow* glfw_window;

    std::function<void(void)> redraw_callback;
    std::function<void(int, int)> mouse_button_callback;
    std::function<void(int, int)> mouse_pos_callback;
    std::function<void(float)> mouse_wheel_callback;
    std::function<void(int, int)> keyboard_callback;
    std::function<void(int, int)> windows_size_callback;
};

#endif