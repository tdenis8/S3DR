#ifndef _CUSTOM_OPERATORS_H_
#define _CUSTOM_OPERATORS_H_

#include <glm/glm.hpp>
#include <iostream>

// Custom operator that prints vector of a glm::vec3 type
std::ostream &operator <<(std::ostream &output, const glm::vec3 & vector);

// Custom operator that prints vector of a glm::vec4 type
std::ostream &operator <<(std::ostream &output, const glm::vec4 & vector);

// Custom operator that prints matrix of a glm::mat4 type
std::ostream &operator <<(std::ostream &output, const glm::mat4 & matrix);

#endif