#version 330 core

out vec4 color;
  
uniform vec3 cubeColor;
uniform vec3 lightColor;

void main()
{
    color = vec4(lightColor * cubeColor, 1.0);
}