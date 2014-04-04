#ifndef _3D_SHAPES_H_
#define _3D_SHAPES_H_

#include "model/shell_object.hpp"

#include <memory>

/// \brief Generate a sphere
///
/// ...
///
/// \param  center of the sphere 
/// \param  radius of the sphere
/// \param  reference to a ShellObject whitch will hold the generated sphere
void GenerateSphereData(const glm::vec3 & center, 
                        float radius, 
					    const std::shared_ptr<ShellObject> & shell_object);

#endif