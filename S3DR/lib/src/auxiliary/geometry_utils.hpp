#ifndef _GEOMETRY_UTILS_H_
#define _GEOMETRY_UTILS_H_

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <vector>

/// \brief Calculate normals
///
/// Calculate normals for given vertices(shared amoung triangles). Normals
/// vector should be initialized with vertices.size() * glm::vec3(0,0,0).
///
/// \param  vector of vertices for witch normals will be calculated
/// \param  vector of indices that describes connections between vertices
/// \param  reference to a vector where calculated normals will be saved
void CalculateNormals(const std::vector<glm::vec3>& vertices,
                      const std::vector<glm::ivec3>& indices,
                      std::vector<glm::vec3>& normals);

#endif