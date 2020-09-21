#pragma once
#include<glew.h>

namespace graphic
{

	//���_���Ƃ��̃C���f�b�N�X���Ǘ�
	class vertex_array
	{
		GLuint m_VAO_ID;
		GLuint m_vertex_ID;
		GLuint m_index_ID;

		size_t m_index_num;

	public:
		//2�̃R���e�i�^���󂯐���
		//�C���f�b�N�X��unsiged int�̔z��
		template<typename VertexContainer,typename IndexContaier>
		vertex_array(VertexContainer&& v, IndexContaier&& i);
		~vertex_array();

		void bind_and_draw(GLenum mode);

		//�Ƃ肠����float�̒l�����ݒ�ł���悤�ɂ���
		void set_attribute_location(GLint location, GLint size, GLboolean normalized, GLsizei strideNum, unsigned int startNum);
	};



	template<typename VertexContainer, typename IndexContaier>
	vertex_array::vertex_array(VertexContainer&& v, IndexContaier&& i)
		:m_VAO_ID{}
		, m_vertex_ID{}
		, m_index_ID{}
		, m_index_num{i.size()}
	{
		
		glGenVertexArrays(1, &m_VAO_ID);
		glGenBuffers(1, &m_vertex_ID);
		glGenBuffers(1, &m_index_ID);

		glBindVertexArray(m_VAO_ID);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertex_ID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(v), &v[0], GL_STATIC_DRAW);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(i), &i[0], GL_STATIC_DRAW);


		//glVertexAttribPointer(attribLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		//glEnableVertexAttribArray(attribLocation);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);

		///

		/*
		glBindVertexArray(m_VAO_ID);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertex_ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_ID);

		glVertexAttribPointer(attribLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(attribLocation);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		*/
	
	}

	vertex_array::~vertex_array()
	{
		glDeleteBuffers(1, &m_vertex_ID);
		glDeleteBuffers(1, &m_index_ID);
		glDeleteBuffers(1, &m_vertex_ID);
	}

	void vertex_array::bind_and_draw(GLenum mode)
	{
		glBindVertexArray(m_VAO_ID);
		glDrawElements(mode, m_index_num, GL_UNSIGNED_INT, 0);
	}

	void vertex_array::set_attribute_location(GLint location, GLint size, GLboolean normalized, GLsizei strideNum, unsigned int startNum)
	{
		glBindVertexArray(m_VAO_ID);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertex_ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_ID);

		glVertexAttribPointer(location, size, GL_FLOAT, normalized, strideNum * sizeof(float), (void*)(startNum * sizeof(float)));
		glEnableVertexAttribArray(location);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
}