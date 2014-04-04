#version 330 core

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec4 color;

smooth out vec4 vsColor;

uniform mat4 modelToClipMatrix;

void main()
{
    gl_Position = modelToClipMatrix * vec4(vertex, 1.0);    
    vsColor = color;
}