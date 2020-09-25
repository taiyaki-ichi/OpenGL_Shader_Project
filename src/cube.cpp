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

    void cube::set_vec3f(const std::string& name, float f1, float f2, float f3)
    {
        m_shader->use();
        auto location = m_shader->get_uniform_location(name);
        glUniform3f(location, f1, f2, f3);
    }

    void cube::set_vec3f(const std::string& name, const glm::vec3& vec)
    {
        m_shader->use();
        auto mvpLoc = m_shader->get_uniform_location(name);
        glUniform3f(mvpLoc, vec.x, vec.y, vec.z);
    }

    void cube::set_float(const std::string& name, float f)
    {
        m_shader->use();
        auto location = m_shader->get_uniform_location(name);
        glUniform1f(location, f);
    }

    void cube::set_mat4f(const std::string& name, const GLfloat* mat4)
    {
        m_shader->use();
        auto location = m_shader->get_uniform_location(name);
        glUniformMatrix4fv(location, 1, GL_FALSE, mat4);
    }

    void cube::draw()
    {
        m_shader->use();
        m_vertex_array->draw(GL_TRIANGLES);
    }

}