#ifndef _SCENE_OBJECT_RENDERER_HPP_
#define _SCENE_OBJECT_RENDERER_HPP_

#include "misc/program.hpp"

#include <memory>

class SceneObjectAdapter;

class SceneObjectRenderer
{
    public:
    SceneObjectRenderer() = delete;
    SceneObjectRenderer(const std::vector<Shader> &shader_list);
    SceneObjectRenderer(const SceneObjectRenderer &) = delete;
    SceneObjectRenderer &operator=(const SceneObjectRenderer &) = delete;
    virtual ~SceneObjectRenderer();

    void ActivateProgram();
    void DeactivateProgram();

    Program &GetProgram();

    protected:
    Program program_;
};

#endif