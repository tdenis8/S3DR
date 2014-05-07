#ifndef _BASE_TEXTURE_HPP_
#define _BASE_TEXTURE_HPP_

#include <GL/glew.h>

class BaseTexture {
public:
    BaseTexture();
    virtual ~BaseTexture();
    BaseTexture(const BaseTexture &) = delete;
    BaseTexture &operator=(const BaseTexture &) = delete;
    BaseTexture(BaseTexture &&);

    void Bind(GLenum texture_unit = GL_TEXTURE0);
    void UnBind();

private:
    GLuint texture_id_;
};

#endif