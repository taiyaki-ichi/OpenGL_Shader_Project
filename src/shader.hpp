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

		GLint get_attribute_location(const std::string& name);
		GLint get_uniform_location(const std::string& name);
	};


}