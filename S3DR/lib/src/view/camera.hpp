#ifndef _CAMERA_H_
#define _CAMERA_H_

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
    Camera() = delete;
    Camera(const glm::vec3 &cam_pos, const glm::vec3 &cam_target, const glm::vec3 &cam_up);
    virtual ~Camera();
    Camera(const Camera &) = delete;
    Camera &operator=(const Camera &) = delete;

    const glm::mat4 &CameraMatrixRef() const;

    void SetCameraPositon(const glm::vec3 &cam_pos);
    void SetCameraTarget(const glm::vec3 &cam_target);
    void SetCameraUP(const glm::vec3 &cam_up);

    void RotateCamera(const glm::vec3 &axis, float angle_in_deg);
    void MoveCamera(float delta_x, float delta_y);

private:
    void offset_orientation(const glm::vec3 &axis_, float angle_in_deg);
    void calculate_view();

    glm::vec3 cam_pos;
    glm::vec3 cam_target;
    glm::vec3 cam_up;

    glm::mat4 view_matrix;
    glm::fquat orientation;
};

#endif