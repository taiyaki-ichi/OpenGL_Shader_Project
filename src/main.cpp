#include<iostream>

#include<Windows.h>

#include"shader.hpp"

#include<glm.hpp>
#include<gtc/matrix_transform.hpp>

#include<array>

#include"vertex_array.hpp"
#include"shader.hpp"

#include"app.hpp"

#include"rainbow_cube.hpp"
#include"light_cube.hpp"

int main()
{

	constexpr float windowWidth = 800.f;
	constexpr float windowHeight = 600.f;
	auto app = graphic::app::create("aa", windowWidth, windowHeight, 60.f);

	auto rainbow = graphic::rainbow_cube{};
	auto light = graphic::light_cube{};

	glm::mat4 lightPos{ 1.f };
	lightPos = glm::translate(lightPos, glm::vec3{ 0.f,2.f,0.f });
	lightPos = glm::scale(lightPos, glm::vec3(0.5f));


	glm::mat4 model{ 1.0 };
	constexpr float deltaRot = 0.01f;

	auto projectionMat = glm::perspective(
		glm::radians(90.f), // ズームの度合い(通常90～30)
		(GLfloat)windowWidth / (GLfloat)windowHeight,		// アスペクト比
		0.1f,		// 近くのクリッピング平面
		100.0f		// 遠くのクリッピング平面
	);

	auto viewMat = glm::lookAt(
		glm::vec3(5.0, 0.0, 0.0), // ワールド空間でのカメラの座標
		glm::vec3(0.0, 2.0, 0.0), // 見ている位置の座標
		glm::vec3(0.0, 1.0, 0.0)  // 上方向を示す。(0,1.0,0)に設定するとy軸が上になります
	);

	

	while (app->loop()) {
		app->begin_drawing();

		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		model = glm::rotate(model, deltaRot, glm::vec3(0.2,0.1, 0.05));
		auto tmp = projectionMat * viewMat * model;
		//rainbow.draw();
		rainbow.set_MVP(&tmp[0][0]);
		rainbow.draw();
		
		lightPos = glm::rotate(lightPos, deltaRot, glm::vec3(0.2, 0.1, 0.05));
		auto aa = projectionMat * viewMat * lightPos;
		//light.draw();
		light.set_MVP(&aa[0][0]);
		light.draw();
	

		app->finish_drawing();
	};

	return 0;

}