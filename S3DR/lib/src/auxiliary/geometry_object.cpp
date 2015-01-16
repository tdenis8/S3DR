#include "geometry_object.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

GeometryObject::GeometryObject()
    : Subject()
    , position_(glm::vec3(0.0))
    , scale_factor_(glm::vec3(1.0))
    , orientation_(glm::fquat(0.0f, 0.0f, 0.0f, 0.0f))
    , model_matrix_(glm::mat4(1.0))
{
}

GeometryObject::~GeometryObject()
{
}

void GeometryObject::CalculateModelMatrix()
{
    glm::mat4 tmp_model_matrix(1.0);
    tmp_model_matrix = glm::scale(tmp_model_matrix, scale_factor_);
    tmp_model_matrix *= glm::mat4_cast(orientation_);
    model_matrix_ = glm::translate(tmp_model_matrix, position_);

    Emit(GeometryObjectEvents::MODEL_MATRIX_CHANGE);
}

void GeometryObject::SetPosition(const glm::vec3& position)
{
    position_ = position;
}

// TODO: calculate position scale and orjentation from model_matrix
void GeometryObject::SetModelMatrix(const glm::mat4& model_matrix)
{
}

const glm::vec3& GeometryObject::GetPosition() const
{
    return position_;
}

const glm::mat4& GeometryObject::GetModelMatrix() const
{
    return model_matrix_;
}

void GeometryObject::Translate(const glm::vec3& vector)
{
    position_ += vector;
    CalculateModelMatrix();
}

void GeometryObject::Scale(const glm::vec3& scale_coef)
{
    scale_factor_[0] *= scale_coef[0];
    scale_factor_[1] *= scale_coef[1];
    scale_factor_[2] *= scale_coef[2];
    CalculateModelMatrix();
}

void GeometryObject::Rotate(const glm::vec3& axis, float angle_in_deg)
{
    glm::vec3 norm_axis = glm::normalize(axis);
    glm::fquat offset = glm::angleAxis(angle_in_deg, norm_axis);
    orientation_ = offset * orientation_;
    orientation_ = glm::normalize(orientation_);
    CalculateModelMatrix();
}