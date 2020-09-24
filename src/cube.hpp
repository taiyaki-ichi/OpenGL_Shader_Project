#pragma once
#include<memory>
#include<glew.h>

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

		void set_MVP(const GLfloat* mat4);

		void draw();
	};
}