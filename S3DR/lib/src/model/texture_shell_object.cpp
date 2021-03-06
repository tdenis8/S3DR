#include "texture_shell_object.hpp"

#include "auxiliary/geometry_utils.hpp"

TextureShellObject::TextureShellObject(SceneObject* parent, std::string name, int priority)
    : SceneObject(parent, name, priority)
{
}

TextureShellObject::~TextureShellObject()
{
}

void TextureShellObject::AppendData(const std::vector<glm::vec3>& vertices,
                                    const std::vector<glm::vec2>& texture_coords,
                                    const std::vector<glm::ivec3>& indices,
                                    const std::string& texture_path)
{
    // Calculate normals
    std::vector<glm::vec3> normals(vertices.size(), glm::vec3(0.0, 0.0, 0.0));
    CalculateNormals(vertices, indices, normals);

    AppendData(vertices, normals, texture_coords, indices, texture_path);
}

void TextureShellObject::AppendData(const std::vector<glm::vec3>& vertices,
                                    const std::vector<glm::vec3>& normals,
                                    const std::vector<glm::vec2>& texture_coords,
                                    const std::vector<glm::ivec3>& indices,
                                    const std::string& texture_path)
{
    TextureShellEntry new_entry = TextureShellEntry();
    new_entry.NumIndices = indices.size() * 3;
    new_entry.VertexOffset = texture_shell_data_.vertices.size();
    new_entry.IndicesOffset = texture_shell_data_.indices.size() * 3;

    texture_shell_data_.textures_paths.push_back(texture_path);
    new_entry.TextureIndex = texture_shell_data_.textures_paths.size() - 1;

    texture_shell_data_.entries.push_back(std::move(new_entry));

    // Copy vertices
    texture_shell_data_.vertices.reserve(texture_shell_data_.vertices.size() + vertices.size());
    texture_shell_data_.vertices.insert(texture_shell_data_.vertices.end(), vertices.begin(), vertices.end());

    // Copy normals
    texture_shell_data_.normals.reserve(texture_shell_data_.normals.size() + normals.size());
    texture_shell_data_.normals.insert(texture_shell_data_.normals.end(), normals.begin(), normals.end());

    // Copy texture_coords
    texture_shell_data_.texture_coords.reserve(texture_shell_data_.texture_coords.size() + texture_coords.size());
    texture_shell_data_.texture_coords.insert(
        texture_shell_data_.texture_coords.end(), texture_coords.begin(), texture_coords.end());

    // Copy indices
    texture_shell_data_.indices.reserve(texture_shell_data_.indices.size() + indices.size());
    texture_shell_data_.indices.insert(texture_shell_data_.indices.end(), indices.begin(), indices.end());

    Subject<SceneObjectEvents>::Emit(SceneObjectEvents::DATA_UPDATE);
}

const TextureShellData& TextureShellObject::GetTextureShellData()
{
    return texture_shell_data_;
}