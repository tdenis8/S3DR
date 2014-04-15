#ifndef _3D_SHAPES_H_
#define _3D_SHAPES_H_

#include "model/shell_object.hpp"

#include <memory>

/// \brief Generate a sphere
///
/// ...
///
/// \param  reference to a ShellObject whitch will hold the generated sphere
/// \param  center of the sphere 
/// \param  radius of the sphere
void GenerateSphere(ShellObject & shell_object,
					const glm::vec3 & center, 
                    float radius);

#endif