#ifndef _PROGRAM_H_
#define _PROGRAM_H_

#include "shader.hpp"

#include <vector>
#include <string>

class Program
{
    public:
    Program() = delete;
    Program(const std::vector<Shader> &shaders);
    Program(const Program &) = delete;
    Program &operator=(const Program &other);
    ~Program();

    GLuint ProgramObject() const;
    GLuint GetUniform(const std::string &uniform_name) const;
    GLuint GetUniformBlock(const std::string &uniform_block_name) const;

    private:
    void CompileShaders(const std::vector<Shader> &shaders);

    bool fake_program_;
    GLuint program_obj_;
};

#endif