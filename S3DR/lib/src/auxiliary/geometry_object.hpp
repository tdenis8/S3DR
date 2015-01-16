#ifndef _GEOMETRY_OBJECT_H_
#define _GEOMETRY_OBJECT_H_

#include "utility/subject.hpp"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

enum class GeometryObjectEvents : unsigned int
{
    MODEL_MATRIX_CHANGE,
};

class GeometryObject : public Subject<GeometryObjectEvents>
{
    public:
    GeometryObject();
    GeometryObject(const GeometryObject &) = delete;
    GeometryObject &operator=(const GeometryObject &) = delete;
    virtual ~GeometryObject();

    void SetPosition(const glm::vec3 &position);
    void SetModelMatrix(const glm::mat4 &model_matrix);

    const glm::vec3 &GetPosition() const;
    const glm::mat4 &GetModelMatrix() const;

    void Translate(const glm::vec3 &vector);
    void Scale(const glm::vec3 &scale_coef);
    void Rotate(const glm::vec3 &axis, float angle_in_deg);

    protected:
    void CalculateModelMatrix();

    private:
    glm::vec3 position_;
    glm::vec3 scale_factor_;
    glm::fquat orientation_;
    glm::mat4 model_matrix_;
};

#endif
