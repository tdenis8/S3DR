#include "point_adapter.hpp"

#define VERTICES_BUF    0
#define COLORS_BUF      1
#define INDICES_BUF     2

template <typename T, unsigned size>
inline unsigned ARRAY_SIZE(const T (&array)[size]) { return size; }

PointAdapter::PointAdapter(PointObject * point_object):
    SceneObjectAdapter(point_object),
    point_object(point_object)
{
    glGenVertexArrays(1, &vao_object);
    glGenBuffers(ARRAY_SIZE(vbo_objects), vbo_objects);
    UpdateData();
}

PointAdapter::~PointAdapter(){
    glDeleteVertexArrays(1, &vao_object);
    glDeleteBuffers(ARRAY_SIZE(vbo_objects), vbo_objects);
}

void PointAdapter::UpdateData(){
    const PointData & point_data = point_object->PointDataRef();
    
    const std::vector<glm::vec3> & vertices = point_data.vertices;
    const std::vector<glm::vec4> & colors   = point_data.colors;
    const std::vector<int> & indices = point_data.indices;

    glBindVertexArray(vao_object);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_objects[VERTICES_BUF]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STREAM_DRAW); // should use GL_STREAM_DRAW
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);    

    glBindBuffer(GL_ARRAY_BUFFER, vbo_objects[COLORS_BUF]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors[0]) * colors.size(), &colors[0], GL_STREAM_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_objects[INDICES_BUF]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STREAM_DRAW);

    glBindVertexArray(0);
}

void PointAdapter::Render(){
    glBindVertexArray(vao_object);
    const std::vector<PointEntry> & entries = point_object->PointDataRef().entries;
    for (auto iter = entries.begin(); iter != entries.end(); ++iter) {
        glPointSize(6);
        glDrawElementsBaseVertex(GL_POINTS, 
                                 iter->NumIndices, 
                                 GL_UNSIGNED_INT, 
                                 (void*)(sizeof(unsigned int) * iter->IndicesOffset), 
                                 iter->VertexOffset);
    }
    glBindVertexArray(0);
}

void PointAdapter::SelectionRender(std::function<void(int)> set_scene_object_key,
                                   std::function<void(int)> set_entry_index)
{
    glBindVertexArray(vao_object);
    set_scene_object_key(point_object->Key());
    const std::vector<PointEntry> & entries = point_object->PointDataRef().entries;
    int entry = 0;
    for (auto iter = entries.begin(); iter != entries.end(); ++iter) {
        set_entry_index(entry++);
        glPointSize(6);
        glDrawElementsBaseVertex(GL_POINTS, 
                                 iter->NumIndices, 
                                 GL_UNSIGNED_INT, 
                                 (void*)(sizeof(unsigned int) * iter->IndicesOffset), 
                                 iter->VertexOffset);
    }
    glBindVertexArray(0);
}