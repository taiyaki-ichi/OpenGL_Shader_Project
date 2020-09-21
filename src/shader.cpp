#include"shader.hpp"
#include"Utility/file.hpp"
#include<iostream>
#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "glew32.lib")


namespace graphic
{

	namespace {

		//�V�F�[�_���R���p�C������
		//GLenum�ɂ́A���GL_VERTEX_SHADER��GL_FRAGMENT_SHADER����
		//�f���P�[�^���w�肷��̂ŉ�������s�v
		std::optional<GLuint> compile(const std::string& fileName, GLenum sharderType);

		//�R���p�C���ς݂̃V�F�[�_��2�󂯎�胊���N���ꂽ�v���O�������쐬
		//�f���P�[�^�w��A��������s�v
		std::optional<GLuint> create_shaderprogram(GLuint vertShader, GLuint fragShader);
	}


	shader::shader(const std::string& vertShaderFileName, const std::string& fragShaderFileName)
		:m_ID{}
	{
		auto vertID = compile(vertShaderFileName, GL_VERTEX_SHADER);
		auto fragID = compile(fragShaderFileName, GL_FRAGMENT_SHADER);

		if (!vertID)
			std::cout << "faild compile " << vertShaderFileName << "\n";
		if (!fragID)
			std::cout << "failed compile " << fragShaderFileName << "\n";

		//�R���p�C���ɐ��������Ƃ��A�V�F�[�_�v���O�����𐶐�
		if (vertID && fragID)
		{
			auto id = create_shaderprogram(vertID.value(), fragID.value());
			if (id) 
				m_ID = id.value();
			else 
				std::cout << "failed create_shaderprogram ( " << vertShaderFileName << " , " << fragShaderFileName << " )\n";
		}



		//�V�F�[�_�I�u�W�F�N�g�̍폜
		if (vertID)
			glDeleteShader(vertID.value());
		if (fragID)
			glDeleteShader(fragID.value());
	}

	void shader::use()
	{
		glUseProgram(m_ID);
	}

	GLint shader::get_attribute_location(const std::string& name)
	{
		return glGetAttribLocation(m_ID, name.c_str());
	}


	namespace {

		std::optional<GLuint> compile(const std::string& fileName, GLenum sharderType)
		{
			auto str = utility::read_file(fileName);
			if (!str)
				return std::nullopt;

			GLuint shaderObj = glCreateShader(sharderType);

			//�\�[�X�v���O�������V�F�[�_�I�u�W�F�N�g��
			const GLchar* sourcePtr = str.value().c_str();
			GLint length = str.value().length();
			glShaderSource(shaderObj, 1, &sourcePtr, &length);

			//�R���p�C��
			glCompileShader(shaderObj);
			//�����������̊m�F
			GLint flag;
			glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &flag);
			if (flag == GL_FALSE) {
				std::cout << "failed shader compile (file name: " << fileName << " )\n";
				return std::nullopt;
			}

			return shaderObj;
		}
		std::optional<GLuint> create_shaderprogram(GLuint vertShader, GLuint fragShader)
		{
			GLuint shader = glCreateProgram();

			//�o�^
			glAttachShader(shader, vertShader);
			glAttachShader(shader, fragShader);

			//�v���O�����̃����N
			glLinkProgram(shader);
			//�`�F�b�N
			GLint flag;
			glGetProgramiv(shader, GL_LINK_STATUS, &flag);
			if (flag == GL_FALSE) {
				std::cout << "failed program link\n";
				return std::nullopt;
			}
			else
				return shader;

		}
	}

}