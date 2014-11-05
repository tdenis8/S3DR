#ifndef _MATH_UTILS_H_
#define _MATH_UTILS_H_

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <vector>

/// \brief Calculate mean point
///
/// Calculate mean point of all input points.
///
/// \param	vector input of points
/// \return mean point value
glm::vec3 MeanPoint(const std::vector<glm::vec3>& points);

/// \brief Convert an angle
///
/// Convert the angle from degrees to radians.
///
/// \param	angle in degrees
/// \return angle in radians
float DegToRad(float angle_deg);

/// \brief Test float value
///
/// Test if float value == 0.0
///
/// \param	float value
/// \return test result
bool IsNull(float value);

/// \brief Circle center
///
/// Calculate the circle center using tree points that form the circle.
///
/// \param	vector that holds tree circle points, NOTE: size of vector
///			must be three
/// \return circle center
glm::vec3 CircleCenterFromCirclePoints(const std::vector<glm::vec3>& points);

/// \brief Circle radius
///
/// Calculate the circle radius using tree points that form the circle.
///
/// \param	vector that holds tree circle points, NOTE: size of vector
///			must be three
/// \return circle radius
float CircleRadiusFromCirclePoints(const std::vector<glm::vec3>& points);

#endif