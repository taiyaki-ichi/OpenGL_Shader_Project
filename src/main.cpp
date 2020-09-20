#include<iostream>

#include<Windows.h>
#include<glew.h>

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "glew32.lib")

#include"windows.hpp"
#include"shader.hpp"

#include<glm.hpp>

#include<array>

#include"vertex_array.hpp"

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

	if (glewInit())
	{
		std::cout << "failed glewInit";
		return 0;
	}


	auto vertS = shader::compile("ShaderFile/shader.vert", GL_VERTEX_SHADER);
	auto fragS = shader::compile("ShaderFile/shader.frag", GL_FRAGMENT_SHADER);

	if (!vertS || !fragS) {
		std::cout << "failed com";
		return 0;
	}

	auto sha = shader::create_shaderprogram(vertS.value(), fragS.value());

	std::array vert{
		glm::vec3{0.f,0.5f,0.f},
		glm::vec3{-0.5f,-0.5f,0.f},
		glm::vec3{0.5f,-0.5f,0.f}
	};

	std::array<unsigned int,3> index{
		0,1,2
	};
	auto posLocation = glGetAttribLocation(sha.value(), "pos");

	auto vao = graphics::vertex_array{ std::move(vert),std::move(index),posLocation };


	while (windows::process_message()) {

		//•`ŽÊ—Ìˆæ‚ðŽw’è
		wglMakeCurrent(pair.value().first, pair.value().second);

		
		glUseProgram(sha.value());

		glClear(GL_COLOR_BUFFER_BIT);

		glColor3f(1.0, 0.0, 0.0);

		vao.bind_and_draw(GL_TRIANGLES);
		
		glFlush();
		SwapBuffers(pair.value().first);
		wglMakeCurrent(NULL, NULL);

	};

	windows::shutdown(hwnd.value(), pair.value().first, pair.value().second);

	return 0;




	return 0;

}