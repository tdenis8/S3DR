#ifndef _GLYPH_DESCRIPTOR_H_
#define _GLYPH_DESCRIPTOR_H_

#include <vector>

/**
 * A structure that hold a kerning value relatively to a charcode.
 *
 * This structure cannot be used alone since the (necessary) right charcode is
 * implicitely held by the owner of this structure.
 */
struct KerningDescriptor {
    char16_t charcode;  // Left character code in the kern pair.
    float kerning;      // Kerning value (in fractional pixels).
};

/**
 * A structure that describe a glyph.
 */
struct GlyphDescriptor {
    wchar_t charcode;     // Wide character this glyph represents
    unsigned int width;   // Glyph's width in pixels.
    unsigned int height;  // Glyph's height in pixels.
    int offset_x;         // Glyph's left bearing expressed in integer pixels.
    int offset_y;         // Glyphs's top bearing expressed in integer pixels.
    float advance_x;      // For horizontal text layouts
    float advance_y;      // For vertical text layouts

    float s0;  // First normalized texture coordinate (x) of top-left corner
    float t0;  // Second normalized texture coordinate (y) of top-left corner
    float s1;  // First normalized texture coordinate (x) of bottom-right corner
    float t1;  // Second normalized texture coordinate (y) of bottom-right corner

    std::vector<KerningDescriptor> kerning;  // A vector of kerning pairs relative to this glyph.

    int outline_type;         // Glyph outline type (0 = None, 1 = line, 2 = inner, 3 = outer)
    float outline_thickness;  // Glyph outline thickness
};

/*
 * Glyph metrics:
 * --------------
 *
 *                       xmin                     xmax
 *                        |                         |
 *                        |<-------- width -------->|
 *                        |                         |
 *              |         +-------------------------+----------------- ymax
 *              |         |    ggggggggg   ggggg    |     ^        ^
 *              |         |   g:::::::::ggg::::g    |     |        |
 *              |         |  g:::::::::::::::::g    |     |        |
 *              |         | g::::::ggggg::::::gg    |     |        |
 *              |         | g:::::g     g:::::g     |     |        |
 *    offset_x -|-------->| g:::::g     g:::::g     |  offset_y    |
 *              |         | g:::::g     g:::::g     |     |        |
 *              |         | g::::::g    g:::::g     |     |        |
 *              |         | g:::::::ggggg:::::g     |     |        |
 *              |         |  g::::::::::::::::g     |     |      height
 *              |         |   gg::::::::::::::g     |     |        |
 *  baseline ---*---------|---- gggggggg::::::g-----*--------      |
 *            / |         |             g:::::g     |              |
 *     origin   |         | gggggg      g:::::g     |              |
 *              |         | g:::::gg   gg:::::g     |              |
 *              |         |  g::::::ggg:::::::g     |              |
 *              |         |   gg:::::::::::::g      |              |
 *              |         |     ggg::::::ggg        |              |
 *              |         |         gggggg          |              v
 *              |         +-------------------------+----------------- ymin
 *              |                                   |
 *              |------------- advance_x ---------->|
 */
#endif
