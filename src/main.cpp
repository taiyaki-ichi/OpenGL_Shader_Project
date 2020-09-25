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
	auto app = graphic::app::create("aa", windowWidth, windowHeight, 60.f);

	auto light = graphic::light_cube{};
	auto lightPos = glm::vec3{ 0.f,0.f,0.f };
	glm::mat4 lightModel{ 1.f };
	lightModel = glm::translate(lightModel, lightPos);
	lightModel = glm::scale(lightModel, glm::vec3(0.2f));

	std::array cubeModel{
		glm::translate(glm::mat4{1.f},glm::vec3{ 0.f,-2.f,0.f }),
		glm::translate(glm::mat4{1.f},glm::vec3{ 0.f,2.f,0.f }),
		glm::translate(glm::mat4{1.f},glm::vec3{ 2.f,0.f,0.f }),
		glm::translate(glm::mat4{1.f},glm::vec3{ -2.f,0.f,0.f }),
		glm::translate(glm::mat4{1.f},glm::vec3{ 0.f,0.f,-2.f }),
		glm::translate(glm::mat4{1.f},glm::vec3{ 0.f,0.f,2.f }),

		glm::translate(glm::mat4{1.f},glm::vec3{ 4.f,4.f,-4.f }),
		glm::translate(glm::mat4{1.f},glm::vec3{ -4.f,4.f,-4.f }),
		glm::translate(glm::mat4{1.f},glm::vec3{ 4.f,-4.f,-4.f }),
		glm::translate(glm::mat4{1.f},glm::vec3{ -4.f,-4.f,-4.f }),
		glm::translate(glm::mat4{1.f},glm::vec3{ 4.f,4.f,4.f }),
		glm::translate(glm::mat4{1.f},glm::vec3{ -4.f,4.f,4.f }),
		glm::translate(glm::mat4{1.f},glm::vec3{ 4.f,-4.f,4.f }),
		glm::translate(glm::mat4{1.f},glm::vec3{ -4.f,-4.f,4.f }),
	};

	std::vector<graphic::cube> cube{};
	for (int i = 0; i < cubeModel.size(); i++)
		cube.emplace_back(graphic::cube{});

	for (auto& c:cube) {
		c.set_vec3f("material.ambient", 1.f, 0.5f, 0.31f);
		c.set_vec3f("material.diffuse", 1.f, 0.5f, 0.31f);
		c.set_vec3f("material.specular", 0.5f, 0.5f, 0.5f);
		c.set_float("material.shininess", 64.f);

		c.set_vec3f("light.ambient", 0.2f, 0.2f, 0.2f);
		c.set_vec3f("light.diffuse", 0.5f, 0.5f, 0.5f);
		c.set_vec3f("light.specular", 1.f, 1.f, 1.f);

		c.set_float("light.constant", 1.f);
		c.set_float("light.liner", 0.09f);
		c.set_float("light.quadratic", 0.032f);
	}

	auto projectionMat = glm::perspective(
		glm::radians(45.f), // ズームの度合い(通常90～30)
		(GLfloat)windowWidth / (GLfloat)windowHeight,		// アスペクト比
		0.1f,		// 近くのクリッピング平面
		100.0f		// 遠くのクリッピング平面
	);

	auto rot = 0.f;
	constexpr auto deltaRot = 0.01f;

	auto viewMat = glm::lookAt(
		glm::vec3(0.0, 0.0, 10.0), // ワールド空間でのカメラの座標
		glm::vec3(0.0, 0.0, 0.0), // 見ている位置の座標
		glm::vec3(0.0, 1.0, 0.0)  // 上方向を示す。(0,1.0,0)に設定するとy軸が上になります
	);

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

		auto lightPosMVP = pv * lightModel;
		light.set_MVP(&lightPosMVP[0][0]);
		light.draw();
		
		for (int i = 0; i < cubeModel.size(); i++)
		{
			cubeModel[i] = glm::rotate(cubeModel[i], deltaRot, glm::vec3(0.2, 0.1, 0.05));
			cube[i].set_mat4f("PV", &pv[0][0]);
			cube[i].set_mat4f("model", &cubeModel[i][0][0]);
			cube[i].set_vec3f("lightPos", lightPos);
			cube[i].set_vec3f("viewPos", viewPos);
			cube[i].draw();
		}
	
		app->finish_drawing();
	};

	return 0;

}