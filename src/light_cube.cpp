#include"light_cube.hpp"
#include"vertex_array.hpp"
#include"shader.hpp"
#include<glm.hpp>
#include<array>

namespace graphic
{
	light_cube::light_cube()
		:m_vertex_array{ nullptr }
		, m_shader{ nullptr }
	{

		m_shader = std::make_unique<graphic::shader>("ShaderFile/light_cube/shader.vert", "ShaderFile/light_cube/shader.frag");

		std::array vert{
			glm::vec3{0.5f,0.5f,0.5f},
			glm::vec3{-0.5f,0.5f,0.5f},
			glm::vec3{-0.5f,-0.5f,0.5f},
			glm::vec3{0.5f,-0.5f,0.5f},
			glm::vec3{0.5f,0.5f,-0.5f},
			glm::vec3{-0.5f,0.5f,-0.5f},
			glm::vec3{-0.5f,-0.5f,-0.5f},
			glm::vec3{0.5f,-0.5f,-0.5f},

		};
		std::array<unsigned int, 36> index{
			0,1,2,0,2,3,
			0,1,5,0,5,4,
			1,2,6,1,6,5,
			4,5,6,4,6,7,
			7,6,2,7,2,3,
			0,4,7,0,7,3
		};
		m_vertex_array = std::make_unique<vertex_array>(std::move(vert), std::move(index));

		auto posLocation = m_shader->get_attribute_location("pos");
		m_vertex_array->set_attribute_location(posLocation, 3, GL_FALSE, 3, 0);
	}

	void light_cube::set_MVP(const GLfloat* mat4)
	{
		m_shader->use();
		auto mvpLoc = m_shader->get_uniform_location("MVP");
		glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, mat4);
	}

	void light_cube::draw()
	{
		m_shader->use();
		m_vertex_array->draw(GL_TRIANGLES);
	}
}