#include "text_adapter.hpp"

#include "utility/custom_operators.hpp"
#include "open_gl/misc/base_texture.hpp"

template <typename T, unsigned size> inline unsigned ARRAY_SIZE(const T (&array)[size])
{
    return size;
}

#define VERTICES_BUF 0
#define COLORS_BUF 1
#define INDICES_BUF 2

TextAdapter::TextAdapter(TextObject &text_object)
    : SceneObjectAdapter(text_object)
    , text_object_(text_object)
    , atlas_texture_(AtlasTexture(512, 512))
{
    glGenVertexArrays(1, &static_vao_object_);
    glGenBuffers(ARRAY_SIZE(static_vbo_objects_), static_vbo_objects_);

    glGenVertexArrays(1, &dynamic_vao_object_);
    glGenBuffers(ARRAY_SIZE(dynamic_vbo_objects_), dynamic_vbo_objects_);

    text_object_.Subject<TextObjectEvents>::Observe(
        TextObjectEvents::STATIC_TEXT_ADDED,
        std::bind(&TextAdapter::StaticTextAdded, this, std::placeholders::_1),
        this);

    text_object_.Subject<TextObjectEvents>::Observe(
        TextObjectEvents::DYNAMIC_TEXT_ADDED,
        std::bind(&TextAdapter::DynamicTextAdded, this, std::placeholders::_1),
        this);

    text_object_.Subject<TextObjectEvents>::Observe(
        TextObjectEvents::TEXT_REMOVED, std::bind(&TextAdapter::TextRemoved, this, std::placeholders::_1), this);

    text_object_.Subject<TextObjectEvents>::Observe(
        TextObjectEvents::DYNAMIC_TEXT_CHANGED,
        std::bind(&TextAdapter::DynamicTextChanged, this, std::placeholders::_1),
        this);

    UpdateData();
}

TextAdapter::~TextAdapter()
{
    text_object_.Subject<TextObjectEvents>::RemoveObservers(this);

    glDeleteVertexArrays(1, &static_vao_object_);
    glDeleteBuffers(ARRAY_SIZE(static_vbo_objects_), static_vbo_objects_);

    glDeleteVertexArrays(1, &dynamic_vao_object_);
    glDeleteBuffers(ARRAY_SIZE(dynamic_vbo_objects_), dynamic_vbo_objects_);
}

void TextAdapter::StaticTextAdded(const EventInfo &info)
{
    const TextObjectInfo &to_info = dynamic_cast<const TextObjectInfo &>(info);
    const auto &entry = to_info.GetEntry();

    std::shared_ptr<FontHandler> font_handler = FindFontHandler(entry.font_name, entry.font_size);
    font_handler->GenerateRenderDataForText(entry.text, entry.x, entry.y, static_text_vertices_, static_text_indices_);

    std::vector<glm::vec4> entry_colors(entry.text.size() * 4, entry.color);
    static_text_colors_.reserve(static_text_colors_.size() + entry_colors.size());
    static_text_colors_.insert(static_text_colors_.end(), entry_colors.begin(), entry_colors.end());

    UpdateStaticData();

    text_key_to_font_handler[entry.key] = font_handler;
}

void TextAdapter::DynamicTextAdded(const EventInfo &info)
{
    const TextObjectInfo &to_info = dynamic_cast<const TextObjectInfo &>(info);
    const auto &entry = to_info.GetEntry();

    std::shared_ptr<FontHandler> font_handler = FindFontHandler(entry.font_name, entry.font_size);
    font_handler->GenerateRenderDataForText(
        entry.text, entry.x, entry.y, dynamic_text_vertices_, dynamic_text_indices_);

    std::vector<glm::vec4> entry_colors(entry.text.size() * 4, entry.color);
    dynamic_text_colors_.reserve(dynamic_text_colors_.size() + entry_colors.size());
    dynamic_text_colors_.insert(dynamic_text_colors_.end(), entry_colors.begin(), entry_colors.end());

    UpdateDynamicData();

    text_key_to_font_handler[entry.key] = font_handler;
}

void TextAdapter::TextRemoved(const EventInfo &info)
{
    UpdateData();
}

