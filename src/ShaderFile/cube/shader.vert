#version 330 core

in vec3 aPos;
in vec3 aNormal;

out vec3 normal;
out vec3 fragPos;

uniform mat4 model;
uniform mat4 PV;

void main()
{
	gl_Position=PV*model*vec4(aPos,1.0);
	fragPos=vec3(model*vec4(aPos,1.0));

	//èŠÔ‚Ì‚©‚©‚éì‹Æ‚È‚Ì‚Åuniform‚Åó‚¯‚Á‚Æ‚Á‚½•û‚ª‚¢‚¢
	normal=mat3(transpose(inverse(model)))*aNormal;
}