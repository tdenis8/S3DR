#ifndef _LINE_OBJECT_H_
#define _LINE_OBJECT_H_

#include "scene_object.hpp"

#include <glm/glm.hpp>

#include <string>
#include <vector>
#include <memory>

struct LineEntry {
    unsigned int NumIndices = 0;
    unsigned int VertexOffset = 0;
    unsigned int IndicesOffset = 0;
};

struct LineData {
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec4> colors;
    std::vector<glm::ivec2> indices;
    std::vector<LineEntry> entries;
};

class LineObject : public SceneObject {
    public:
        LineObject()=delete;
        explicit LineObject(SceneObject * parent, std::string name, int priority = 1);
        LineObject(const LineObject &)=delete;
        LineObject & operator=(const LineObject &)=delete;
        virtual ~LineObject();

        void AppendData(const std::vector<glm::vec3> & vertices,
                        const std::vector<glm::vec4> & colors,
                        const std::vector<glm::ivec2> & indices);

        const LineData & LineDataRef();
        
    private:
        LineData line_data;
};

#endif
