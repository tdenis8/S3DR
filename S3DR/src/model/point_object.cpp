#include "point_object.hpp"

PointObject::PointObject(SceneObject * parent, std::string name, int priority):
    SceneObject(parent, name, priority)
{

}

PointObject::~PointObject(){

}

void PointObject::AppendData(const std::vector<glm::vec3> & vertices,
                             const std::vector<glm::vec4> & colors,
                             const std::vector<int> & indices)
{
    PointEntry new_entry = PointEntry();
    new_entry.NumIndices = indices.size() * 1;
    new_entry.VertexOffset = point_data.vertices.size();
    new_entry.IndicesOffset = point_data.indices.size() * 1;
    point_data.entries.push_back(std::move(new_entry));

    // Copy vertices
    point_data.vertices.reserve(point_data.vertices.size() + vertices.size());
    point_data.vertices.insert(point_data.vertices.end(), vertices.begin(), vertices.end());

    // Copy colors
    point_data.colors.reserve(point_data.colors.size() + colors.size());
    point_data.colors.insert(point_data.colors.end(), colors.begin(), colors.end());

    // Copy indices
    point_data.indices.reserve(point_data.indices.size() + indices.size());
    point_data.indices.insert(point_data.indices.end(), indices.begin(), indices.end());

    Emit(SceneObjectEvents::DATA_UPDATE);
}

const PointData & PointObject::PointDataRef(){
    return point_data;
}