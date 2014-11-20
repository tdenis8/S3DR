#include "program.hpp"

#include "utility/custom_exp.hpp"

Program::Program(const std::vector<Shader>& shaders) : fake_program_(false), program_obj_(0)
{
    if(shaders.size() > 0)
    {
        CompileShaders(shaders);
    }
    else
    {
        fake_program_ = true;
    }
}

Program& Program::operator=(const Program& other)
{
    if(fake_program_)
    {
        fake_program_ = true;
        program_obj_ = other.program_obj_;
        return *this;
    }

    std::string error("*** Trying to copy non fake program.");
    throw CustomExp(error);
}

Program::~Program()
{
    if(program_obj_ != 0 and !fake_program_)
    {
        glDeleteProgram(program_obj_);
    }
}

void Program::CompileShaders(const std::vector<Shader>& shaders)
{
    program_obj_ = glCreateProgram();
    if(program_obj_ == 0)
    {
        std::string error("*** Failed on glCreateShader call.");
        throw CustomExp(error);
    }

    for(unsigned i = 0; i < shaders.size(); ++i)
    {
        glAttachShader(program_obj_, shaders[i].ShaderObject());
    }

    glLinkProgram(program_obj_);

    for(unsigned i = 0; i < shaders.size(); ++i)
    {
        glDetachShader(program_obj_, shaders[i].ShaderObject());
    }

    GLint status;
    glGetProgramiv(program_obj_, GL_LINK_STATUS, &status);
    if(status == GL_FALSE)
    {
        std::string error("*** Failed to link program.\n");

        GLint infoSize;
        glGetProgramiv(program_obj_, GL_INFO_LOG_LENGTH, &infoSize);
        char* Info = new char[infoSize + 1];
        glGetProgramInfoLog(program_obj_, infoSize, NULL, Info);
        error += std::string(Info);

        delete[] Info;
        glDeleteProgram(program_obj_);
        program_obj_ = 0;

        throw CustomExp(error);
    }
}

GLuint Program::ProgramObject() const
{
    return program_obj_;
}

GLuint Program::GetUniform(const std::string& uniform_name) const
{
    return glGetUniformLocation(program_obj_, uniform_name.c_str());
}

GLuint Program::GetUniformBlock(const std::string& uniform_block_name) const
{
    return glGetUniformBlockIndex(program_obj_, uniform_block_name.c_str());
}