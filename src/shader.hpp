#pragma once
#include<Windows.h>
#include<glew.h>
#include<optional>
#include<string>

namespace graphic
{

	class shader
	{
		GLint m_ID;

	public:
		//2つのファイル名から生成
		shader(const std::string& vertShaderFileName, const std::string& fragShaderFileName);

		//使用する場合呼び出す
		void use();

		template<typename T>
		void set(const std::string& name, T&& data);

		GLint get_attribute_location(const std::string& name);
	};

	template<typename T>
	void shader::set(const std::string& name, T&& data) {
		if constexpr (std::is_same_v<bool, T>)
			glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int)data);
		else
			glUniform1i(glGetUniformLocation(m_ID, name.c_str()), data);
	}

}