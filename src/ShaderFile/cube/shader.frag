#version 330 core

out vec4 color;
 
in vec3 normal;
in vec3 fragPos;

uniform vec3 cubeColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{

    //�@���x�N�g��
    vec3 norm=normalize(normal);
    //���C�g�̕���
    vec3 lightDir=normalize(lightPos-fragPos);
    //���̉e���ǂ���
    float diff=max(dot(norm,lightDir),0.0);
    vec3 diffuse=diff*lightColor;

    //���ʔ��ˋ����x�l������
    float specularStrength=0.5;
    vec3 viewDir=normalize(viewPos-fragPos);
    vec3 reflectDir=reflect(-lightDir,norm);
    float spec=pow(max(dot(viewDir,reflectDir),0.0),64);
    vec3 specular=specularStrength*spec*lightColor;

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 result=(ambient+diffuse+specular)*cubeColor;
    color = vec4(result, 1.0);
   

}