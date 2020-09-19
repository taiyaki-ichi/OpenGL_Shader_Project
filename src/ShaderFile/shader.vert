#version 120

//
// shader.vert
//

void main(void)
{
    gl_Position = gl_Vertex+vec4(0.0,0.4,0.0,0.0);
    gl_FrontColor = gl_Color;
}