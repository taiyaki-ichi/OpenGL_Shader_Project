#include"windows.hpp"
#include<iostream>

#include<gl/GL.h>
#pragma comment(lib, "OpenGL32.lib")

int main()
{
	auto hwnd = windows::create_window("aaa", 800.f, 600.f);
	
	if (!hwnd) {
		std::cout << "failed window_create";
		return 0;
	}

	auto pair = windows::init_opengl(hwnd.value());
	if (!pair) {
		std::cout << "failed init_opengl";
		return 0;
	}

	while (windows::process_message()) {

		
		wglMakeCurrent(pair.value().first, pair.value().second);
		glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glRectf(-0.5f, -0.5f, 0.5f, 0.5f);

		glFlush();
		SwapBuffers(pair.value().first);
		wglMakeCurrent(NULL, NULL);

	};

	windows::shutdown(hwnd.value(), pair.value().first, pair.value().second);

	return 0;
}