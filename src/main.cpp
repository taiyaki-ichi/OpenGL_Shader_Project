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
		glm::vec3{0.5f,0.5f,0.f},glm::vec3{1.f,0.f,0.f},
		glm::vec3{-0.5f,0.5f,0.f},glm::vec3{0.f,1.f,0.f},
		glm::vec3{-0.5f,-0.5f,0.f},glm::vec3{0.f,0.f,1.f},
		glm::vec3{0.5f,-0.5f,0.f},glm::vec3{1.f,0.f,1.f},
	};

	std::array<unsigned int,6> index{
		0,1,2,0,2,3
	};

	auto vao = graphic::vertex_array{ std::move(vert),std::move(index)};

	auto posLocation = s.get_attribute_location("pos");
	vao.set_attribute_location(posLocation, 3, GL_FALSE, 6, 0);

	auto colorLocation = s.get_attribute_location("color");
	vao.set_attribute_location(colorLocation, 3, GL_FALSE, 6, 3);


	while (app->loop()) {

		//•`ŽÊ—Ìˆæ‚ðŽw’è
		//wglMakeCurrent(pair.value().first, pair.value().second);
		app->begin_drawing();

		glClear(GL_COLOR_BUFFER_BIT);
		//glColor3f(1.0, 0.0, 0.0);


		s.use();

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		vao.bind_and_draw(GL_TRIANGLES);

		app->finish_drawing();
	};

	return 0;

}