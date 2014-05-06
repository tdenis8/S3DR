#include "text_adapter.hpp"

template <typename T, unsigned size>
inline unsigned ARRAY_SIZE(const T (&array)[size]) { return size; }

#define VERTICES_BUF    0
#define COLORS_BUF      1
#define INDICES_BUF     2

TextAdapter::TextAdapter(TextObject * text_object):
	SceneObjectAdapter(*text_object),
    text_object(text_object)
{
	glGenVertexArrays(1, &vao_object);
    glGenBuffers(ARRAY_SIZE(vbo_objects), vbo_objects);
    UpdateData();
}

TextAdapter::~TextAdapter(){
	glDeleteVertexArrays(1, &vao_object);
	glDeleteBuffers(ARRAY_SIZE(vbo_objects), vbo_objects);
}

void TextAdapter::UpdateData(){
	const LineData & line_data = text_object->LineDataRef();
	
	const std::vector<glm::vec3> & vertices = line_data.vertices;
    const std::vector<glm::vec4> & colors 	= line_data.colors;
    const std::vector<glm::ivec2> & indices = line_data.indices;

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

void TextAdapter::Render(){
    glBindVertexArray(vao_object);
    const std::vector<LineEntry> & entries = text_object->LineDataRef().entries;
    for (auto iter = entries.begin(); iter != entries.end(); ++iter) {
        glLineWidth(2);
        glDrawElementsBaseVertex(GL_LINES, 
                                 iter->NumIndices, 
                                 GL_UNSIGNED_INT, 
                                 (void*)(sizeof(unsigned int) * iter->IndicesOffset), 
                                 iter->VertexOffset);
    }
    glBindVertexArray(0);
}

void TextAdapter::SelectionRender(std::function<void(int)> set_scene_object_key,
                                  std::function<void(int)> set_entry_index)
{
    glBindVertexArray(vao_object);
    set_scene_object_key(text_object->GetKey());
    const std::vector<LineEntry> & entries = text_object->LineDataRef().entries;
    int entry = 0;
    for (auto iter = entries.begin(); iter != entries.end(); ++iter) {
        set_entry_index(entry++);
        glLineWidth(2);
        glDrawElementsBaseVertex(GL_LINES, 
                                 iter->NumIndices, 
                                 GL_UNSIGNED_INT, 
                                 (void*)(sizeof(unsigned int) * iter->IndicesOffset), 
                                 iter->VertexOffset);
    }
    glBindVertexArray(0);
}