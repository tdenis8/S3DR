#ifndef _TEXT_ADAPTER_HPP_
#define _TEXT_ADAPTER_HPP_

#include "model/text_object.hpp"
#include "scene_object_adapter.hpp"

#include "fonts/atlas_texture.hpp"
#include "fonts/font_handler.hpp"

class TextAdapter : public SceneObjectAdapter
{
    public:
    TextAdapter() = delete;
    TextAdapter(TextObject& text_object);
    TextAdapter(const TextAdapter&) = delete;
    TextAdapter& operator=(const TextAdapter&) = delete;
    ~TextAdapter();

    void Render();
    void SelectionRender(std::function<void(int)> set_scene_object_key, std::function<void(int)> set_entry_index);

    private:
    void StaticTextAdded(const EventInfo& info);
    void DynamicTextAdded(const EventInfo& info);
    void TextRemoved(const EventInfo& info);
    void DynamicTextChanged(const EventInfo& info);

    std::shared_ptr<FontHandler> FindFontHandler(const std::string& font_name, unsigned int font_size);

    void UpdateData();
    void UpdateStaticData();
    void UpdateDynamicData();

    TextObject& text_object_;

    AtlasTexture atlas_texture_;
    std::map<unsigned int, std::shared_ptr<FontHandler> > text_key_to_font_handler_;

    GLuint static_vao_object_;
    GLuint static_vbo_objects_[3];

    GLuint dynamic_vao_object_;
    GLuint dynamic_vbo_objects_[3];

    std::vector<glm::vec4> static_text_vertices_;
    std::vector<glm::vec4> static_text_colors_;
    std::vector<glm::ivec3> static_text_indices_;

    std::vector<glm::vec4> dynamic_text_vertices_;
    std::vector<glm::vec4> dynamic_text_colors_;
    std::vector<glm::ivec3> dynamic_text_indices_;
};

#endif