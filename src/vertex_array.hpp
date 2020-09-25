#pragma once
#include<glew.h>

namespace graphic
{
	//���_���̂�
	class vertex_array
	{
		GLuint m_VAO_ID;
		GLuint m_vertex_ID;

		//�R���e�i�̑傫��
		const size_t m_vert_container_size;
		//���_������̏���
		size_t m_info_size_per_vert;
		
	public:
		template<typename VertexContainer>
		vertex_array(VertexContainer&& v);
		virtual ~vertex_array();

		void draw(GLenum mode);

		//�Ƃ肠����float�̒l�����ݒ�ł���悤�ɂ���
		void set_attribute_location(GLint location, GLint size, GLboolean normalized, GLsizei strideNum, unsigned int startNum);
	};


	template<typename VertexContainer>
	vertex_array::vertex_array(VertexContainer&& v)
		:m_VAO_ID{}
		, m_vertex_ID{}
		, m_vert_container_size{v.size()}
		, m_info_size_per_vert{}
	{
		glGenVertexArrays(1, &m_VAO_ID);
		glGenBuffers(1, &m_vertex_ID);

		glBindVertexArray(m_VAO_ID);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertex_ID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(v), &v[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);

	}

	//���_���Ƃ��̃C���f�b�N�X���Ǘ�
	class vertex_array_with_index
	{
		GLuint m_VAO_ID;
		GLuint m_vertex_ID;
		GLuint m_index_ID;

		size_t m_index_num;

	public:
		//2�̃R���e�i�^���󂯐���
		//�C���f�b�N�X��unsiged int�̔z��
		template<typename VertexContainer,typename IndexContaier>
		vertex_array_with_index(VertexContainer&& v, IndexContaier&& i);
		~vertex_array_with_index();

		void draw(GLenum mode);

		//�Ƃ肠����float�̒l�����ݒ�ł���悤�ɂ���
		void set_attribute_location(GLint location, GLint size, GLboolean normalized, GLsizei strideNum, unsigned int startNum);
	};



	template<typename VertexContainer, typename IndexContaier>
	vertex_array_with_index::vertex_array_with_index(VertexContainer&& v, IndexContaier&& i)
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

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);

	}

}