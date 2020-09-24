#version 330 core

out vec4 color;
 
in vec3 normal;
in vec3 fragPos;

uniform vec3 cubeColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{
    //法線ベクトル
    vec3 norm=normalize(normal);
    //ライトの方向
    vec3 lightDir=normalize(lightPos-fragPos);
    //光の影響どあい
    float diff=max(dot(norm,lightDir),0.0);
    vec3 diffuse=diff*lightColor;

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 result=(ambient+diffuse)*cubeColor;
    color = vec4(result, 1.0);


}