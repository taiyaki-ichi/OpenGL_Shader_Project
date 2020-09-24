#include<iostream>

#include<Windows.h>

#include<glm.hpp>
#include<gtc/matrix_transform.hpp>

#include<array>

#include"vertex_array.hpp"
#include"shader.hpp"

#include"app.hpp"

#include"light_cube.hpp"
#include"cube.hpp"

int main()
{

	constexpr float windowWidth = 800.f;
	constexpr float windowHeight = 600.f;
	auto app = graphic::app::create("aa", windowWidth, windowHeight, 60.f);

	auto light = graphic::light_cube{};
	glm::mat4 lightPos{ 1.f };
	lightPos = glm::translate(lightPos, glm::vec3{ 1.2f,1.f,2.f });
	lightPos = glm::scale(lightPos, glm::vec3(0.2f));

	auto cube = graphic::cube{};
	cube.set_cube_color(1.f, 0.5f, 0.31f);
	cube.set_light_color(1.f, 1.f, 1.f);
	glm::mat4 cubePos{ 1.f };
	//cubePos = glm::translate(cubePos, glm::vec3{ 0.f,0.f,0.f });
	cubePos = glm::scale(cubePos, glm::vec3(0.5f));

	constexpr float deltaRot = 0.01f;

	auto projectionMat = glm::perspective(
		glm::radians(45.f), // ズームの度合い(通常90～30)
		(GLfloat)windowWidth / (GLfloat)windowHeight,		// アスペクト比
		0.1f,		// 近くのクリッピング平面
		100.0f		// 遠くのクリッピング平面
	);

	auto viewMat = glm::lookAt(
		glm::vec3(0.0, 0.0, 5.0), // ワールド空間でのカメラの座標
		glm::vec3(0.0, 0.0, 0.0), // 見ている位置の座標
		glm::vec3(0.0, 1.0, 0.0)  // 上方向を示す。(0,1.0,0)に設定するとy軸が上になります
	);

	

	while (app->loop()) {
		app->begin_drawing();

		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//lightPos= glm::rotate(lightPos, deltaRot, glm::vec3(0.2, 0.1, 0.05));
		auto lightPosMVP = projectionMat * viewMat * lightPos;
		light.set_MVP(&lightPosMVP[0][0]);
		light.draw();
		
		cubePos = glm::rotate(cubePos, deltaRot, glm::vec3(0.2, 0.1, 0.05));
		auto cubePosMVP = projectionMat * viewMat * cubePos;
		cube.set_MVP(&cubePos[0][0]);
		cube.draw();
	
		app->finish_drawing();
	};

	return 0;

}