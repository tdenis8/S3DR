#version 330 core

smooth in vec4 vsColor;

out vec4 outputColor;

void main()
{
	outputColor = vsColor;
}