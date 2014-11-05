#ifndef _SCENE_OBJECT_H_
#define _SCENE_OBJECT_H_

#include "utility/subject.hpp"
#include "auxiliary/geometry_object.hpp"
#include "model.hpp"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <string>

enum class SceneObjectEvents : unsigned int
{
    COMBINED_MODEL_MATRIX_CHANGE,
    DATA_UPDATE
};

class SceneObject : public Subject<SceneObjectEvents>, Observer, public GeometryObject
{
    friend class Model;

public:
    SceneObject() = delete;
    SceneObject(SceneObject *parent, std::string name, int priority);
    SceneObject(const SceneObject &) = delete;
    SceneObject &operator=(const SceneObject &) = delete;
    ~SceneObject();

    std::string GetName() const;
    int GetKey() const;
    int GetPriority() const;
    const glm::mat4 &GetCombineModelMatrix() const;

    void SetObjectOption(unsigned int option);
    void ResetObjectOption(unsigned int option);
    bool TestObjectOption(unsigned int option);
    unsigned int GetObjectOptions();

private:
    void ParentModelMatrixChange(const EventInfo &info);
    void CalculateModelMatrix();
    void SetKey(int key);

    SceneObject *parent;
    int key;
    std::string name;
    int priority;
    glm::mat4 combine_model_matrix;
    unsigned int object_options;
};

#endif
