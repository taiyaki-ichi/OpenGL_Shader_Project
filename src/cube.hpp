#pragma once
#include<memory>
#include<glew.h>
#include<glm.hpp>
#include<string>
#include<vector>

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

		void set_vec3f(const std::string&, float, float, float);
		void set_vec3f(const std::string&, const glm::vec3&);
		void set_float(const std::string&, float);
		void set_mat4f(const std::string&, const GLfloat* mat4);

		void draw();
	};

}