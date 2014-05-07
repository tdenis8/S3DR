#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <GL/glew.h>
#include <string>

class Texture {
public:
    Texture() = delete;
    Texture(const std::string& texture_filename);
    ~Texture();
    // Texture(const Texture &)=delete;
    // Texture & operator=(const Texture &)=delete;

    bool Load();
    void Bind(GLenum texture_unit);

private:
    std::string texture_filename;
    GLuint texture_object;
};

#endif