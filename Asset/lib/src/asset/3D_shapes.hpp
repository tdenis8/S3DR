#ifndef _3D_SHAPES_H_
#define _3D_SHAPES_H_

#include "model/shell_object.hpp"

#include <vector>

/// \brief Generate a sphere
///
/// ...
///
/// \param  center of the sphere 
/// \param  radius of the sphere
/// \param  ....
/// \param  ....
void GenerateSphere(const glm::vec3 & center, 
                    float radius,
                    std::vector<glm::vec3> & vertices,
                    std::vector<glm::ivec3> & indices);
#endif