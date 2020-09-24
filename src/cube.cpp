#include"cube.hpp"
#include"shader.hpp"
#include"vertex_array.hpp"
#include<array>

namespace graphic
{

	cube::cube()
		:m_shader{ nullptr }
		, m_vertex_array{ nullptr }
	{
		m_shader = std::make_unique<shader>("ShaderFile/cube/shader.vert", "ShaderFile/cube/shader.frag");

        std::array v = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
        };

        m_vertex_array = std::make_unique<vertex_array>(std::move(v));

        //posの設定
        auto posLocation = m_shader->get_attribute_location("aPos");
        m_vertex_array->set_attribute_location(posLocation, 3, GL_FALSE, 6, 0);

        //法線ベクトル
        auto normalLocation = m_shader->get_attribute_location("aNormal");
        m_vertex_array->set_attribute_location(normalLocation, 3, GL_FALSE, 6, 3);
	}

    void cube::set_cube_color(float r, float g, float b)
    {
        m_shader->use();
        auto colorLocation = m_shader->get_uniform_location("cubeColor");
        glUniform3f(colorLocation, r, g, b);
    }

    void cube::set_light_color(float r, float g, float b)
    {
        m_shader->use();
        auto colorLocation = m_shader->get_uniform_location("lightColor");
        glUniform3f(colorLocation, r, g, b);
    }

    void cube::set_PV(const GLfloat* mat4)
    {
        m_shader->use();
        auto mvpLoc = m_shader->get_uniform_location("PV");
        glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, mat4);
    }

    void cube::set_model(const GLfloat* mat4)
    {
        m_shader->use();
        auto mvpLoc = m_shader->get_uniform_location("model");
        glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, mat4);
    }

    void cube::set_light_pos(const glm::vec3& pos)
    {
        m_shader->use();
        auto mvpLoc = m_shader->get_uniform_location("lightPos");
        glUniform3f(mvpLoc, pos.x, pos.y, pos.z);
    }

    void cube::set_view_pos(const glm::vec3& pos)
    {
        m_shader->use();
        auto mvpLoc = m_shader->get_uniform_location("viewPos");
        glUniform3f(mvpLoc, pos.x, pos.y, pos.z);
    }

    void cube::draw()
    {
        m_shader->use();
        m_vertex_array->draw(GL_TRIANGLES);
    }

}