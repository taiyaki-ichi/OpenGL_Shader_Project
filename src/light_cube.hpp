#pragma once
#include<memory>
#include<glew.h>

namespace graphic
{
	class vertex_array_with_index;
	class shader;

	//光源の位置の目安として使用するシンプルな白いハコ
	class light_cube
	{
		std::unique_ptr<vertex_array_with_index> m_vertex_array;
		std::unique_ptr<shader> m_shader;

	public:
		light_cube();

		//model,view,per..の設定
		void set_MVP(const GLfloat* mat4);
		//描写
		void draw();
	};
}