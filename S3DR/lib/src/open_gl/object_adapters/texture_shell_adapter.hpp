#ifndef _TEXTURE_SHELL_ADAPTER_HPP_
#define _TEXTURE_SHELL_ADAPTER_HPP_

#include "model/texture_shell_object.hpp"
#include "scene_object_adapter.hpp"

#include <vector>

class Texture;

class TextureShellAdapter : public SceneObjectAdapter
{
    public:
    TextureShellAdapter() = delete;
    TextureShellAdapter(TextureShellObject &texture_shell_object);
    TextureShellAdapter(const TextureShellAdapter &) = delete;
    TextureShellAdapter &operator=(const TextureShellAdapter &) = delete;
    ~TextureShellAdapter();

    void Render();
    void SelectionRender(std::function<void(int)> set_scene_object_key, std::function<void(int)> set_entry_index);

    private:
    void UpdateData();

    TextureShellObject &texture_shell_object_;
    bool allow_render_;
    GLuint vao_object_;
    GLuint vbo_objects_[4];

    std::vector<Texture> textures_;
};

#endif