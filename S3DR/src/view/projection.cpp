#include "projection.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Projection::Projection(float field_of_view, int window_width, int window_height, float near_plane, float far_plane):
	field_of_view(field_of_view),
	window_width(window_width),
	window_height(window_height),
	near_plane(near_plane),
	far_plane(far_plane),
	projection_matrix(glm::mat4(1.0)),
	projection_type(ProjectionType::Orthogonal)
{
	CalculateProjection();
}

Projection::~Projection(){

}

void Projection::CalculateProjection(){
	if (projection_type == ProjectionType::Perspective){
		projection_matrix = glm::perspective(field_of_view , 
			                                 float(window_width)/float(window_height), 
			                                 near_plane, 
			                                 far_plane);
	}
	else{
		projection_matrix = glm::ortho( -float(window_width) / 1000 * field_of_view, 
		                            	 float(window_width) / 1000 * field_of_view, 
		                           	    -float(window_height) / 1000 * field_of_view,
		                           	     float(window_height) / 1000 * field_of_view, 
		                           		 near_plane, far_plane );
	}
}

const glm::mat4 & Projection::ProjectionMatrixRef() const{
	return projection_matrix;
}

void Projection::SetProjectionType(ProjectionType projection_type){
	this->projection_type = projection_type;
	CalculateProjection();
}

void Projection::SetAspectRatio(int window_width, int window_height){
	this->window_width = window_width;
	this->window_height = window_height;
	CalculateProjection();
}

void Projection::ChangeFieldOfView(float delta){
	field_of_view += delta;
	if(field_of_view < 5){
		field_of_view = 5;
	}
	if(field_of_view >= 175.0){
		field_of_view = 175.0;
	}
	CalculateProjection();
}

int Projection::Width() const {
	return this->window_width;
}

int Projection::Height() const {
	return this->window_height;
}