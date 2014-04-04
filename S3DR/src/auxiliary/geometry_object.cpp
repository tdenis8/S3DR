#include "geometry_object.hpp"

#include <glm/gtc/matrix_transform.hpp>

GeometryObject::GeometryObject():
	Subject(),
	transformation_matrix(glm::mat4(1.0))
{

}

GeometryObject::~GeometryObject(){

}