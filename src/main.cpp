#include<iostream>

#include<Windows.h>

#include"shader.hpp"

#include<glm.hpp>

#include<array>

#include"vertex_array.hpp"
#include"shader.hpp"

#include"app.hpp"


int main()
{

	auto app = graphic::app::create("aa", 800.f, 600.f, 60.f);

	auto s = graphic::shader{ "ShaderFile/shader.vert" ,"ShaderFile/shader.frag" };

	std::array vert{
		glm::vec3{0.f,0.5f,0.f},
		glm::vec3{-0.5f,-0.5f,0.f},
		glm::vec3{0.5f,-0.5f,0.f}
	};

	std::array<unsigned int,3> index{
		0,1,2
	};
	auto posLocation = s.get_attribute_location("pos");

	auto vao = graphic::vertex_array{ std::move(vert),std::move(index),posLocation };

	while (app->loop()) {

		//•`ŽÊ—Ìˆæ‚ðŽw’è
		//wglMakeCurrent(pair.value().first, pair.value().second);
		app->begin_drawing();

		s.use();

		glClear(GL_COLOR_BUFFER_BIT);

		glColor3f(1.0, 0.0, 0.0);

		vao.bind_and_draw(GL_TRIANGLES);
		
		
		app->finish_drawing();
	};

	return 0;

}