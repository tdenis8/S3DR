#include "text_object.hpp"

TextObject::TextObject(SceneObject* parent, const std::string& name, unsigned int size, int priority)
    : SceneObject(parent, name, priority)
    , Subject<TextObjectEvents>()
    , text_key_counter_(0)
    , font_name_("")
    , font_size_(0)
{
}

TextObject::~TextObject()
{
}

int TextObject::AddText(
    unsigned int type, const std::wstring& text, const glm::vec4& color, unsigned int x, unsigned int y)
{
    TextEntry new_text_entry;

    if (font_name_.size() == 0 && font_size_ == 0)
    {
        return -1;
    }

    new_text_entry.key = text_key_counter_++;

    new_text_entry.text = text;
    new_text_entry.color = color;
    new_text_entry.x = x;
    new_text_entry.y = y;

    new_text_entry.font_name = font_name_;
    new_text_entry.font_size = font_size_;

    if (type == 0)
    {
        static_text_entries_.push_back(new_text_entry);
        Subject<TextObjectEvents>::Emit(TextObjectEvents::STATIC_TEXT_ADDED, TextObjectInfo(new_text_entry));
    }
    else
    {
        dynamic_text_entries_.push_back(new_text_entry);
        Subject<TextObjectEvents>::Emit(TextObjectEvents::DYNAMIC_TEXT_ADDED, TextObjectInfo(new_text_entry));
    }

    return new_text_entry.key;
}

void TextObject::RemoveText(unsigned int type, unsigned int text_key)
{
    if (type == 0)
    {
        for (auto it = std::begin(static_text_entries_); it != std::end(static_text_entries_); ++it)
        {
            if (it->key == text_key)
            {
                static_text_entries_.erase(it);
                Subject<TextObjectEvents>::Emit(TextObjectEvents::TEXT_REMOVED);
                break;
            }
        }
    }
    else
    {
        for (auto it = std::begin(dynamic_text_entries_); it != std::end(dynamic_text_entries_); ++it)
        {
            if (it->key == text_key)
            {
                dynamic_text_entries_.erase(it);
                Subject<TextObjectEvents>::Emit(TextObjectEvents::TEXT_REMOVED);
                break;
            }
        }
    }
}

void TextObject::SetFontNameAndFontSize(const std::string& font_name, unsigned int font_size)
{
    font_name_ = font_name;
    font_size_ = font_size;
}
int TextObject::AddStaticText(const std::wstring& text, const glm::vec4& color, unsigned int x, unsigned int y)
{
    return AddText(0, text, color, x, y);
}

int TextObject::AddDynamicText(const std::wstring& text, const glm::vec4& color, unsigned int x, unsigned int y)
{
    return AddText(1, text, color, x, y);
}

void TextObject::RemoveStaticText(unsigned int text_key)
{
    RemoveText(0, text_key);
}

void TextObject::RemoveDynamicText(unsigned int text_key)
{
    RemoveText(1, text_key);
}

void TextObject::UpdateDynamicText(unsigned int text_key, const std::wstring& text)
{
    for (auto it = std::begin(dynamic_text_entries_); it != std::end(dynamic_text_entries_); ++it)
    {
        if (it->key == text_key)
        {
            it->text = text;
            Subject<TextObjectEvents>::Emit(TextObjectEvents::DYNAMIC_TEXT_CHANGED);
            break;
        }
    }
}

const std::vector<TextEntry>& TextObject::GetStaticTextEntries()
{
    return static_text_entries_;
}

const std::vector<TextEntry>& TextObject::GetDynamicTextEntries()
{
    return dynamic_text_entries_;
}
