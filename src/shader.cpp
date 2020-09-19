#include"shader.hpp"
#include"Utility/file.hpp"
#include<iostream>
#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "glew32.lib")


namespace shader
{
	std::optional<GLuint> compile(const std::string& fileName, GLenum sharderType)
	{
		auto str = utility::read_file(fileName);
		if (!str)
			return std::nullopt;

		GLuint shaderObj = glCreateShader(sharderType);

		//ソースプログラムをシェーダオブジェクトへ
		const GLchar* sourcePtr = str.value().c_str();
		GLint length = str.value().length();
		glShaderSource(shaderObj, 1, &sourcePtr, &length);

		//コンパイル
		glCompileShader(shaderObj);
		//成功したかの確認
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

		//登録
		glAttachShader(shader, vertShader);
		glAttachShader(shader, fragShader);

		//プログラムのリンク
		glLinkProgram(shader);
		//チェック
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