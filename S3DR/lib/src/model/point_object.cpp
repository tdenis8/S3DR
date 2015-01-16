#include "point_object.hpp"

PointObject::PointObject(SceneObject* parent, std::string name, int priority) : SceneObject(parent, name, priority)
{
}

PointObject::~PointObject()
{
}

void PointObject::AppendData(const std::vector<glm::vec3>& vertices,
                             const std::vector<glm::vec4>& colors,
                             const std::vector<int>& indices)
{
    PointEntry new_entry = PointEntry();
    new_entry.NumIndices = indices.size() * 1;
    new_entry.VertexOffset = point_data_.vertices.size();
    new_entry.IndicesOffset = point_data_.indices.size() * 1;
    point_data_.entries.push_back(std::move(new_entry));

    // Copy vertices
    point_data_.vertices.reserve(point_data_.vertices.size() + vertices.size());
    point_data_.vertices.insert(point_data_.vertices.end(), vertices.begin(), vertices.end());

    // Copy colors
    point_data_.colors.reserve(point_data_.colors.size() + colors.size());
    point_data_.colors.insert(point_data_.colors.end(), colors.begin(), colors.end());

    // Copy indices
    point_data_.indices.reserve(point_data_.indices.size() + indices.size());
    point_data_.indices.insert(point_data_.indices.end(), indices.begin(), indices.end());

    Subject<SceneObjectEvents>::Emit(SceneObjectEvents::DATA_UPDATE);
}

const PointData& PointObject::GetPointData()
{
    return point_data_;
}