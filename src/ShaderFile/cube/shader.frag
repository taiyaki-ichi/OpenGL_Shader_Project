#version 330 core

out vec4 color;
 
in vec3 normal;
in vec3 fragPos;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

struct Material{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
uniform Material material;

struct Light{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;

void main()
{

    //�@���x�N�g��
    vec3 norm=normalize(normal);
    //���C�g�̕���
    vec3 lightDir=normalize(lightPos-fragPos);
    //���̉e���ǂ���
    float diff=max(dot(norm,lightDir),0.0);
    vec3 diffuse=light.diffuse*(diff*material.diffuse);

    //���ʔ��ˋ����x�l�֌W
    vec3 viewDir=normalize(viewPos-fragPos);
    vec3 reflectDir=reflect(-lightDir,norm);
    float spec=pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
    vec3 specular=light.specular*(spec*material.specular);

    vec3 ambient =light.ambient*material.ambient;

    vec3 result=ambient+diffuse+specular;
    color = vec4(result, 1.0);
   

}