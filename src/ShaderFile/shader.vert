#version 330 core

in vec3 pos;
in vec3 color;

out vec3 outColor;

void main()
{
    gl_Position = vec4(pos,1.0);
    outColor=color;
}