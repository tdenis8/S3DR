#version 330 core

layout(location = 0) in vec3 vertex;

uniform mat4 modelToClipMatrix;

void main()
{
    gl_Position = modelToClipMatrix * vec4(vertex, 1.0);
}