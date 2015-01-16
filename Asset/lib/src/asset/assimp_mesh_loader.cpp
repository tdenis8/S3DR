#include "assimp_mesh_loader.hpp"

#include "utility/file_utils.hpp"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>

void LoadAssimpMesh(const std::string& filename, MaterialShellObject& material_shell_object, const Material& material)
{
   Assimp::Importer Importer;
   const aiScene* scene =
      Importer.ReadFile(filename.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

   if (scene)
   {
      std::vector<glm::vec3> points;
      std::vector<glm::vec3> normals;
      std::vector<glm::ivec3> indices;

      for (unsigned int i = 0; i < scene->mNumMeshes; i++)
      {
         const aiMesh* mesh = scene->mMeshes[i];
         points.clear();
         points.reserve(mesh->mNumVertices);
         normals.clear();
         normals.reserve(mesh->mNumVertices);
         indices.clear();
         indices.reserve(mesh->mNumFaces);

         for (unsigned int i = 0; i < mesh->mNumVertices; i++)
         {
            const aiVector3D* pPos = &(mesh->mVertices[i]);
            const aiVector3D* pNormal = &(mesh->mNormals[i]);

            points.push_back(glm::vec3(pPos->x, pPos->y, pPos->z));
            normals.push_back(glm::vec3(pNormal->x, pNormal->y, pNormal->z));
         }

         for (unsigned int i = 0; i < mesh->mNumFaces; i++)
         {
            const aiFace& Face = mesh->mFaces[i];
            assert(Face.mNumIndices == 3);
            indices.push_back(glm::ivec3(Face.mIndices[0], Face.mIndices[1], Face.mIndices[2]));
         }
         material_shell_object.AppendData(points, normals, indices, material);
      }
   }
   else
   {
      std::cerr << "*** Error parsing: " << filename.c_str() << " : " << Importer.GetErrorString() << std::endl;
   }
}

void LoadAssimpMesh(const std::string& filename, TextureShellObject& texture_shell_object)
{
   Assimp::Importer Importer;
   const aiScene* scene =
      Importer.ReadFile(filename.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

   if (scene)
   {
      std::vector<glm::vec3> points;
      std::vector<glm::vec3> normals;
      std::vector<glm::vec2> tex_coords;
      std::vector<glm::ivec3> indices;

      const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

      for (unsigned int i = 0; i < scene->mNumMeshes; i++)
      {
         const aiMesh* mesh = scene->mMeshes[i];
         points.clear();
         points.reserve(mesh->mNumVertices);
         normals.clear();
         normals.reserve(mesh->mNumVertices);
         tex_coords.clear();
         tex_coords.reserve(mesh->mNumVertices);
         indices.clear();
         indices.reserve(mesh->mNumFaces);

         for (unsigned int i = 0; i < mesh->mNumVertices; i++)
         {
            const aiVector3D* pPos = &(mesh->mVertices[i]);
            const aiVector3D* pNormal = &(mesh->mNormals[i]);
            const aiVector3D* pTexCoord = mesh->HasTextureCoords(0) ? &(mesh->mTextureCoords[0][i]) : &Zero3D;

            points.push_back(glm::vec3(pPos->x, pPos->y, pPos->z));
            normals.push_back(glm::vec3(pNormal->x, pNormal->y, pNormal->z) * float(-1.0));
            tex_coords.push_back(glm::vec2(pTexCoord->x, pTexCoord->y));
         }

         for (unsigned int i = 0; i < mesh->mNumFaces; i++)
         {
            const aiFace& Face = mesh->mFaces[i];
            assert(Face.mNumIndices == 3);
            indices.push_back(glm::ivec3(Face.mIndices[0], Face.mIndices[1], Face.mIndices[2]));
         }

         int material_index = mesh->mMaterialIndex;
         const aiMaterial* pMaterial = scene->mMaterials[material_index];

         if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
         {
            aiString Path;

            if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
            {
               std::string FullPath = FileDirFormFileName(filename) + "/" + Path.data;
               std::cout << "Found texture: " << FullPath.c_str() << std::endl;
               texture_shell_object.AppendData(points, normals, tex_coords, indices, FullPath.c_str());
            }
         }
      }
   }
   else
   {
      std::cerr << "*** Error parsing: " << filename.c_str() << " : " << Importer.GetErrorString() << std::endl;
   }
}
