#include "texture.hpp"

#include "utility/custom_exp.hpp"

#include <Magick++.h>

Texture::Texture(const std::string& texture_filename)
    : texture_filename(texture_filename)
{
}

Texture::~Texture()
{
}

bool Texture::Load()
{
    Magick::Image* m_pImage;
    Magick::Blob m_blob;

    try {
        m_pImage = new Magick::Image(texture_filename);
        m_pImage->write(&m_blob, "RGBA");
    }
    catch (Magick::Error& Error) {
        std::string error("*** Error loading texture ");
        throw CustomExp(error + texture_filename + Error.what());
        return false;
    }

    glGenTextures(1, &texture_object);
    glBindTexture(GL_TEXTURE_2D, texture_object);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_RGBA, m_pImage->columns(), m_pImage->rows(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_blob.data());

    return true;
}

void Texture::Bind(GLenum texture_unit)
{
    glActiveTexture(texture_unit);
    glBindTexture(GL_TEXTURE_2D, texture_object);
}