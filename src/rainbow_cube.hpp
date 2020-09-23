#pragma once
#include<memory>
#include<glew.h>

namespace graphic
{
	class vertex_array;
	class shader;

	//���F�̃L���[�u
	class rainbow_cube
	{
		std::unique_ptr<vertex_array> m_vertex_array;
		std::unique_ptr<shader> m_shader;

	public:
		rainbow_cube();

		//�z��̐擪�̃|�C���^
		void set_MVP(const GLfloat* mat4);

		void draw();
	};
}