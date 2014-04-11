#include "texture_shell_adapter.hpp"

#include "../misc/texture.hpp"
#include <iostream>

template <typename T, unsigned size>
inline unsigned ARRAY_SIZE(const T (&array)[size]) { return size; }

#define VERTICES_BUF    0
#define NORMALS_BUF     1
#define TEX_COORDS_BUF  2
#define INDICES_BUF     3

TextureShellAdapter::TextureShellAdapter(TextureShellObject * texture_shell_object):
	SceneObjectAdapter(*texture_shell_object),
    texture_shell_object(texture_shell_object),
    allow_render(true)
{
	glGenVertexArrays(1, &vao_object);
    glGenBuffers(ARRAY_SIZE(vbo_objects), vbo_objects);
    UpdateData();
}

TextureShellAdapter::~TextureShellAdapter(){
	glDeleteVertexArrays(1, &vao_object);
	glDeleteBuffers(ARRAY_SIZE(vbo_objects), vbo_objects);
}

void TextureShellAdapter::UpdateData(){
	// Update shell data
    const TextureShellData & texture_shell_data = texture_shell_object->TextureShellDataRef();

	const std::vector<glm::vec3> & vertices = texture_shell_data.vertices;
    const std::vector<glm::vec3> & normals 	= texture_shell_data.normals;
    const std::vector<glm::vec2> & texture_coords 	= texture_shell_data.texture_coords;
    const std::vector<glm::ivec3> & indices = texture_shell_data.indices;

    glBindVertexArray(vao_object);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_objects[VERTICES_BUF]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STREAM_DRAW); // should use GL_STREAM_DRAW
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);    

    glBindBuffer(GL_ARRAY_BUFFER, vbo_objects[NORMALS_BUF]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normals[0]) * normals.size(), &normals[0], GL_STREAM_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_objects[TEX_COORDS_BUF]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texture_coords[0]) * texture_coords.size(), &texture_coords[0], GL_STREAM_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_objects[INDICES_BUF]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STREAM_DRAW);

    glBindVertexArray(0);

    // Update textures
    const std::vector<TextureShellEntry> & entries = texture_shell_object->TextureShellDataRef().entries;
    if(textures.size() != entries.size()){
        for(int i = textures.size(); i<entries.size(); ++i){
            int texture_index = entries[i].TextureIndex; 
            std::string texture_path = texture_shell_data.textures_paths[texture_index];
            Texture texture = Texture(texture_path);
            if(texture.Load()){
                textures.push_back(texture);
                std::cout<<"*** INFO: Loaded texture: "<<texture_path<<std::endl;
            }
            else{
                std::cout<<"*** ERROR: Filed to load texture: "<<texture_path<<std::endl;
                allow_render = false;
            }
        }
    }
}

void TextureShellAdapter::Render(){
    if(!allow_render){
        return;
    }
    glBindVertexArray(vao_object);
    const std::vector<TextureShellEntry> & entries = texture_shell_object->TextureShellDataRef().entries;
    for (auto iter = entries.begin(); iter != entries.end(); ++iter) {
        textures[iter->TextureIndex].Bind(GL_TEXTURE0);

        glDrawElementsBaseVertex(GL_TRIANGLES, 
                                 iter->NumIndices, 
                                 GL_UNSIGNED_INT, 
                                 (void*)(sizeof(unsigned int) * iter->IndicesOffset), 
                                 iter->VertexOffset);
    }
    glBindVertexArray(0);
}

void TextureShellAdapter::SelectionRender(std::function<void(int)> set_scene_object_key,
                                          std::function<void(int)> set_entry_index)
{
    if(!allow_render){
        return;
    }
    glBindVertexArray(vao_object);
    set_scene_object_key(texture_shell_object->GetKey());
    const std::vector<TextureShellEntry> & entries = texture_shell_object->TextureShellDataRef().entries;
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