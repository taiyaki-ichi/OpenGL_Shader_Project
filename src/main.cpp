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
		glm::radians(45.f), // �Y�[���̓x����(�ʏ�90�`30)
		(GLfloat)windowWidth / (GLfloat)windowHeight,		// �A�X�y�N�g��
		0.1f,		// �߂��̃N���b�s���O����
		100.0f		// �����̃N���b�s���O����
	);

	auto viewMat = glm::lookAt(
		glm::vec3(5.0, 0.0, 0.0), // ���[���h��Ԃł̃J�����̍��W
		glm::vec3(0.0, 2.0, 0.0), // ���Ă���ʒu�̍��W
		glm::vec3(0.0, 1.0, 0.0)  // ������������B(0,1.0,0)�ɐݒ肷���y������ɂȂ�܂�
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