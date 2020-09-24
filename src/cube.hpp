#pragma once
#include<memory>
#include<glew.h>
#include<glm.hpp>

namespace graphic
{
	class vertex_array;
	class shader;

	//Œõ‚Ì‰e‹¿‚ðŽó‚¯‚éƒnƒR
	class cube
	{
		std::unique_ptr<vertex_array> m_vertex_array;
		std::unique_ptr<shader> m_shader;

	public:
		cube();

		void set_cube_color(float r, float g, float b);
		void set_light_color(float r, float g, float b);

		void set_PV(const GLfloat* mat4);
		void set_model(const GLfloat* mat4);

		void set_light_pos(const glm::vec3& pos);
		void set_view_pos(const glm::vec3& pos);

		void draw();
	};
}