#ifndef _MATERIAL_SHELL_RENDERER_H_
#define _MATERIAL_SHELL_RENDERER_H_

#include "scene_object_renderer.hpp"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <vector>

class MaterialShellAdapter;
class Material;

class MaterialShellRenderer : public SceneObjectRenderer
{
   public:
   MaterialShellRenderer();
   MaterialShellRenderer(const MaterialShellRenderer &) = delete;
   MaterialShellRenderer &operator=(const MaterialShellRenderer &) = delete;
   ~MaterialShellRenderer();

   void AttachMaterialShellAdapter(MaterialShellAdapter *material_shell_adapter);
   void DetachMaterialShellAdapter(MaterialShellAdapter *mateiral_shell_adapter);
   void Reset();

   void Render(const glm::mat4 &view, const glm::mat4 &projection, int priority);

   private:
   static std::vector<Shader> GetShaderList();

   void SetModelMatrixPA(const glm::mat4 &model);
   void SetProjectionViewMatrixPA(const glm::mat4 &projection_view);
   void SetNormalModelMatrixPA(const glm::mat3 &normal_model);

   std::vector<MaterialShellAdapter *> material_shell_adapters_[3];
};

#endif