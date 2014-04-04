#include "program.hpp"

#include "misc/custom_exp.hpp"

Program::Program(const std::vector<Shader>& shaders):
	program_obj(0)
{
    if(shaders.size() <= 0){
    	std::string error("*** No shaders were provided to create the program.");
        throw CustomExp(error);
    }
    
    program_obj = glCreateProgram();   
    if( program_obj == 0 ){
        std::string error("*** Failed on glCreateShader call.");
        throw CustomExp(error);
    }

    for(unsigned i = 0; i < shaders.size(); ++i){
        glAttachShader(program_obj, shaders[i].ShaderObject());
    }

    glLinkProgram(program_obj);
    
    for(unsigned i = 0; i < shaders.size(); ++i){
        glDetachShader(program_obj, shaders[i].ShaderObject());
    }
    
    GLint status;
    glGetProgramiv(program_obj, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        std::string error("*** Failed to link program.\n");
        
        GLint infoSize;
        glGetProgramiv(program_obj, GL_INFO_LOG_LENGTH, &infoSize);
        char* Info = new char[infoSize + 1];
        glGetProgramInfoLog(program_obj, infoSize, NULL, Info);
        error += std::string(Info);

        delete[] Info;
        glDeleteProgram(program_obj);
        program_obj = 0;

        throw CustomExp(error);
    }
}
 
Program::~Program()
{
	if(program_obj != 0){
		glDeleteProgram(program_obj);
	}
}

GLuint Program::ProgramObject() const {
	return program_obj;
}

GLuint Program::Uniform(const std::string & uniform_name) const{
    return glGetUniformLocation(program_obj, uniform_name.c_str());
}

GLuint Program::UniformBlock(const std::string & uniform_block_name) const {
    return glGetUniformBlockIndex(program_obj, uniform_block_name.c_str());
}