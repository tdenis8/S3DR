#ifndef _SHELL_OBJECT_H_
#define _SHELL_OBJECT_H_

#include "scene_object.hpp"

#include <glm/glm.hpp>

#include <string>
#include <vector>
#include <memory>

struct ShellEntry {
    unsigned int NumIndices = 0;
    unsigned int VertexOffset = 0;
    unsigned int IndicesOffset = 0;
};

struct ShellData {
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec4> colors;
    std::vector<glm::ivec3> indices;
    std::vector<ShellEntry> entries;
};

struct ShellMaterial {
    glm::vec4 color = glm::vec4(1,0,0,1);
    int status = 0;
};

enum class ShellOption: int {
    Transparency = 0,
};

class ShellObject : public SceneObject {
    public:
        ShellObject()=delete;
        explicit ShellObject(SceneObject * parent, std::string name, int priority);
        ShellObject(const ShellObject &)=delete;
        ShellObject & operator=(const ShellObject &)=delete;
        virtual ~ShellObject();

        void AppendData(const std::vector<glm::vec3> & vertices,
                        const std::vector<glm::vec4> & colors,
                        const std::vector<glm::ivec3> & indices);

        void AppendData(const std::vector<glm::vec3> & vertices,
                        const std::vector<glm::vec3> & normals,
                        const std::vector<glm::vec4> & colors,
                        const std::vector<glm::ivec3> & indices);

        void Highlight(bool highlight);

        const ShellData & ShellDataRef();
        const ShellMaterial & ShellMaterialRef();

    private:
        ShellData shell_data;
        ShellMaterial shell_material;
};

#endif
