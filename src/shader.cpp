#include"shader.hpp"
#include"Utility/file.hpp"
#include<iostream>
#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "glew32.lib")


namespace graphic
{

	namespace {

		//シェーダをコンパイルする
		//GLenumには、主にGL_VERTEX_SHADERかGL_FRAGMENT_SHADERかな
		//デリケータを指定するので解放処理不要
		std::optional<GLuint> compile(const std::string& fileName, GLenum sharderType);

		//コンパイル済みのシェーダを2つ受け取りリンクされたプログラムを作成
		//デリケータ指定、解放処理不要
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

		//コンパイルに成功したとき、シェーダプログラムを生成
		if (vertID && fragID)
		{
			auto id = create_shaderprogram(vertID.value(), fragID.value());
			if (id) 
				m_ID = id.value();
			else 
				std::cout << "failed create_shaderprogram ( " << vertShaderFileName << " , " << fragShaderFileName << " )\n";
		}



		//シェーダオブジェクトの削除
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

}