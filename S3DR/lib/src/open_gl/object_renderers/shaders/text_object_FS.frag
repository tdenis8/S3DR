#version 330 core

in vec2 textureCord;
in vec4 vsColor;

uniform sampler2D text_texture;

out vec4 outputColor;

void main(void) {
  	outputColor = vec4(vsColor.x, vsColor.y, vsColor.z, texture(text_texture, textureCord).r);
}