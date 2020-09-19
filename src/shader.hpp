#pragma once
#include<Windows.h>
#include<glew.h>
#include<optional>
#include<string>

namespace shader
{

	//�V�F�[�_���R���p�C������
	//GLenum�ɂ́A���GL_VERTEX_SHADER��GL_FRAGMENT_SHADER����
	//�f���P�[�^���w�肷��̂ŉ�������s�v
	std::optional<GLuint> compile(const std::string& fileName, GLenum sharderType);

	//�R���p�C���ς݂̃V�F�[�_��2�󂯎�胊���N���ꂽ�v���O�������쐬
	//�f���P�[�^�w��A��������s�v
	std::optional<GLuint> create_shaderprogram(GLuint vertShader, GLuint fragShader);

}