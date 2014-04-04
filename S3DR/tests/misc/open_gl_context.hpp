#ifndef _OPEN_GL_CONTEST_H_
#define _OPEN_GL_CONTEST_H_

#include <utility>
#include <functional>
#include <string>

class OpenGLContext{
	public:
		OpenGLContext();
        OpenGLContext(const std::string & title);
		~OpenGLContext();

		template <typename T>
        void Redraw(T&& func) {
            redraw_callback = std::forward<T>(func);
            Loop();
        }

        template <typename T>
     	void SetMouseButtonCallback(T&& func){
     		mouse_button_callback = std::forward<T>(func);
     	}

        template <typename T>
     	void SetMousePosCallback(T&& func){
     		mouse_pos_callback = std::forward<T>(func);
     	}

     	template <typename T>
     	void SetMouseWheelCallback(T&& func){
     		mouse_wheel_callback = std::forward<T>(func);
     	}

     	template <typename T>
     	void SetKeyboardCallback(T&& func){
     		keyboard_callback = std::forward<T>(func);
     	}

     	template <typename T>
     	void SetWindowSizeCallback(T&& func){
     		windows_size_callback = std::forward<T>(func);
     	}

     	void MouseButtonCallback(int button, int state);
     	void MousePosCallback(int x, int y);
     	void MouseWheelCallback(int delta);
     	void KeyboardCallback(int key, int state);
     	void WindowSizeCallback(int width, int height);

	private:
		void Loop();

		std::function<void(void)> redraw_callback;
		std::function<void(int,int)> mouse_button_callback;
		std::function<void(int,int)> mouse_pos_callback;
		std::function<void(float)> mouse_wheel_callback;
		std::function<void(int,int)> keyboard_callback;
		std::function<void(int,int)> windows_size_callback;

        int previous_delta;
};

#endif