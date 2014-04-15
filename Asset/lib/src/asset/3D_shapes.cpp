#include "3D_shapes.hpp"

void GenerateSphere(ShellObject & shell_object,
                    const glm::vec3 & center, 
                    float radius)
{
	constexpr unsigned int NUM_OF_ITERATIONS = 4;
	std::vector<glm::vec3> vertices;
    std::vector<glm::ivec3> indices;
    std::vector<glm::ivec3> temp_indices1;
    std::vector<glm::ivec3> temp_indices2;

    glm::vec3 p[6] = {glm::vec3(0,0,1), glm::vec3(0,0,-1), glm::vec3(-1,-1,0),
                      glm::vec3(1,-1,0), glm::vec3(1,1,0), glm::vec3(-1,1,0)};
    
    double a = 1 / sqrt(2.0);
    for (int i=0; i<6; ++i) {
        p[i].x *= a;
        p[i].y *= a;
        vertices.push_back(p[i] * radius + center);
    }

    temp_indices1.push_back(glm::ivec3(0, 3, 4));
    temp_indices1.push_back(glm::ivec3(0, 4, 5));
    temp_indices1.push_back(glm::ivec3(0, 5, 2));
    temp_indices1.push_back(glm::ivec3(0, 2, 3));
    temp_indices1.push_back(glm::ivec3(1, 4, 3));
    temp_indices1.push_back(glm::ivec3(1, 5, 4));
    temp_indices1.push_back(glm::ivec3(1, 2, 5));
    temp_indices1.push_back(glm::ivec3(1, 3, 2));

    for (int it=0; it<NUM_OF_ITERATIONS; ++it) {
        // Divide all triangles (from a one triangle create four triangles)
        temp_indices2.clear();
        int number_of_triangles = temp_indices1.size();
        for (int i=0; i<number_of_triangles; ++i) {
            int i1 = temp_indices1[i].x;
            int i2 = temp_indices1[i].y;
            int i3 = temp_indices1[i].z;

            glm::vec3 pa = (vertices[i2] - vertices[i1]) * float(0.5) + vertices[i1];
            glm::vec3 pb = (vertices[i3] - vertices[i2]) * float(0.5) + vertices[i2];
            glm::vec3 pc = (vertices[i1] - vertices[i3]) * float(0.5) + vertices[i3];

            vertices.push_back(glm::normalize(pa -center)  * radius + center);
            vertices.push_back(glm::normalize(pb -center)  * radius + center);
            vertices.push_back(glm::normalize(pc -center)  * radius + center);

            int ia = vertices.size()-3;
            int ib = vertices.size()-2;
            int ic = vertices.size()-1;

            temp_indices2.push_back(glm::ivec3(i1, ia, ic));
            temp_indices2.push_back(glm::ivec3(ia, i2, ib));
            temp_indices2.push_back(glm::ivec3(ib, i3, ic));
            temp_indices2.push_back(glm::ivec3(ia, ib, ic));
        }
        temp_indices1 = temp_indices2;
    }
    indices = temp_indices1;

    std::vector<glm::vec4> colors(vertices.size(), glm::vec4(0.5, 0.5, 0.0, 1.0));
    shell_object.AppendData(vertices, colors, indices);
}