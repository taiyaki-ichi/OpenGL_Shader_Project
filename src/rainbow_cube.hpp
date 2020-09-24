#pragma once
#include<memory>
#include<glew.h>

namespace graphic
{
	class vertex_array_with_index;
	class shader;

	//虹色のキューブ
	class rainbow_cube
	{
		std::unique_ptr<vertex_array_with_index> m_vertex_array;
		std::unique_ptr<shader> m_shader;

	public:
		rainbow_cube();

		//配列の先頭のポインタ
		void set_MVP(const GLfloat* mat4);

		void draw();
	};
}