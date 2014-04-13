#include "geometry_object.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

GeometryObject::GeometryObject():
	position(glm::vec3(0.0)),
	scale_factor(glm::vec3(1.0)),
	orientation(glm::fquat(0.0f, 0.0f, 0.0f, 0.0f)),
	model_matrix(glm::mat4(1.0))
{

}

GeometryObject::~GeometryObject(){

}

void GeometryObject::CalculateModelMatrix(){
	glm::mat4 tmp_model_matrix(1.0);
	tmp_model_matrix = glm::scale(tmp_model_matrix, scale_factor);
	tmp_model_matrix *= glm::mat4_cast(orientation);
	model_matrix = glm::translate(tmp_model_matrix, position);
}

void GeometryObject::SetPosition(const glm::vec3 & position){
	this->position = position;
}

// TODO: calculate position scale and orjentation from model_matrix
void GeometryObject::SetModelMatrix(const glm::mat4 &  model_matrix){

}

const glm::vec3 & GeometryObject::GetPosition() const{
	return position;
}

const glm::mat4 & GeometryObject::GetModelMatrix() const{
	return model_matrix;
}

void GeometryObject::Translate(const glm::vec3 & vector){
	position += vector;
	CalculateModelMatrix();
}

void GeometryObject::Scale(const glm::vec3 & scale_coef){
	scale_factor[0] *= scale_coef[0];
	scale_factor[1] *= scale_coef[1];
	scale_factor[2] *= scale_coef[2];
	CalculateModelMatrix();
}

void GeometryObject::Rotate(const glm::vec3 & axis, float angle_in_deg){
	glm::vec3 norm_axis = glm::normalize(axis);
    glm::fquat offset = glm::angleAxis(angle_in_deg, norm_axis);
    orientation = offset * orientation;
    orientation = glm::normalize(orientation);
	CalculateModelMatrix();
}