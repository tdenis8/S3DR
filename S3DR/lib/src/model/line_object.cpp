#include "line_object.hpp"

LineObject::LineObject(SceneObject* parent, std::string name, int priority) : SceneObject(parent, name, priority)
{
}

LineObject::~LineObject()
{
}

void LineObject::AppendData(const std::vector<glm::vec3>& vertices,
                            const std::vector<glm::vec4>& colors,
                            const std::vector<glm::ivec2>& indices)
{
    LineEntry new_entry = LineEntry();
    new_entry.NumIndices = indices.size() * 2;
    new_entry.VertexOffset = line_data_.vertices.size();
    new_entry.IndicesOffset = line_data_.indices.size() * 2;
    line_data_.entries.push_back(std::move(new_entry));

    // Copy vertices
    line_data_.vertices.reserve(line_data_.vertices.size() + vertices.size());
    line_data_.vertices.insert(line_data_.vertices.end(), vertices.begin(), vertices.end());

    // Copy colors
    line_data_.colors.reserve(line_data_.colors.size() + colors.size());
    line_data_.colors.insert(line_data_.colors.end(), colors.begin(), colors.end());

    // Copy indices
    line_data_.indices.reserve(line_data_.indices.size() + indices.size());
    line_data_.indices.insert(line_data_.indices.end(), indices.begin(), indices.end());

    Emit(SceneObjectEvents::DATA_UPDATE);
}

const LineData& LineObject::GetLineData()
{
    return line_data_;
}