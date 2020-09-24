#include"vertex_array.hpp"

namespace graphic
{

	vertex_array::~vertex_array()
	{
		glDeleteBuffers(1, &m_vertex_ID);
		glDeleteBuffers(1, &m_vertex_ID);
	}

	void vertex_array::draw(GLenum mode)
	{
		glBindVertexArray(m_VAO_ID);
		glDrawArrays(GL_TRIANGLES, 0, m_vert_container_size / m_info_size_per_vert);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void vertex_array::set_attribute_location(GLint location, GLint size, GLboolean normalized, GLsizei strideNum, unsigned int startNum)
	{
		glBindVertexArray(m_VAO_ID);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertex_ID);

		glVertexAttribPointer(location, size, GL_FLOAT, normalized, strideNum * sizeof(float), (void*)(startNum * sizeof(float)));
		glEnableVertexAttribArray(location);

		m_info_size_per_vert += size;

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}


	vertex_array_with_index::~vertex_array_with_index()
	{
		glDeleteBuffers(1, &m_vertex_ID);
		glDeleteBuffers(1, &m_index_ID);
		glDeleteBuffers(1, &m_vertex_ID);
	}

	void vertex_array_with_index::draw(GLenum mode)
	{
		glBindVertexArray(m_VAO_ID);
		glDrawElements(mode, m_index_num, GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void vertex_array_with_index::set_attribute_location(GLint location, GLint size, GLboolean normalized, GLsizei strideNum, unsigned int startNum)
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