#include "atlas_texture.hpp"

#include <limits>
#include <cstring>

AtlasTexture::AtlasTexture(unsigned int width, unsigned int height)
    : BaseTexture()
    , width_(width)
    , height_(height)
    , used_(0)
    , data_(nullptr)
{
    data_.reset(new unsigned char[width_ * height_]);

    // We want a one pixel border around the whole atlas to avoid any artefact when
    // sampling texture
    nodes_.push_back(Node{1, 1, (int)width - 2});
}

AtlasTexture::~AtlasTexture()
{
}

AtlasTexture::AtlasTexture(AtlasTexture &&other)
    : BaseTexture(std::forward<AtlasTexture>(other))
    , width_(other.width_)
    , height_(other.height_)
    , used_(other.used_)
    , data_(std::move(other.data_))
    , nodes_(std::move(other.nodes_))
{
}

int AtlasTexture::RectangleFits(unsigned int index, unsigned int width, unsigned int height) const
{
    auto node = nodes_[index];

    if ((node.x + width) > (width_ - 1)) {
        return -1;
    }

    int y = node.y;
    int width_left = width;

    while (width_left > 0) {
        node = nodes_[index];

        if (node.y > y) {
            y = node.y;
        }

        if ((y + height) > (height_ - 1)) {
            return -1;
        }

        width_left -= node.width;
        ++index;

        if (index >= nodes_.size() && width_left > 0) {
            return -1;
        }
    }

    return y;
}

void AtlasTexture::InsertNewNode(unsigned int best_index, const Rectangle &rectangle)
{
    nodes_.insert(nodes_.begin() + best_index, Node({rectangle.x, rectangle.y + rectangle.height, rectangle.width}));

    for (unsigned int i = best_index + 1; i < nodes_.size(); ++i) {
        auto &node = nodes_[i];
        auto &prev_node = nodes_[i - 1];

        if (node.x < (prev_node.x + prev_node.width)) {
            int shrink = prev_node.x + prev_node.width - node.x;
            node.x += shrink;
            node.width -= shrink;

            if (node.width <= 0) {
                nodes_.erase(nodes_.begin() + i);
                --i;
            } else {
                break;
            }
        } else {
            break;
        }
    }
}

void AtlasTexture::MergeNodes()
{
    for (unsigned int i = 0; i < nodes_.size() - 1; ++i) {
        auto &node = nodes_[i];
        auto &next = nodes_[i + 1];

        if (node.y == next.y) {
            node.width += next.width;
            nodes_.erase(nodes_.begin() + (i + 1));
            --i;
        }
    }
}

Rectangle AtlasTexture::GetRegion(unsigned int width, unsigned int height)
{
    Rectangle new_rectangle({-1, -1, (int)width, (int)height});

    int best_height = std::numeric_limits<int>::max();
    int best_width = std::numeric_limits<int>::max();
    int best_index = -1;

    for (unsigned int i = 0; i < nodes_.size(); ++i) {
        int y = RectangleFits(i, width, height);
        if (y >= 0) {
            auto node = nodes_[i];
            if (((y + height) < best_height) || (((y + height) == best_height) && (node.width < best_width))) {
                best_height = y + height;
                best_width = node.width;
                best_index = i;
                new_rectangle.x = node.x;
                new_rectangle.y = y;
            }
        }
    }

    if (best_index == -1) {
        return new_rectangle;
    }

    InsertNewNode(best_index, new_rectangle);
    MergeNodes();

    return new_rectangle;
}

void AtlasTexture::SetRegion(unsigned int x,
                             unsigned int y,
                             unsigned int width,
                             unsigned int height,
                             const unsigned char *data,
                             unsigned int stride)
{
    for (unsigned int i = 0; i < height; ++i) {
        std::memcpy(data_.get() + ((y + i) * width_ + x) * sizeof(char),
                    data + (i * stride) * sizeof(char),
                    width * sizeof(char));
    }
}

unsigned int AtlasTexture::GetWidth()
{
    return width_;
}

unsigned int AtlasTexture::GetHeight()
{
    return height_;
}

void AtlasTexture::UpdateTexture()
{
    Bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width_, height_, 0, GL_RED, GL_UNSIGNED_BYTE, data_.get());
    UnBind();
}