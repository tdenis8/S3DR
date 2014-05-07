#ifndef _ATLAS_TEXTURE_H_
#define _ATLAS_TEXTURE_H_

#include "open_gl/misc/base_texture.hpp"

#include <vector>
#include <memory>

struct Rectangle {
    int x;
    int y;
    int width;
    int height;
};

/// \brief ...
///
/// A texture atlas is used to pack several small regions into a single texture.
class AtlasTexture : public BaseTexture {
public:
    AtlasTexture() = delete;
    AtlasTexture(unsigned int width, unsigned int height);
    ~AtlasTexture();

    AtlasTexture(const AtlasTexture &) = delete;
    AtlasTexture &operator=(const AtlasTexture &) = delete;
    AtlasTexture(AtlasTexture &&);

    Rectangle GetRegion(unsigned int width, unsigned int height);
    void SetRegion(unsigned int x,
                   unsigned int y,
                   unsigned int width,
                   unsigned int height,
                   const unsigned char *data,
                   unsigned int stride);

    unsigned int GetWidth();
    unsigned int GetHeight();

    void UpdateTexture();

private:
    struct Node {
        int x;      // The starting x-coordinate (leftmost).
        int y;      // The y-coordinate of the skyline level line.
        int width;  // The line width. The ending coordinate (inclusive) will be x+width-1.
    };

    int RectangleFits(unsigned int index, unsigned int width, unsigned int height) const;
    void InsertNewNode(unsigned int best_index, const Rectangle &rectangle);
    void MergeNodes();

    unsigned int width_;                   // Width (in pixels) of the underlying texture
    unsigned int height_;                  // Height (in pixels) of the underlying texture
    unsigned int used_;                    // Allocated surface size
    std::unique_ptr<unsigned char> data_;  // Atlas data
    std::vector<Node> nodes_;              // Allocated nodes
};

#endif