void TextAdapter::DynamicTextChanged(const EventInfo &info)
{
    dynamic_text_vertices_.clear();
    dynamic_text_indices_.clear();

    const auto &dynamic_entries = text_object_.GetDynamicTextEntries();
    for (const auto &it : dynamic_entries)
    {
        std::shared_ptr<FontHandler> font_handler = text_key_to_font_handler[it.key];
        font_handler->GenerateRenderDataForText(it.text, it.x, it.y, dynamic_text_vertices_, dynamic_text_indices_);
    }

    UpdateDynamicData();
}

std::shared_ptr<FontHandler> TextAdapter::FindFontHandler(const std::string &font_name, unsigned int font_size)
{
    for (auto &it : text_key_to_font_handler)
    {
        if ((it.second)->FontName() != font_name)
        {
            continue;
        }

        if ((it.second)->FontSize() != font_size)
        {
            continue;
        }

        return it.second;
    }

    return std::shared_ptr<FontHandler>(new FontHandler(atlas_texture_, font_name, font_size));
}

void TextAdapter::UpdateData()
{
    static_text_vertices_.clear();
    static_text_indices_.clear();
    const auto &static_entries = text_object_.GetStaticTextEntries();
    for (const auto &it : static_entries)
    {
        StaticTextAdded(TextObjectInfo(it));
    }

    dynamic_text_vertices_.clear();
    dynamic_text_indices_.clear();
    const auto &dynamic_entries = text_object_.GetDynamicTextEntries();
    for (const auto &it : dynamic_entries)
    {
        DynamicTextAdded(TextObjectInfo(it));
    }
}

void TextAdapter::UpdateStaticData()
{
    glBindVertexArray(static_vao_object_);

    glBindBuffer(GL_ARRAY_BUFFER, static_vbo_objects_[VERTICES_BUF]);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(static_text_vertices_[0]) * static_text_vertices_.size(),
                 &static_text_vertices_[0],
                 GL_STREAM_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, static_vbo_objects_[COLORS_BUF]);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(static_text_colors_[0]) * static_text_colors_.size(),
                 &static_text_colors_[0],
                 GL_STREAM_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, static_vbo_objects_[INDICES_BUF]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(static_text_indices_[0]) * static_text_indices_.size(),
                 &static_text_indices_[0],
                 GL_STREAM_DRAW);

    glBindVertexArray(0);
}

void TextAdapter::UpdateDynamicData()
{
    glBindVertexArray(dynamic_vao_object_);

    glBindBuffer(GL_ARRAY_BUFFER, dynamic_vbo_objects_[VERTICES_BUF]);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(dynamic_text_vertices_[0]) * dynamic_text_vertices_.size(),
                 &dynamic_text_vertices_[0],
                 GL_STREAM_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, dynamic_vbo_objects_[COLORS_BUF]);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(dynamic_text_colors_[0]) * dynamic_text_colors_.size(),
                 &dynamic_text_colors_[0],
                 GL_STREAM_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, dynamic_vbo_objects_[INDICES_BUF]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(dynamic_text_indices_[0]) * dynamic_text_indices_.size(),
                 &dynamic_text_indices_[0],
                 GL_STREAM_DRAW);

    glBindVertexArray(0);
}

void TextAdapter::Render()
{
    atlas_texture_.Bind();

    unsigned int num_static_indices = static_text_indices_.size() * 3;
    if (num_static_indices)
    {
        glBindVertexArray(static_vao_object_);
        glDrawElementsBaseVertex(GL_TRIANGLES, num_static_indices, GL_UNSIGNED_INT, 0, 0);
        glBindVertexArray(0);
    }

    unsigned int num_dynamic_indices = dynamic_text_indices_.size() * 3;
    if (num_dynamic_indices)
    {
        glBindVertexArray(dynamic_vao_object_);
        glDrawElementsBaseVertex(GL_TRIANGLES, num_dynamic_indices, GL_UNSIGNED_INT, 0, 0);
        glBindVertexArray(0);
    }

    atlas_texture_.UnBind();
}

void TextAdapter::SelectionRender(std::function<void(int)> set_scene_object_key,
                                  std::function<void(int)> set_entry_index)
{
}
