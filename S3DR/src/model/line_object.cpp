#include "line_object.hpp"

LineObject::LineObject(SceneObject * parent, std::string name, int priority):
    SceneObject(parent, name, priority)
{

}

LineObject::~LineObject(){

}

void LineObject::AppendData(const std::vector<glm::vec3> & vertices,
                             const std::vector<glm::vec4> & colors,
                             const std::vector<glm::ivec2> & indices)
{
    LineEntry new_entry = LineEntry();
    new_entry.NumIndices = indices.size() * 2;
    new_entry.VertexOffset = line_data.vertices.size();
    new_entry.IndicesOffset = line_data.indices.size() * 2;
    line_data.entries.push_back(std::move(new_entry));

    // Copy vertices
    line_data.vertices.reserve(line_data.vertices.size() + vertices.size());
    line_data.vertices.insert(line_data.vertices.end(), vertices.begin(), vertices.end());

    // Copy colors
    line_data.colors.reserve(line_data.colors.size() + colors.size());
    line_data.colors.insert(line_data.colors.end(), colors.begin(), colors.end());

    // Copy indices
    line_data.indices.reserve(line_data.indices.size() + indices.size());
    line_data.indices.insert(line_data.indices.end(), indices.begin(), indices.end());

    Emit(SceneObjectEvents::DATA_UPDATE);
}

const LineData & LineObject::LineDataRef(){
    return line_data;
}