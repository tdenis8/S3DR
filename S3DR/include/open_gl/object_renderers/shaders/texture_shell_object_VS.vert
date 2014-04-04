#version 330 core

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 tex_coord;

out vec2 textureCord;
out vec3 vertexNormal;
out vec3 cameraSpacePosition;

uniform mat4 modelToCameraMatrix;
uniform mat4 cameraToClipMatrix;
uniform mat3 normalModelToCameraMatrix;

void main()
{
	vec4 tempCamPosition = (modelToCameraMatrix * vec4(vertex, 1.0));
	gl_Position = cameraToClipMatrix * tempCamPosition;

	vertexNormal = normalModelToCameraMatrix * normal;
	textureCord = tex_coord;
	cameraSpacePosition = vec3(tempCamPosition);
}
