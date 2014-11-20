#ifndef _POINT_OBJECT_H_
#define _POINT_OBJECT_H_

#include "scene_object.hpp"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <string>
#include <vector>
#include <memory>

struct PointEntry
{
    unsigned int NumIndices = 0;
    unsigned int VertexOffset = 0;
    unsigned int IndicesOffset = 0;
};

struct PointData
{
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec4> colors;
    std::vector<int> indices;
    std::vector<PointEntry> entries;
};

class PointObject : public SceneObject
{
    public:
    PointObject() = delete;
    explicit PointObject(SceneObject *parent, std::string name, int priority = 1);
    PointObject(const PointObject &) = delete;
    PointObject &operator=(const PointObject &) = delete;
    ~PointObject();

    void AppendData(const std::vector<glm::vec3> &vertices,
                    const std::vector<glm::vec4> &colors,
                    const std::vector<int> &indices);

    const PointData &GetPointData();

    private:
    PointData point_data_;
};

#endif