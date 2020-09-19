#pragma once
#include<Windows.h>
#include<glew.h>
#include<optional>
#include<string>

namespace shader
{

	//シェーダをコンパイルする
	//GLenumには、主にGL_VERTEX_SHADERかGL_FRAGMENT_SHADERかな
	//デリケータを指定するので解放処理不要
	std::optional<GLuint> compile(const std::string& fileName, GLenum sharderType);

	//コンパイル済みのシェーダを2つ受け取りリンクされたプログラムを作成
	//デリケータ指定、解放処理不要
	std::optional<GLuint> create_shaderprogram(GLuint vertShader, GLuint fragShader);

}