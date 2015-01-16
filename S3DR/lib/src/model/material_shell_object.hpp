#ifndef _MATERIAL_SHELL_OBJECT_H_
#define _MATERIAL_SHELL_OBJECT_H_

#include "scene_object.hpp"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <string>
#include <vector>
#include <memory>

// ShellType: MATERIAL -> every shell entry have uniform or some material
struct Material
{
   glm::vec3 ambient = glm::vec3(0.5, 0.5, 0.5);  // For now ambient component is ignored
   glm::vec3 diffuse = glm::vec3(0.5, 0.5, 0.5);
   glm::vec3 specular = glm::vec3(0.5, 0.5, 0.5);
   float shininess = 32.0f;  // Must be bigger than 0.0
};

struct MaterialShellEntry
{
   unsigned int num_indices = 0;
   unsigned int vertices_offset = 0;
   unsigned int indices_offset = 0;
   Material material;
};

struct MaterialShellData
{
   std::vector<glm::vec3> vertices;
   std::vector<glm::vec3> normals;
   std::vector<glm::ivec3> indices;
   std::vector<MaterialShellEntry> entries;
};

class MaterialShellObject : public SceneObject
{
   public:
   MaterialShellObject() = delete;
   explicit MaterialShellObject(SceneObject *parent, std::string name, int priority);
   MaterialShellObject(const MaterialShellObject &) = delete;
   MaterialShellObject &operator=(const MaterialShellObject &) = delete;
   ~MaterialShellObject();

   void AppendData(const std::vector<glm::vec3> &vertices, const std::vector<glm::ivec3> &indices, const Material &material);

   void AppendData(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec3> &normals,
                   const std::vector<glm::ivec3> &indices, const Material &material);

   void Highlight(bool highlight);

   const MaterialShellData &GetMaterialShellData();

   private:
   MaterialShellData material_shell_data_;
};

#endif
