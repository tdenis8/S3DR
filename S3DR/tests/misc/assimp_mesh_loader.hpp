#ifndef _ASSIMP_MESH_LOADER_H_
#define _ASSIMP_MESH_LOADER_H_

#include "model/shell_object.hpp"
#include "model/texture_shell_object.hpp"

#include <string>
#include <memory>

void LoadAssimpMesh(const std::string & filename, const std::shared_ptr<ShellObject> & shell_object);
void LoadAssimpMesh(const std::string & filename, const std::shared_ptr<TextureShellObject> & texture_shell_object);


#endif