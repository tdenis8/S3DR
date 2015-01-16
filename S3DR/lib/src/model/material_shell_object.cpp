#include "material_shell_object.hpp"

#include "auxiliary/geometry_utils.hpp"

MaterialShellObject::MaterialShellObject(SceneObject* parent, std::string name, int priority)
    : SceneObject(parent, name, priority)
{
}

MaterialShellObject::~MaterialShellObject()
{
}

void MaterialShellObject::AppendData(const std::vector<glm::vec3>& vertices,
                                     const std::vector<glm::ivec3>& indices,
                                     const Material& material)
{
    // Calculate and copy normals
    std::vector<glm::vec3> normals(vertices.size(), glm::vec3(0.0, 0.0, 0.0));
    CalculateNormals(vertices, indices, normals);

    AppendData(vertices, normals, indices, material);
}

void MaterialShellObject::AppendData(const std::vector<glm::vec3>& vertices,
                                     const std::vector<glm::vec3>& normals,
                                     const std::vector<glm::ivec3>& indices,
                                     const Material& material)
{
    MaterialShellEntry new_material_shell_entry = MaterialShellEntry();
    new_material_shell_entry.num_indices = indices.size() * 3;
    new_material_shell_entry.vertices_offset = material_shell_data_.vertices.size();
    new_material_shell_entry.indices_offset = material_shell_data_.indices.size() * 3;
    new_material_shell_entry.material = material;

    material_shell_data_.entries.push_back(std::move(new_material_shell_entry));

    // Copy vertices
    material_shell_data_.vertices.reserve(material_shell_data_.vertices.size() + vertices.size());
    material_shell_data_.vertices.insert(material_shell_data_.vertices.end(), vertices.begin(), vertices.end());

    // Copy normals
    material_shell_data_.normals.reserve(material_shell_data_.normals.size() + normals.size());
    material_shell_data_.normals.insert(material_shell_data_.normals.end(), normals.begin(), normals.end());

    // Copy indices
    material_shell_data_.indices.reserve(material_shell_data_.indices.size() + indices.size());
    material_shell_data_.indices.insert(material_shell_data_.indices.end(), indices.begin(), indices.end());

    Subject<SceneObjectEvents>::Emit(SceneObjectEvents::DATA_UPDATE);
}

void MaterialShellObject::Highlight(bool highlight)
{
}

const MaterialShellData& MaterialShellObject::GetMaterialShellData()
{
    return material_shell_data_;
}