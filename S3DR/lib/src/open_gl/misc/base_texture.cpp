#include "base_texture.hpp"

BaseTexture::BaseTexture()
{
    glGenTextures(1, &texture_id_);
}

BaseTexture::~BaseTexture()
{
    glDeleteTextures(1, &texture_id_);
}

BaseTexture::BaseTexture(BaseTexture &&other)
    : texture_id_(other.texture_id_)
{
    other.texture_id_ = 0;
}

void BaseTexture::Bind(GLenum texture_unit)
{
    glActiveTexture(texture_unit);
    glBindTexture(GL_TEXTURE_2D, texture_id_);
}

void BaseTexture::UnBind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
