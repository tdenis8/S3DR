#version 330

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec4 color;

out vec4 diffuseColor;
out vec3 vertexNormal;
out vec3 cameraSpacePosition;

uniform mat4 modelToClipMatrix;
uniform mat4 modelToCameraMatrix;
uniform mat3 normalModelToCameraMatrix;

void main()
{
	gl_Position = modelToClipMatrix * vec4(vertex, 1.0);

	vertexNormal = normalModelToCameraMatrix * normal;
	diffuseColor = color;
	cameraSpacePosition = vec3(modelToCameraMatrix * vec4(vertex, 1.0));
}
