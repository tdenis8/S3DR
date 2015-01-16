#include "camera.hpp"

#include "utility/math_utils.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

Camera::Camera()
   : Subject(),
     projection_type(ProjectionType::Orthogonal),
     projection_matrix(glm::mat4(1.0)),
     view_matrix(glm::mat4(1.0)),
     world_orientation(glm::fquat(0.0f, 0.0f, 0.0f, 0.0f))
{
   SetCameraData(glm::vec3(0.0f, 0.0f, 15.0f), glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, 1.0, 0.0));
   SetProjectionData(15.0f, 800, 600, -0.1f, 100.0f);
}

Camera::~Camera()
{
}

void Camera::CalculateWorldOrientation(float angle_deg, const glm::vec3 &axis)
{
   const glm::fquat &offset_quat = glm::angleAxis(DegToRad(angle_deg), axis);

   const glm::mat4 &view_mat = glm::lookAt(cam_position, cam_target, cam_up);
   glm::fquat view_quat = glm::quat_cast(view_mat);
   glm::fquat inv_view_quat = glm::conjugate(view_quat);

   const glm::fquat &world_offset_quat = (inv_view_quat * offset_quat * view_quat);

   world_orientation = world_offset_quat * world_orientation;
   world_orientation = glm::normalize(world_orientation);
}

void Camera::CalculateView()
{
   const glm::mat4 &world_orientation_mat = glm::mat4_cast(world_orientation);
   view_matrix = glm::lookAt(cam_position, cam_target, cam_up) * world_orientation_mat;
   cam_position_in_world = glm::vec3(glm::inverse(world_orientation_mat) * glm::vec4(cam_position, 1));
   Emit(CameraEvents::VIEW_CHANGED);
}

void Camera::CalculateProjection()
{
   if (projection_type == ProjectionType::Perspective)
   {
      projection_matrix = glm::perspective(field_of_view, float(window_width) / float(window_height), near_plane, far_plane);
   }
   else
   {
      projection_matrix = glm::ortho(-float(window_width) / 1000 * field_of_view, float(window_width) / 1000 * field_of_view,
                                     -float(window_height) / 1000 * field_of_view, float(window_height) / 1000 * field_of_view,
                                     near_plane, far_plane);
   }
   Emit(CameraEvents::PROJECTION_CHANGED);
}

// ------------------------------
// Setters
// ------------------------------
void Camera::SetCameraData(const glm::vec3 &cam_position, const glm::vec3 &cam_target, const glm::vec3 &cam_up)
{
   this->cam_position = cam_position;
   this->cam_target = cam_target;
   this->cam_up = cam_up;
   CalculateView();
}

void Camera::SetCameraPositon(const glm::vec3 &cam_position)
{
   this->cam_position = cam_position;
   CalculateView();
}

void Camera::SetCameraTarget(const glm::vec3 &cam_target)
{
   this->cam_target = cam_target;
   CalculateView();
}

void Camera::SetCameraUP(const glm::vec3 &cam_up)
{
   this->cam_up = cam_up;
   CalculateView();
}

void Camera::SetProjectionData(float field_of_view, int window_width, int window_height, float near_plane, float far_plane)
{
   this->field_of_view = field_of_view;
   this->window_width = window_width;
   this->window_height = window_height;
   this->near_plane = near_plane;
   this->far_plane = far_plane;
   CalculateProjection();
}

void Camera::SetProjectionType(ProjectionType projection_type)
{
   this->projection_type = projection_type;
   CalculateProjection();
}

void Camera::SetFieldOfView(float field_of_view)
{
   this->field_of_view = field_of_view;
   CalculateProjection();
}

void Camera::SetAspectRatio(int window_width, int window_height)
{
   this->window_width = window_width;
   this->window_height = window_height;
   CalculateProjection();
}

void Camera::SetNearPlane(float near_plane)
{
   this->near_plane = near_plane;
   CalculateProjection();
}
void Camera::SetFarPlane(float far_plane)
{
   this->far_plane = far_plane;
   CalculateProjection();
}

// ------------------------------
// Modifiers
// ------------------------------
void Camera::RotateCamera(float angle_deg, const glm::vec3 &axis)
{
   CalculateWorldOrientation(angle_deg, axis);
   CalculateView();
}

void Camera::MoveCamera(float delta_x, float delta_y)
{
   glm::vec3 right = glm::cross(cam_up, cam_target - cam_position);
   right = glm::normalize(right);
   cam_position += right * delta_x + cam_up * delta_y;
   cam_target += right * delta_x + cam_up * delta_y;
   CalculateView();
}

void Camera::ChangeFieldOfView(float delta)
{
   field_of_view += delta;
   if (field_of_view < 5)
   {
      field_of_view = 5;
   }
   if (field_of_view >= 175.0)
   {
      field_of_view = 175.0;
   }
   CalculateProjection();
}

// ------------------------------
// Getters
// ------------------------------
const glm::mat4 &Camera::GetViewMatrix() const
{
   return view_matrix;
}
const glm::mat4 &Camera::GetProjectionMatrix() const
{
   return projection_matrix;
}

int Camera::GetWidth() const
{
   return this->window_width;
}

int Camera::GetHeight() const
{
   return this->window_height;
}

const glm::vec3 &Camera::GetCameraPositionInWorld() const
{
   return cam_position_in_world;
}