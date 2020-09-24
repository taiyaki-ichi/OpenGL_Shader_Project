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
	auto lightPos = glm::vec3{ 1.2f,1.f,2.f };
	glm::mat4 lightModel{ 1.f };
	lightModel = glm::translate(lightModel, lightPos);
	lightModel = glm::scale(lightModel, glm::vec3(0.2f));

	auto cube = graphic::cube{};
	cube.set_cube_color(1.f, 0.5f, 0.31f);
	cube.set_light_color(1.f, 1.f, 1.f);
	glm::mat4 cubeModel{ 1.f };
	//cubePos = glm::translate(cubePos, glm::vec3{ 0.f,0.f,0.f });
	cubeModel = glm::scale(cubeModel, glm::vec3(1.f));

	constexpr float deltaRot = 0.01f;

	auto projectionMat = glm::perspective(
		glm::radians(45.f), // �Y�[���̓x����(�ʏ�90�`30)
		(GLfloat)windowWidth / (GLfloat)windowHeight,		// �A�X�y�N�g��
		0.1f,		// �߂��̃N���b�s���O����
		100.0f		// �����̃N���b�s���O����
	);

	auto viewMat = glm::lookAt(
		glm::vec3(0.0, 0.0, 5.0), // ���[���h��Ԃł̃J�����̍��W
		glm::vec3(0.0, 0.0, 0.0), // ���Ă���ʒu�̍��W
		glm::vec3(0.0, 1.0, 0.0)  // ������������B(0,1.0,0)�ɐݒ肷���y������ɂȂ�܂�
	);

	auto pv = projectionMat * viewMat;

	while (app->loop()) {
		app->begin_drawing();

		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//lightPos= glm::rotate(lightPos, deltaRot, glm::vec3(0.2, 0.1, 0.05));
		auto lightPosMVP = projectionMat * viewMat * lightModel;
		light.set_MVP(&lightPosMVP[0][0]);
		light.draw();
		
		cubeModel = glm::rotate(cubeModel, deltaRot, glm::vec3(0.2, 0.1, 0.05));
		cube.set_PV(&pv[0][0]);
		cube.set_model(&cubeModel[0][0]);
		cube.set_light_pos(lightPos);
		cube.draw();
	
		app->finish_drawing();
	};

	return 0;

}