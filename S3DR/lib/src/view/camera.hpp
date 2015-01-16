#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "utility/subject.hpp"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum class ProjectionType
{
   Perspective,
   Orthogonal
};

enum class CameraEvents : unsigned int
{
   VIEW_CHANGED,
   PROJECTION_CHANGED
};

class Camera : public Subject<CameraEvents>
{
   public:
   Camera();
   virtual ~Camera();
   Camera(const Camera &) = delete;
   Camera &operator=(const Camera &) = delete;

   // Setters
   void SetCameraData(const glm::vec3 &cam_position, const glm::vec3 &cam_target, const glm::vec3 &cam_up);

   void SetCameraPositon(const glm::vec3 &cam_position);
   void SetCameraTarget(const glm::vec3 &cam_target);
   void SetCameraUP(const glm::vec3 &cam_up);

   void SetProjectionData(float field_of_view, int window_width, int window_height, float near_plane, float far_plane);

   void SetProjectionType(ProjectionType projection_type);
   void SetFieldOfView(float field_of_view);
   void SetAspectRatio(int window_width, int window_height);
   void SetNearPlane(float near_plane);
   void SetFarPlane(float far_plane);

   // Modifiers
   void RotateCamera(float angle_deg, const glm::vec3 &axis);
   void MoveCamera(float delta_x, float delta_y);

   void ChangeFieldOfView(float delta);

   // Getters
   const glm::mat4 &GetViewMatrix() const;
   const glm::mat4 &GetProjectionMatrix() const;

   int GetWidth() const;
   int GetHeight() const;

   const glm::vec3 &GetCameraPositionInWorld() const;

   private:
   void CalculateWorldOrientation(float angle_deg, const glm::vec3 &axis);
   void CalculateView();
   void CalculateProjection();

   ProjectionType projection_type;

   glm::mat4 view_matrix;
   glm::fquat world_orientation;
   glm::mat4 projection_matrix;

   glm::vec3 cam_position;
   glm::vec3 cam_target;
   glm::vec3 cam_up;

   float field_of_view;
   int window_width;
   int window_height;
   float near_plane;
   float far_plane;

   glm::vec3 cam_position_in_world;
};

#endif