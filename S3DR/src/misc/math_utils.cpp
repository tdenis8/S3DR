#include "math_utils.hpp"

#include <cmath>

glm::vec3 MeanPoint(const std::vector<glm::vec3> & points){
	glm::vec3 result(0.0, 0.0, 0.0);
	auto size=points.size();

	for(auto it=points.begin(); it<points.end(); ++it){
		result += *it;
	}
	if(size>0){
		result /= size;
	}

	return result;
}

float DegToRad(float angle_deg)
{
	const float deg_to_rad = 3.14159f * 2.0f / 360.0f;
	return angle_deg * deg_to_rad;
}

bool IsNull(float value){
	if(value < 0.000000001){
		return true;
	}
	return false;
}

glm::vec3 CircleCenterFromCirclePoints(const std::vector<glm::vec3> & points){
    if(points.size()!=3){
        return glm::vec3(0.0, 0.0, 0.0);
    }

    const glm::vec3 & p1 = points[0];
    const glm::vec3 & p2 = points[1];
    const glm::vec3 & p3 = points[2];

    auto tmp = glm::length(glm::cross(p1-p2, p2-p3));
    if(IsNull(tmp)){
        return glm::vec3(0.0, 0.0, 0.0);
    }

    auto k = 1/(2*tmp*tmp);
   
    tmp = glm::length(p2-p3);
    glm::vec3 a = (tmp*tmp) * glm::cross(p1-p2,p1-p3) * k;

    tmp = glm::length(p1-p3);
    glm::vec3 b = (tmp*tmp) * glm::cross(p2-p1,p2-p3) * k;

    tmp = glm::length(p1-p2);
    glm::vec3 c = (tmp*tmp) * glm::cross(p3-p1,p3-p2) * k;

    return a*p1 + b*p2 + c*p3;
}

float CircleRadiusFromCirclePoints(const std::vector<glm::vec3> & points){
    if(points.size()!=3){
        return 0.0;;
    }

    const glm::vec3 & p1 = points[0];
    const glm::vec3 & p2 = points[1];
    const glm::vec3 & p3 = points[2]; 

    float tmp1 = glm::length(p1-p2) * glm::length(p2-p3) * glm::length(p3-p1);

    float tmp2 = 2 * glm::length(glm::cross(p1-p2, p2-p3));
    if(IsNull(tmp2)){
        return 0.0;
    }

    return tmp1/tmp2;
}