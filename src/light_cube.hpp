#pragma once
#include<memory>
#include<glew.h>

namespace graphic
{
	class vertex_array_with_index;
	class shader;

	//�����̈ʒu�̖ڈ��Ƃ��Ďg�p����V���v���Ȕ����n�R
	class light_cube
	{
		std::unique_ptr<vertex_array_with_index> m_vertex_array;
		std::unique_ptr<shader> m_shader;

	public:
		light_cube();

		//model,view,per..�̐ݒ�
		void set_MVP(const GLfloat* mat4);
		//�`��
		void draw();
	};
}