#include "camera.hpp"

#include "utility/math_utils.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera::Camera(const glm::vec3 & cam_pos, const glm::vec3 & cam_target, const glm::vec3 & cam_up):
	cam_pos(cam_pos),
	cam_target(cam_target),
	cam_up(glm::normalize(cam_up)),
	view_matrix(glm::mat4(1.0)),
	orientation(glm::fquat(0.0f, 0.0f, 0.0f, 0.0f))
{
	calculate_view();
}

Camera::~Camera(){
	
}

// TODO: This method is to slow and should be replaced as soon as possible
void Camera::offset_orientation(const glm::vec3 &axis_, float angle_in_deg)
{
	float angleRad = DegToRad(angle_in_deg);
	glm::vec3 axis = glm::normalize(axis_);
	axis = axis * sinf(angleRad / 2.0f);
	float scalar = cosf(angleRad / 2.0f);

	glm::fquat offset(scalar, axis.x, axis.y, axis.z);

	// const glm::vec3 &_camPos = ResolveCamPosition();
	const glm::mat4 &camMat = glm::lookAt(cam_pos, cam_target, cam_up);

	glm::fquat viewQuat = glm::quat_cast(camMat);
	glm::fquat invViewQuat = glm::conjugate(viewQuat);
	const glm::fquat &worldQuat = (invViewQuat * offset * viewQuat);

	orientation = worldQuat * orientation;
	orientation = glm::normalize(orientation);
}

void Camera::calculate_view(){
	view_matrix = glm::lookAt(cam_pos, cam_target, cam_up);
	view_matrix = view_matrix * glm::mat4_cast(orientation);
}

const glm::mat4 & Camera::CameraMatrixRef() const{
	return view_matrix;
}

void Camera::SetCameraPositon(const glm::vec3 & cam_pos){
	this->cam_pos = cam_pos;
	calculate_view();
}

void Camera::SetCameraTarget(const glm::vec3 & cam_target){
	this->cam_target = cam_target;
	calculate_view();
}

void Camera::SetCameraUP(const glm::vec3 & cam_up){
	this->cam_up = cam_up;
	calculate_view();
}

void Camera::RotateCamera(const glm::vec3 &axis, float angle_in_deg){
	offset_orientation(axis, angle_in_deg);
	calculate_view();
}

void Camera::MoveCamera(float delta_x, float delta_y){
	glm::vec3 right = glm::cross(cam_up, cam_target - cam_pos);
	right = glm::normalize(right);
	cam_pos    += right*delta_x + cam_up*delta_y;
	cam_target += right*delta_x + cam_up*delta_y;
	calculate_view();
}