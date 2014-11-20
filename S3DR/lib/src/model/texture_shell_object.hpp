#ifndef _TEXTURE_SHELL_OBJECT_H_
#define _TEXTURE_SHELL_OBJECT_H_

#include "scene_object.hpp"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <string>
#include <vector>
#include <memory>

struct TextureShellEntry
{
    unsigned int NumIndices = 0;
    unsigned int VertexOffset = 0;
    unsigned int IndicesOffset = 0;
    unsigned int TextureIndex = 0;
};

struct TextureShellData
{
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texture_coords;
    std::vector<glm::ivec3> indices;
    std::vector<TextureShellEntry> entries;
    std::vector<std::string> textures_paths;
};

class TextureShellObject : public SceneObject
{
    public:
    TextureShellObject() = delete;
    explicit TextureShellObject(SceneObject *parent, std::string name, int priority = 1);
    TextureShellObject(const TextureShellObject &) = delete;
    TextureShellObject &operator=(const TextureShellObject &) = delete;
    ~TextureShellObject();

    void AppendData(const std::vector<glm::vec3> &vertices,
                    const std::vector<glm::vec2> &texture_coords,
                    const std::vector<glm::ivec3> &indices,
                    const std::string &texture_path);

    void AppendData(const std::vector<glm::vec3> &vertices,
                    const std::vector<glm::vec3> &normals,
                    const std::vector<glm::vec2> &texture_coords,
                    const std::vector<glm::ivec3> &indices,
                    const std::string &texture_path);

    const TextureShellData &GetTextureShellData();

    private:
    TextureShellData texture_shell_data_;
};

#endif
