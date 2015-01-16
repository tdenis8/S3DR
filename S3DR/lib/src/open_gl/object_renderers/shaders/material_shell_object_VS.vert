#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec3 Position;
out vec3 Normal;

uniform mat4 model;
uniform mat4 projection_view;
uniform mat3 normal_model;

void main()
{
	vec4 world_position =  model * vec4(position, 1.0f);
    gl_Position = projection_view * world_position;
    Position = vec3(world_position);
    Normal = normal_model * normalize(normal);
}

