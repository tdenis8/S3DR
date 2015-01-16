#include "material_shell_adapter.hpp"

#define VERTICES_BUFFER 0
#define NORMALS_BUFFER 1
#define INDICES_BUFFER 2

MaterialShellAdapter::MaterialShellAdapter(MaterialShellObject& material_shell_object)
   : SceneObjectAdapter(material_shell_object), material_shell_object_(material_shell_object)
{
   glGenVertexArrays(1, &vao_object_);
   glGenBuffers(3, vbo_objects_);
   UpdateData();
}

MaterialShellAdapter::~MaterialShellAdapter()
{
   glDeleteVertexArrays(1, &vao_object_);
   glDeleteBuffers(3, vbo_objects_);
}

void MaterialShellAdapter::UpdateData()
{
   const MaterialShellData& material_shell_data = material_shell_object_.GetMaterialShellData();

   const std::vector<glm::vec3>& vertices = material_shell_data.vertices;
   const std::vector<glm::vec3>& normals = material_shell_data.normals;
   const std::vector<glm::ivec3>& indices = material_shell_data.indices;

   glBindVertexArray(vao_object_);

   glBindBuffer(GL_ARRAY_BUFFER, vbo_objects_[VERTICES_BUFFER]);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STREAM_DRAW);
   glEnableVertexAttribArray(0);
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

   glBindBuffer(GL_ARRAY_BUFFER, vbo_objects_[NORMALS_BUFFER]);
   glBufferData(GL_ARRAY_BUFFER, sizeof(normals[0]) * normals.size(), &normals[0], GL_STREAM_DRAW);
   glEnableVertexAttribArray(1);
   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_objects_[INDICES_BUFFER]);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STREAM_DRAW);

   glBindVertexArray(0);
}

void MaterialShellAdapter::SetMaterialPA(const Material& material)
{
   GLuint ambient_uniform = program_->GetUniform("material.ambient");
   glUniform3f(ambient_uniform, material.ambient[0], material.ambient[1], material.ambient[2]);

   GLuint diffuse_uniform = program_->GetUniform("material.diffuse");
   glUniform3f(diffuse_uniform, material.diffuse[0], material.diffuse[1], material.diffuse[2]);

   GLuint specular_uniform = program_->GetUniform("material.specular");
   glUniform3f(specular_uniform, material.specular[0], material.specular[1], material.specular[2]);

   GLuint shininess_uniform = program_->GetUniform("material.shininess");
   glUniform1f(shininess_uniform, material.shininess);
}

void MaterialShellAdapter::SetProgram(Program* program)
{
   program_ = program;
}

void MaterialShellAdapter::Render()
{
   glBindVertexArray(vao_object_);
   const std::vector<MaterialShellEntry>& entries = material_shell_object_.GetMaterialShellData().entries;
   for (auto iter = entries.begin(); iter != entries.end(); ++iter)
   {
      SetMaterialPA(iter->material);
      glDrawElementsBaseVertex(GL_TRIANGLES, iter->num_indices, GL_UNSIGNED_INT,
                               (void*)(sizeof(unsigned int) * iter->indices_offset), iter->vertices_offset);
   }
   glBindVertexArray(0);
}

void MaterialShellAdapter::SelectionRender(std::function<void(int)> set_scene_object_key,
                                           std::function<void(int)> set_entry_index)
{
   glBindVertexArray(vao_object_);
   set_scene_object_key(material_shell_object_.GetKey());
   const std::vector<MaterialShellEntry>& entries = material_shell_object_.GetMaterialShellData().entries;
   int entry = 0;
   for (auto iter = entries.begin(); iter != entries.end(); ++iter)
   {
      set_entry_index(entry++);
      glDrawElementsBaseVertex(GL_TRIANGLES, iter->num_indices, GL_UNSIGNED_INT,
                               (void*)(sizeof(unsigned int) * iter->indices_offset), iter->vertices_offset);
   }
   glBindVertexArray(0);
}