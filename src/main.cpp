#include<iostream>
#include<Windows.h>
#include<glm.hpp>
#include<gtc/matrix_transform.hpp>
#include<array>
#include"app.hpp"
#include"light_cube.hpp"
#include"cube.hpp"
#include"vertex_array.hpp"
#include"shader.hpp"
#include<math.h>
#include<vector>

int main()
{

	constexpr float windowWidth = 800.f;
	constexpr float windowHeight = 600.f;
	auto app = graphic::app::create("shader", windowWidth, windowHeight, 60.f);

	std::vector<glm::vec3> lightPos{
		glm::vec3{ 0.f,0.f,0.f },
		glm::vec3{ 5.f,5.f,5.f },
		glm::vec3{ 0.f,7.f,0.f }
	};

	std::vector<glm::vec3> cubePos{
		glm::vec3{ 0.f,-2.f,0.f },
		glm::vec3{ 0.f,2.f,0.f },
		glm::vec3{ 2.f,0.f,0.f },
		glm::vec3{ -2.f,0.f,0.f },
		glm::vec3{ 0.f,0.f,-2.f },
		glm::vec3{ 0.f,0.f,2.f },

		glm::vec3{ 4.f,4.f,-4.f },
		glm::vec3{ -4.f,4.f,-4.f },
		glm::vec3{ 4.f,-4.f,-4.f },
		glm::vec3{ -4.f,-4.f,-4.f },
		glm::vec3{ 4.f,4.f,4.f },
		glm::vec3{ -4.f,4.f,4.f },
		glm::vec3{ 4.f,-4.f,4.f },
		glm::vec3{ -4.f,-4.f,4.f },
	};

	//vec3からmat4へ
	constexpr auto to_mat4 = [](const glm::vec3& vec)->glm::mat4 {
		return glm::translate(glm::mat4{ 1.f }, vec);
	};

	std::vector<glm::mat4> lightModel{};
	for (const auto& light : lightPos)
		lightModel.emplace_back(glm::scale(to_mat4(light), glm::vec3(0.2f)));

	std::vector<glm::mat4> cubeModel{};
	for (const auto& c : cubePos)
		cubeModel.emplace_back(to_mat4(c));


	std::vector<graphic::light_cube> lightCube(sizeof(lightPos));

	std::vector<graphic::cube> cube(sizeof(cubePos));
	for (auto& c:cube) {
		c.set_vec3f("material.ambient", 1.f, 0.5f, 0.31f);
		c.set_vec3f("material.diffuse", 1.f, 0.5f, 0.31f);
		c.set_vec3f("material.specular", 0.5f, 0.5f, 0.5f);
		c.set_float("material.shininess", 64.f);

		for (size_t i = 0; i < lightPos.size(); i++)
		{
			c.set_vec3f("light[" + std::to_string(i) + "].ambient", 0.2f, 0.2f, 0.2f);
			c.set_vec3f("light[" + std::to_string(i) + "].diffuse", 0.5f, 0.5f, 0.5f);
			c.set_vec3f("light[" + std::to_string(i) + "].specular", 1.f, 1.f, 1.f);

			c.set_float("light[" + std::to_string(i) + "].constant", 1.f);
			c.set_float("light[" + std::to_string(i) + "].liner", 0.09f);
			c.set_float("light[" + std::to_string(i) + "].quadratic", 0.032f);
		}
	}

	const auto projectionMat = glm::perspective(
		glm::radians(45.f), // ズームの度合い(通常90～30)
		(GLfloat)windowWidth / (GLfloat)windowHeight,		// アスペクト比
		0.1f,		// 近くのクリッピング平面
		100.0f		// 遠くのクリッピング平面
	);

	//視点の角度
	auto rot = 0.f;
	constexpr auto deltaRot = 0.01f;

	while (app->loop()) {
		app->begin_drawing();

		glEnable(GL_DEPTH_TEST);
		glClearColor(0.2, 0.2, 0.2, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		rot += deltaRot;
		auto viewPos = glm::vec3(20.0 * std::sin(rot), 0.0, 20.0 * std::cos(rot));
		auto viewMat = glm::lookAt(
			viewPos,
			glm::vec3(0.0, 0.0, 0.0),
			glm::vec3(0.0, 1.0, 0.0)
		);
		auto pv = projectionMat * viewMat;

		for (size_t i = 0; i < lightPos.size(); i++)
		{
			auto lightPosMVP = pv * lightModel[i];
			lightCube[i].set_MVP(&lightPosMVP[0][0]);
			lightCube[i].draw();
		}
		
		for (size_t i = 0; i < cubeModel.size(); i++)
		{
			cubeModel[i] = glm::rotate(cubeModel[i], deltaRot, glm::vec3(0.2, 0.1, 0.05));
			cube[i].set_mat4f("PV", &pv[0][0]);
			cube[i].set_mat4f("model", &cubeModel[i][0][0]);
			cube[i].set_vec3f("viewPos", viewPos);

			for (size_t j = 0; j < lightPos.size(); j++) {
				cube[i].set_vec3f("light[" + std::to_string(j) + "].position", lightPos[j]);
			}
			

			cube[i].draw();
		}
	
		app->finish_drawing();
	};

	return 0;

}