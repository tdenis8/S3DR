#include "texture.hpp"

#include <SOIL/SOIL.h>

Texture::Texture(const std::string & texture_filename):
	texture_filename(texture_filename)
{

}

Texture::~Texture(){

}

bool Texture::Load(){
	int width, height;
	unsigned char* image = SOIL_load_image(texture_filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);

	if(image){
	    glGenTextures(1, &texture_object);
	    glBindTexture(GL_TEXTURE_2D, texture_object);
	    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	    
	    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	    return true;
	}

	return false;
}

void Texture::Bind(GLenum texture_unit)
{
    glActiveTexture(texture_unit);
    glBindTexture(GL_TEXTURE_2D, texture_object);
}