#ifndef _SHADER_H_
#define _SHADER_H_

#include <GL/glew.h>
#include <string>
#include <memory>

class Shader { 
    public:
        Shader() = delete;
        Shader(const std::string& shaderCode, GLenum shader_type);
        ~Shader();
        // Shader(const Shader &)=delete;
        // Shader & operator=(const Shader &)=delete;

        static Shader ShaderFromFile(const std::string& file_path, GLenum shader_type);
        
        GLuint ShaderObject() const;
        
    private:
        std::shared_ptr<GLuint> shader_obj;
};
    
#endif