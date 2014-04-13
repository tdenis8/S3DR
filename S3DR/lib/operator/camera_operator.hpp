#ifndef _CAMERA_OPERATOR_H_
#define _CAMERA_OPERATOR_H_

#include "operator.hpp"

#include <glm/glm.hpp>

class CameraOperator: public Operator {
	public:
		CameraOperator(View & view);
		virtual ~CameraOperator();

		int OnLeftButtonDownAndMove(const MouseEventInfo & info);
		int OnRightButtonDownAndMove(const MouseEventInfo & info);
		int OnMouseWheel(const MouseEventInfo & info);

		//Utility functions
		glm::vec3 MousePosition(const MouseEventInfo & info) const;
};

#endif