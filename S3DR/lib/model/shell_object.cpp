#include "shell_object.hpp"

#include "auxiliary/geometry_utils.hpp"

ShellObject::ShellObject(SceneObject * parent, std::string name, int priority):
    SceneObject(parent, name, priority)
{

}

ShellObject::~ShellObject(){

}

void ShellObject::AppendData(const std::vector<glm::vec3> & vertices,
                             const std::vector<glm::vec4> & colors,
                             const std::vector<glm::ivec3> & indices)
{
    // Calculate and copy normals
    std::vector<glm::vec3> normals(vertices.size(), glm::vec3(0.0, 0.0, 0.0));
    CalculateNormals(vertices, indices, normals); 
     
    AppendData(vertices, normals, colors, indices);  
}

void ShellObject::AppendData(const std::vector<glm::vec3> & vertices,
                             const std::vector<glm::vec3> & normals,
                             const std::vector<glm::vec4> & colors,
                             const std::vector<glm::ivec3> & indices)
{
    ShellEntry new_entry = ShellEntry();
    new_entry.NumIndices = indices.size() * 3;
    new_entry.VertexOffset = shell_data.vertices.size() ;
    new_entry.IndicesOffset = shell_data.indices.size() * 3;
    shell_data.entries.push_back(std::move(new_entry));

    // Copy vertices
    shell_data.vertices.reserve(shell_data.vertices.size() + vertices.size());
    shell_data.vertices.insert(shell_data.vertices.end(), vertices.begin(), vertices.end());

    // Copy normals
    shell_data.normals.reserve(shell_data.normals.size() + normals.size());
    shell_data.normals.insert(shell_data.normals.end(), normals.begin(), normals.end());

    // Copy colors
    shell_data.colors.reserve(shell_data.colors.size() + colors.size());
    shell_data.colors.insert(shell_data.colors.end(), colors.begin(), colors.end());

    // Copy indices
    shell_data.indices.reserve(shell_data.indices.size() + indices.size());
    shell_data.indices.insert(shell_data.indices.end(), indices.begin(), indices.end());

    Emit(SceneObjectEvents::DATA_UPDATE);
}

void ShellObject::Highlight(bool highlight){
    if(highlight){
        shell_material.status = 1;
    }
    else{
        shell_material.status = 0;
    }
}

const ShellData & ShellObject::ShellDataRef(){
    return shell_data;
}

const ShellMaterial & ShellObject::ShellMaterialRef(){
    return shell_material;
}