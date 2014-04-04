#include "open_gl_context.hpp"

#include "utility/custom_exp.hpp"

#include <string>
#include <GL/glew.h>
#include <GL/glfw.h>

#include <iostream>

static OpenGLContext * _context = NULL;

static void MouseButtonCB(int button, int state){
	_context->MouseButtonCallback(button, state);
}

static void MousePosCB(int x, int y){
	_context->MousePosCallback(x, y);
}

static void MouseWheelCB(int delta){
	_context->MouseWheelCallback(delta);
}

static void KeyboardCB(int key, int state){
	_context->KeyboardCallback(key, state);
}

static void WindowSizeCB(int width, int height){
	_context->WindowSizeCallback(width, height);
}

static void InitGLFW(unsigned int width, unsigned int height,const char* title){
	// Initialise GLFW
	if( !glfwInit() ){
	    std::string error("*** Failed to initialize GLFW.");
	    throw CustomExp(error);
	}

	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	if( !glfwOpenWindow( width, height, 0,0,0,0, 32,0, GLFW_WINDOW ) )
	{
		std::string error("*** Failed to open GLFW window.");
		glfwTerminate();
		throw CustomExp(error);
	}
	
	glfwSetWindowTitle(title);

}

static void RegisterGLFWCallbacks(OpenGLContext * context){
	if (!context) {
	    std::string error("*** Failed to set GLFW callbacks.");
	    throw CustomExp(error);
    }

    _context = context;

	glfwSetMouseButtonCallback(MouseButtonCB);
	glfwSetMousePosCallback(MousePosCB);
	glfwSetMouseWheelCallback(MouseWheelCB);
	glfwSetKeyCallback(KeyboardCB);
	glfwSetWindowSizeCallback(WindowSizeCB);
}

static void GLFWTerminate(){
	glfwTerminate();
}

///**********************************************************
/// OpenGLContext class
///**********************************************************
OpenGLContext::OpenGLContext():
	previous_delta(0)
{ 
	InitGLFW(800, 600, "Fenix3D tests");
	RegisterGLFWCallbacks(this);
}

OpenGLContext::OpenGLContext(const std::string & title):
	previous_delta(0)
{
	InitGLFW(800, 600, title.c_str());
	RegisterGLFWCallbacks(this);
}

OpenGLContext::~OpenGLContext() { 
	GLFWTerminate();
}

void OpenGLContext::Loop(){
	double last_time = glfwGetTime();
	int number_of_frames = 0;

	while(glfwGetWindowParam(GLFW_OPENED)){
		redraw_callback();
		glfwSwapBuffers();

		double current_time = glfwGetTime();
		number_of_frames++;
		// Print every five seconds
		if ( current_time - last_time >= 1.0 ){ 
			// printf and reset timer
			std::cout<<1000.0/double(number_of_frames)<<" ms/frame"<<std::endl;
			number_of_frames = 0;
			last_time += 1.0;
		}
	}
}

void OpenGLContext::MouseButtonCallback(int button, int state){
	if(!mouse_button_callback) {
		return;
	}
	mouse_button_callback(button, state);
}

void OpenGLContext::MousePosCallback(int x, int y){
	if(!mouse_pos_callback) {
		return;
	}
	mouse_pos_callback(x, y);
}

void OpenGLContext::MouseWheelCallback(int delta){
	if(!mouse_wheel_callback) {
		return;
	}

	mouse_wheel_callback(delta-previous_delta);
	previous_delta = delta;
}

void OpenGLContext::KeyboardCallback(int key, int state){
	if(!keyboard_callback) {
		return;
	}
	keyboard_callback(key, state);
}

void OpenGLContext::WindowSizeCallback(int width, int height){
	if(!windows_size_callback) {
		return;
	}
	windows_size_callback(width, height);
}