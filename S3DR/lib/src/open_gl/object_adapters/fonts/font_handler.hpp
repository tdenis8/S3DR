#ifndef _FONT_HANDLER_H_
#define _FONT_HANDLER_H_

#include "atlas_texture.hpp"
#include "glyph_descriptor.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <glm/glm.hpp>

#include <string>
#include <vector>

class FontHandler
{
public:
    FontHandler() = delete;
    FontHandler(AtlasTexture &atlas_texture, const std::string &font_name, unsigned int font_size);
    ~FontHandler();
    FontHandler(const FontHandler &) = delete;
    FontHandler &operator=(const FontHandler &) = delete;

    void GenerateRenderDataForText(const std::wstring &text,
                                   unsigned int pen_x,
                                   unsigned int pen_y,
                                   std::vector<glm::vec4> &vertices,
                                   std::vector<glm::ivec3> &indices);

    const std::string &FontName();
    unsigned int FontSize();

private:
    bool LoadGlyph(char16_t charcode);
    bool LoadGlyphs(const std::wstring &text_buffer);

    AtlasTexture &atlas_texture_;
    const std::string &font_name_;
    unsigned int font_size_;

    FT_Library ft_library_;
    FT_Face ft_face_;

    std::vector<GlyphDescriptor> glyphs_;  // Vector of glyphs contained in this font.
};

#endif
