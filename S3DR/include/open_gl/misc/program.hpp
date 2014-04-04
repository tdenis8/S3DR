#ifndef _PROGRAM_H_
#define _PROGRAM_H_

#include "shader.hpp"

#include <vector>
#include <string>

class Program { 
    public:
        Program(const std::vector<Shader>& shaders);
        ~Program();
        Program(const Program &) = delete;
        Program & operator=(const Program &) = delete;

        GLuint ProgramObject() const;
        GLuint Uniform(const std::string & uniform_name) const;
        GLuint UniformBlock(const std::string & uniform_block_name) const;

    private:
    	GLuint program_obj;
};
    
#endif