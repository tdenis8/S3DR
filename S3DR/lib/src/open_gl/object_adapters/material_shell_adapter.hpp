#ifndef _MATERIAL_SHELL_ADAPTER_HPP_
#define _MATERIAL_SHELL_ADAPTER_HPP_

#include "scene_object_adapter.hpp"
#include "model/material_shell_object.hpp"
#include "../object_renderers/misc/program.hpp"

class MaterialShellAdapter : public SceneObjectAdapter
{
    public:
    MaterialShellAdapter() = delete;
    MaterialShellAdapter(MaterialShellObject& material_shell_object);
    MaterialShellAdapter(const MaterialShellAdapter&) = delete;
    MaterialShellAdapter& operator=(const MaterialShellAdapter&) = delete;
    ~MaterialShellAdapter();

    void SetProgram(Program* program);

    void Render();
    void SelectionRender(std::function<void(int)> set_scene_object_key, std::function<void(int)> set_entry_index);

    private:
    void UpdateData();

    void SetMaterialPA(const Material& material);

    MaterialShellObject& material_shell_object_;

    GLuint vao_object_;
    GLuint vbo_objects_[3];
    Program* program_;
};

#endif