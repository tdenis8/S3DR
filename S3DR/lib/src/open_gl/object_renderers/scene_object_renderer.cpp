#include "scene_object_renderer.hpp"

SceneObjectRenderer::SceneObjectRenderer(const std::vector<Shader>& shader_list) : program_(shader_list)
{
}

SceneObjectRenderer::~SceneObjectRenderer()
{
}

void SceneObjectRenderer::ActivateProgram()
{
    glUseProgram(program_.ProgramObject());
}

void SceneObjectRenderer::DeactivateProgram()
{
    glUseProgram(0);
}

Program& SceneObjectRenderer::GetProgram()
{
    return program_;
}
