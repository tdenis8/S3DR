#include "geometry_object.hpp"

#include <glm/gtc/matrix_transform.hpp>

GeometryObject::GeometryObject():
	Subject(),
	transformation_matrix(glm::mat4(1.0))
{

}

GeometryObject::~GeometryObject(){

}

void GeometryObject::SetPosition(const glm::vec3 & position){
	this->position = position;
}

void GeometryObject::SetTransformMatrix(const glm::mat4 &  transformation_matrix){
	this->transformation_matrix = transformation_matrix;
}

const glm::vec3 & GeometryObject::GetPosition() const{
	return position;
}

const glm::mat4 & GeometryObject::GetTransformMatrix() const{
	return transformation_matrix;
}

void GeometryObject::Translate(const glm::vec3 & vector){

}

void GeometryObject::Scale(const glm::vec3 & scale_coef){

}

void GeometryObject::Rotate(const glm::vec3 & axis, float angle_in_deg){

}