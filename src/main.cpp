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

int main()
{

	constexpr float windowWidth = 800.f;
	constexpr float windowHeight = 600.f;
	auto app = graphic::app::create("aa", windowWidth, windowHeight, 60.f);

	auto rainbow = graphic::rainbow_cube{};

	glm::mat4 model{ 1.0 };
	constexpr float deltaRot = 0.01f;

	auto projectionMat = glm::perspective(
		glm::radians(45.f), // ズームの度合い(通常90～30)
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

		rainbow.set_MVP(&tmp[0][0]);
		rainbow.draw();

		app->finish_drawing();
	};

	return 0;

}