#include "font_handler.hpp"

#include "utility/custom_exp.hpp"

#include <algorithm>
#include <iostream>

FontHandler::FontHandler(AtlasTexture &atlas_texture, const std::string &font_name, unsigned int font_size)
    : atlas_texture_(atlas_texture)
    , font_name_(font_name)
    , font_size_(font_size)
{
    if (FT_Init_FreeType(&ft_library_))
    {
        std::string error("*** FreeType init error.");
        throw CustomExp(error);
    }

    if (FT_New_Face(ft_library_, font_name.c_str(), 0, &ft_face_))
    {
        std::string error = std::string("*** Could not load font: ") + font_name;
        throw CustomExp(error);
    }
    FT_Set_Pixel_Sizes(ft_face_, 0, font_size_);

    std::wstring cache =
        L" !\"#$%&'()*+,-./0123456789:;<=>?"
        L"@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_"
        L"`abcdefghijklmnopqrstuvwxyz{|}~";

    LoadGlyphs(cache);
}

FontHandler::~FontHandler()
{
    FT_Done_Face(ft_face_);
    FT_Done_FreeType(ft_library_);
}

bool FontHandler::LoadGlyph(char16_t charcode)
{
    if (FT_Load_Char(ft_face_, charcode, FT_LOAD_RENDER))
    {
        std::cout << "Filed to load gryph for charcode " << charcode << std::endl;
        return false;
    }

    FT_GlyphSlot glyph = ft_face_->glyph;

    unsigned int region_width = glyph->bitmap.width + 1;
    unsigned int region_height = glyph->bitmap.rows + 1;

    Rectangle region = atlas_texture_.GetRegion(region_width, region_height);

    if (region.width == -1 && region.height == -1)
    {
        std::cout << "Texture atlas is full. " << std::endl;
        return false;
    }

    atlas_texture_.SetRegion(
        region.x, region.y, region_width - 1, region_height - 1, glyph->bitmap.buffer, glyph->bitmap.pitch);

    GlyphDescriptor desc;

    desc.charcode = charcode;
    desc.width = glyph->bitmap.width;
    desc.height = glyph->bitmap.rows;
    desc.offset_x = glyph->bitmap_left;
    desc.offset_y = glyph->bitmap_top;
    desc.advance_x = glyph->advance.x / 64;
    desc.advance_y = glyph->advance.y / 64;

    desc.s0 = region.x / (float)atlas_texture_.GetWidth();
    desc.t0 = region.y / (float)atlas_texture_.GetHeight();
    desc.s1 = (region.x + desc.width) / (float)atlas_texture_.GetWidth();
    desc.t1 = (region.y + desc.height) / (float)atlas_texture_.GetHeight();

    glyphs_.push_back(desc);

    return true;
}

bool FontHandler::LoadGlyphs(const std::wstring &text_buffer)
{
    for (const auto &charcode : text_buffer)
    {
        auto it = std::find_if(std::begin(glyphs_),
                               std::end(glyphs_),
                               [&charcode](const GlyphDescriptor &glyph)
                               {
            return glyph.charcode == charcode;
        });
        if (it != std::end(glyphs_))
        {
            continue;
        }
        if (!LoadGlyph(charcode))
        {
            return false;
        }
    }
    atlas_texture_.UpdateTexture();
    return true;
}

void FontHandler::GenerateRenderDataForText(const std::wstring &text,
                                            unsigned int pen_x,
                                            unsigned int pen_y,
                                            std::vector<glm::vec4> &vertices,
                                            std::vector<glm::ivec3> &indices)
{
    std::vector<glm::vec4> data;
    bool new_gylph_loaded = false;

    for (const auto &charcode : text)
    {
        auto it = std::find_if(std::begin(glyphs_),
                               std::end(glyphs_),
                               [&charcode](const GlyphDescriptor &glyph)
                               {
            return glyph.charcode == charcode;
        });

        if (it == std::end(glyphs_))
        {
            if (!LoadGlyph(charcode))
            {
                std::cout << "Filed to load charcode: " << charcode << std::endl;
                continue;
            }
            new_gylph_loaded = true;
            it = std::end(glyphs_) - 1;
        }
        const auto &glyph = *it;

        // float kerning = 0.0f;
        // if (i > 0) {
        //     kerning = texture_glyph_get_kerning(glyph, text[i - 1]);
        // }
        // pen_x += kerning;

        float x0 = (pen_x + glyph.offset_x);
        float x1 = (x0 + glyph.width);

        // float y0 = (pen_y + glyph.offset_y);
        // float y1 = (y0 - glyph.height);

        float y0 = (pen_y - glyph.offset_y);
        float y1 = (y0 + glyph.height);

        pen_x += glyph.advance_x;

        vertices.push_back(glm::vec4(x0, y0, glyph.s0, glyph.t0));
        vertices.push_back(glm::vec4(x0, y1, glyph.s0, glyph.t1));
        vertices.push_back(glm::vec4(x1, y1, glyph.s1, glyph.t1));
        vertices.push_back(glm::vec4(x1, y0, glyph.s1, glyph.t0));

        unsigned int v0_offset = vertices.size() - 4;

        indices.push_back(glm::ivec3(v0_offset + 0, v0_offset + 1, v0_offset + 2));
        indices.push_back(glm::ivec3(v0_offset + 0, v0_offset + 2, v0_offset + 3));
    }

    if (new_gylph_loaded)
    {
        atlas_texture_.UpdateTexture();
    }
}

const std::string &FontHandler::FontName()
{
    return font_name_;
}

unsigned int FontHandler::FontSize()
{
    return font_size_;
}
