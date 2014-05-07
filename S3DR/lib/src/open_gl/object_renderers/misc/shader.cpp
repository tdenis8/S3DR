#include "shader.hpp"

#include "utility/custom_exp.hpp"

#include <fstream>
#include <sstream>

Shader::~Shader()
{
    if (shader_obj.unique() && *shader_obj != 0)
    {
        glDeleteShader(*shader_obj);
    }
}

Shader::Shader(const std::string &shader_string, GLenum shader_type) : shader_obj(new GLuint)
{

    *shader_obj = glCreateShader(shader_type);
    if (*shader_obj == 0)
    {
        std::string error("*** Failed on glCreateShader call.");
        throw CustomExp(error);
    }

    const GLchar *shader_code_ptr = reinterpret_cast<const GLchar *>(shader_string.c_str());
    const GLint shader_code_length = shader_string.size();

    glShaderSource(*shader_obj, 1, &shader_code_ptr, &shader_code_length);
    glCompileShader(*shader_obj);

    GLint status;
    glGetShaderiv(*shader_obj, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        std::string error("*** Failed to compile shader.\n");

        GLint infoSize;
        glGetShaderiv(*shader_obj, GL_INFO_LOG_LENGTH, &infoSize);
        char *Info = new char[infoSize + 1];
        glGetShaderInfoLog(*shader_obj, infoSize, NULL, Info);
        error += std::string(Info);

        delete[] Info;
        glDeleteShader(*shader_obj);
        *shader_obj = 0;

        throw CustomExp(error);
    }
}

Shader Shader::ShaderFromFile(const std::string &file_path, GLenum shader_type)
{
    std::ifstream File;
    File.open(file_path.c_str(), std::ios::in | std::ios::binary);
    if (!File.is_open())
    {
        std::string error = std::string("*** Failed to open file: ") + file_path;
        throw CustomExp(error);
    }

    std::stringstream buffer;
    buffer << File.rdbuf();
    File.close();

    Shader shader(buffer.str(), shader_type);
    return shader;
}

GLuint Shader::ShaderObject() const
{
    return *shader_obj;
}
