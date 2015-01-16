#ifndef _SHADER_H_
#define _SHADER_H_

#include <GL/glew.h>
#include <string>
#include <memory>

class Shader
{
   public:
   Shader() = delete;
   Shader(const std::string &shader_string, GLenum shader_type, const std::string &shader_name = "UNDEFINED_SHADER_NAME");
   ~Shader();
   // Shader(const Shader &)=delete;
   // Shader & operator=(const Shader &)=delete;

   static Shader ShaderFromFile(const std::string &file_path, GLenum shader_type);

   GLuint ShaderObject() const;

   private:
   std::shared_ptr<GLuint> shader_obj;
};

#endif