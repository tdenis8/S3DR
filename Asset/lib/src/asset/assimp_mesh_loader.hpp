#ifndef _ASSIMP_MESH_LOADER_H_
#define _ASSIMP_MESH_LOADER_H_

#include "model/material_shell_object.hpp"
#include "model/texture_shell_object.hpp"

#include <string>

void LoadAssimpMesh(const std::string& filename, MaterialShellObject& materialshell_object, const Material& material);
void LoadAssimpMesh(const std::string& filename, TextureShellObject& texture_shell_object);

#endif