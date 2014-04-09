#include "shell_adapter.hpp"

template <typename T, unsigned size>
inline unsigned ARRAY_SIZE(const T (&array)[size]) { return size; }

#define VERTICES_BUF    0
#define NORMALS_BUF     1
#define COLORS_BUF      2
#define INDICES_BUF     3

ShellAdapter::ShellAdapter(ShellObject * shell_object):
	SceneObjectAdapter(shell_object),
    shell_object(shell_object)
{
	glGenVertexArrays(1, &vao_object);
    glGenBuffers(ARRAY_SIZE(vbo_objects), vbo_objects);
    UpdateData();
}

ShellAdapter::~ShellAdapter(){
	glDeleteVertexArrays(1, &vao_object);
	glDeleteBuffers(ARRAY_SIZE(vbo_objects), vbo_objects);
}

void ShellAdapter::UpdateData(){
	const ShellData & shell_data = shell_object->ShellDataRef();
	
	const std::vector<glm::vec3> & vertices = shell_data.vertices;
    const std::vector<glm::vec3> & normals 	= shell_data.normals;
    const std::vector<glm::vec4> & colors 	= shell_data.colors;
    const std::vector<glm::ivec3> & indices = shell_data.indices;

    glBindVertexArray(vao_object);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_objects[VERTICES_BUF]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STREAM_DRAW); // should use GL_STREAM_DRAW
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);    

    glBindBuffer(GL_ARRAY_BUFFER, vbo_objects[NORMALS_BUF]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normals[0]) * normals.size(), &normals[0], GL_STREAM_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_objects[COLORS_BUF]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors[0]) * colors.size(), &colors[0], GL_STREAM_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_objects[INDICES_BUF]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STREAM_DRAW);

    glBindVertexArray(0);
}

void ShellAdapter::Render(){
    glBindVertexArray(vao_object);
    const std::vector<ShellEntry> & entries = shell_object->ShellDataRef().entries;
    for (auto iter = entries.begin(); iter != entries.end(); ++iter) {
        glDrawElementsBaseVertex(GL_TRIANGLES, 
                                 iter->NumIndices, 
                                 GL_UNSIGNED_INT, 
                                 (void*)(sizeof(unsigned int) * iter->IndicesOffset), 
                                 iter->VertexOffset);
    }
    glBindVertexArray(0);
}

void ShellAdapter::SelectionRender(std::function<void(int)> set_scene_object_key,
                                   std::function<void(int)> set_entry_index)
{
    glBindVertexArray(vao_object);
    set_scene_object_key(shell_object->Key());
    const std::vector<ShellEntry> & entries = shell_object->ShellDataRef().entries;
    int entry = 0;
    for (auto iter = entries.begin(); iter != entries.end(); ++iter) {
        set_entry_index(entry++);
        glDrawElementsBaseVertex(GL_TRIANGLES, 
                                 iter->NumIndices, 
                                 GL_UNSIGNED_INT, 
                                 (void*)(sizeof(unsigned int) * iter->IndicesOffset), 
                                 iter->VertexOffset);
    }
    glBindVertexArray(0);
}