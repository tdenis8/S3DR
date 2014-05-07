#ifndef _TEXT_OBJECT_H_
#define _TEXT_OBJECT_H_

#include "scene_object.hpp"

#include <glm/glm.hpp>

#include <string>
#include <vector>
#include <memory>

struct TextEntry
{
    unsigned int key;

    std::wstring text;
    glm::vec4 color;
    unsigned int x;
    unsigned int y;

    std::string font_name;
    unsigned int font_size;
};

enum class TextObjectEvents : unsigned int
{
    FONT_CHANGE,
    STATIC_TEXT_ADDED,
    DYNAMIC_TEXT_ADDED,
    TEXT_REMOVED,
    DYNAMIC_TEXT_CHANGED
};

class TextObjectInfo : public EventInfo
{
public:
    TextObjectInfo(const TextEntry &entry)
        : EventInfo()
        , entry_(entry)
    {
    }

    const TextEntry &GetEntry() const
    {
        return entry_;
    }

private:
    const TextEntry &entry_;
};

class TextObject : public SceneObject, public Subject<TextObjectEvents>
{
public:
    TextObject() = delete;
    explicit TextObject(SceneObject *parent, const std::string &name, unsigned int size, int priority = 1);
    TextObject(const TextObject &) = delete;
    TextObject &operator=(const TextObject &) = delete;
    virtual ~TextObject();

    void SetFontNameAndFontSize(const std::string &font_name, unsigned int font_size);

    int AddStaticText(const std::wstring &text, const glm::vec4 &color, unsigned int x, unsigned int y);
    int AddDynamicText(const std::wstring &text, const glm::vec4 &color, unsigned int x, unsigned int y);

    void RemoveStaticText(unsigned int text_key);
    void RemoveDynamicText(unsigned int text_key);

    void UpdateDynamicText(unsigned int text_key, const std::wstring &text);

    const std::vector<TextEntry> &GetStaticTextEntries();
    const std::vector<TextEntry> &GetDynamicTextEntries();

private:
    // type == 0 for static text, type == 1 for dynamic text
    int AddText(unsigned int type, const std::wstring &text, const glm::vec4 &color, unsigned int x, unsigned int y);
    void RemoveText(unsigned int type, unsigned int text_key);

    unsigned int text_key_counter_;

    std::string font_name_;
    unsigned int font_size_;

    std::vector<TextEntry> static_text_entries_;
    std::vector<TextEntry> dynamic_text_entries_;
};

#endif
