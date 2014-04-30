#ifndef _ASSIMP_MESH_LOADER_H_
#define _ASSIMP_MESH_LOADER_H_

#include "model/shell_object.hpp"
#include "model/texture_shell_object.hpp"

#include <string>

void LoadAssimpMesh(const std::string & filename, ShellObject & shell_object);
void LoadAssimpMesh(const std::string & filename, TextureShellObject & texture_shell_object);


#endif