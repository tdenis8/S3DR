#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};


in vec3 Position;
in vec3 Normal;

out vec4 color;

#define NUM_POINT_LIGHTS 6

uniform Material material;
uniform vec3 camera_pos;

layout (std140) uniform DirectionalLightBlock
{
    DirectionalLight directional_light;
};

layout (std140) uniform PointLightsBlock
{
    PointLight point_lights[NUM_POINT_LIGHTS];
};

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 camera_dir)
{
    vec3 light_dir = normalize(-light.direction);
    vec3 reflect_dir = reflect(-light_dir, normal);

    float diffuse_coef = max(dot(normal, light_dir), 0.0);
    float specular_coef = pow(max(dot(camera_dir, reflect_dir), 0.0), material.shininess);

    vec3 ambient = light.ambient * material.diffuse;
    vec3 diffuse = light.diffuse * diffuse_coef * material.diffuse;
    vec3 specular = light.specular * specular_coef * material.specular;
    
    return (ambient + diffuse + specular);
}

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 frag_position, vec3 camera_dir)
{
    vec3 light_dir = normalize(light.position - frag_position);
    vec3 reflect_dir = reflect(-light_dir, normal);

    float diffuse_coef = max(dot(normal, light_dir), 0.0);
    float specular_coef = pow(max(dot(camera_dir, reflect_dir), 0.0), material.shininess);
   
    float distance = length(light.position - frag_position);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance)); 

    vec3 ambient = light.ambient * material.diffuse;
    vec3 diffuse = light.diffuse * diffuse_coef * material.diffuse;
    vec3 specular = light.specular * specular_coef * material.specular;

    return (ambient + diffuse + specular) * attenuation;
}

void main()
{    
    vec3 norm = normalize(Normal);
    vec3 camera_dir = normalize(camera_pos - Position);
    
    vec3 result = CalculateDirectionalLight(directional_light, norm, camera_dir);
    
    for(int i = 0; i < NUM_POINT_LIGHTS; i++){
        result = result + CalculatePointLight(point_lights[i], norm, Position, camera_dir);   
    }

    color = vec4(result, 1.0);
}
