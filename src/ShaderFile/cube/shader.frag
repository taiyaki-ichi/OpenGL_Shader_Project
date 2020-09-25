#version 330 core

out vec4 color;
 
in vec3 normal;
in vec3 fragPos;

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

    float constant;
    float liner;
    float quadratic;
};

#define LIGHT_NUM 3
uniform Light light[LIGHT_NUM];

//ライトの計算
vec3 calcLight(Light light, vec3 norm, vec3 fragPos, vec3 viewDir); 

void main()
{

    //法線ベクトル
    vec3 norm=normalize(normal);
    //視点へのベクトル
    vec3 viewDir=normalize(viewPos-fragPos);

    vec3 result;
    for(int i=0;i<LIGHT_NUM;i++)
        result+=calcLight(light[i],norm,fragPos,viewDir);

    color=vec4(result,1.0);  
}

vec3 calcLight(Light light, vec3 norm, vec3 fragPos, vec3 viewDir)
{
    //ライトの方向
    vec3 lightDir=normalize(light.position-fragPos);
    //光の影響どあい
    float diff=max(dot(norm,lightDir),0.0);
    vec3 diffuse=light.diffuse*(diff*material.diffuse);

    //鏡面反射鏡強度値関係
    vec3 reflectDir=reflect(-lightDir,norm);
    float spec=pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
    vec3 specular=light.specular*(spec*material.specular);

    vec3 ambient =light.ambient*material.ambient;

    //減衰の実装
    float distance=length(light.position-fragPos);
    float atteniation=1.0/(light.constant+light.liner*distance+light.quadratic*(distance*distance));

    vec3 result=(ambient+diffuse+specular)*atteniation;
    
    return result;
}


