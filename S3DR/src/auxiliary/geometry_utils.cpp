#include "geometry_utils.hpp"

#include "utility/math_utils.hpp"

void CalculateNormals(const std::vector<glm::vec3> & vertices, 
                      const std::vector<glm::ivec3> & indices,
                      std::vector<glm::vec3>  & normals)
{
    for(const auto & it: indices){
        int i1 = it.x;
        int i2 = it.y;
        int i3 = it.z;
       
        const glm::vec3 & v1 = vertices.at(i1);
        const glm::vec3 & v2 = vertices.at(i2);
        const glm::vec3 & v3 = vertices.at(i3);

        // Note: order of vectors in cross function is important
        glm::vec3 n1 = glm::cross(glm::normalize(v2-v1), glm::normalize(v3-v1));
        n1 = glm::normalize(n1);
        normals[i1] = n1 + normals[i1];

        glm::vec3 n2 = glm::cross(glm::normalize(v3-v2), glm::normalize(v1-v2));
        n2 = glm::normalize(n2);
        normals[i2] = n2 + normals[i2];

        glm::vec3 n3 = glm::cross(glm::normalize(v1-v3), glm::normalize(v2-v3));
        n3 = glm::normalize(n3);
        normals[i3] = n3 + normals[i3];
    }

    for(auto & n: normals){
        if(n.x + n.y + n.z == 0.0){
            continue;
        }
        n = glm::normalize(n);
    }
}