#include<iostream>

#include<Windows.h>

#include"shader.hpp"

#include<glm.hpp>
#include<gtc/matrix_transform.hpp>

#include<array>

#include"vertex_array.hpp"
#include"shader.hpp"

#include"app.hpp"


int main()
{

	auto app = graphic::app::create("aa", 800.f, 600.f, 60.f);

	auto shader1 = graphic::shader{ "ShaderFile/cube_shader.vert" ,"ShaderFile/shader.frag" };

	std::array vert{
		glm::vec3{0.5f,0.5f,0.f},glm::vec3{1.f,0.5f,0.5f},
		glm::vec3{-0.5f,0.5f,0.f},glm::vec3{1.f,0.f,0.f},
		glm::vec3{-0.5f,-0.5f,0.f},glm::vec3{0.f,1.f,0.f},
		glm::vec3{0.5f,-0.5f,0.f},glm::vec3{0.f,0.f,1.f},
		glm::vec3{0.5f,0.5f,-0.5f},glm::vec3{1.f,1.f,0.f},
		glm::vec3{-0.5f,0.5f,-0.5f},glm::vec3{0.f,1.f,1.f},
		glm::vec3{-0.5f,-0.5f,-0.5f},glm::vec3{1.f,0.f,1.f},
		glm::vec3{0.5f,-0.5f,-0.5f},glm::vec3{0.5f,0.5f,1.f},
		
	};
	std::array<unsigned int,36> index{
		0,1,2,0,2,3,
		0,1,5,0,5,4,
		1,2,6,1,6,5,
		4,5,6,4,6,7,
		7,6,2,7,2,3,
		0,4,7,0,7,3
	};
	auto vao = graphic::vertex_array{ std::move(vert),std::move(index)};

	auto posLocation = shader1.get_attribute_location("pos");
	vao.set_attribute_location(posLocation, 3, GL_FALSE, 6, 0);

	auto colorLocation = shader1.get_attribute_location("color");
	vao.set_attribute_location(colorLocation, 3, GL_FALSE, 6, 3);

	glm::mat4 model{ 1.0 };
	constexpr float deltaRot = 0.01f;

	while (app->loop()) {
		app->begin_drawing();

		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader1.use();

		model = glm::rotate(model, deltaRot, glm::vec3(0.2,0.1, 0.05));
		
		auto mvpLoc = shader1.get_uniform_location("MVP");
		glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, &model[0][0]);

		vao.draw(GL_TRIANGLES);

		app->finish_drawing();
	};

	return 0;

}