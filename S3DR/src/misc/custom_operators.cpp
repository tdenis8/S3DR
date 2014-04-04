#include "custom_operators.hpp"

#include <iomanip>

#define WIDTH 13

std::ostream &operator <<(std::ostream &output, const glm::vec3 & vector)
{
	output<<std::setiosflags(std::ios::left);
	for(int i=0; i<3; i++){
		output<<std::setw(WIDTH)<<vector[i];
	}
	return output;
}

std::ostream &operator <<(std::ostream &output, const glm::vec4 & vector)
{
	output<<std::setiosflags(std::ios::left);
	for(int i=0; i<4; i++){
		output<<std::setw(WIDTH)<<vector[i];
	}
	return output;
}

std::ostream &operator <<(std::ostream &output, const glm::mat4 & matrix)
{
	output<<std::setiosflags(std::ios::left);

	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			output<<std::setw(WIDTH)<<matrix[i][j];
		}
		output<<std::endl;
	}

    return output;
}