#version 330 core

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec4 color;

out vec4 diffuseColor;
out vec3 vertexNormal;
out vec3 cameraSpacePosition;

uniform vec4 material_color;
uniform int material_status;

uniform mat4 modelToCameraMatrix;
uniform mat4 cameraToClipMatrix;
uniform mat3 normalModelToCameraMatrix;

void main()
{
	vec4 tempCamPosition = (modelToCameraMatrix * vec4(vertex, 1.0));
	gl_Position = cameraToClipMatrix * tempCamPosition;

	vertexNormal = normalModelToCameraMatrix * normal;
	if(material_status == 0){
		diffuseColor = color;
	}
	else{
		diffuseColor = material_color;
	}
	cameraSpacePosition = vec3(tempCamPosition);
}