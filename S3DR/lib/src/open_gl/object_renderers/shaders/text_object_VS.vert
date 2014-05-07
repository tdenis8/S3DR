#version 330 core

layout(location = 0) in vec4 vertex;
layout(location = 1) in vec4 color;

out vec2 textureCord;
out vec4 vsColor;

uniform mat4 modelToClipMatrix;

void main()
{
	gl_Position = modelToClipMatrix * vec4(vertex.xy, 0, 1);
	textureCord = vertex.zw;
	vsColor = color;
}
