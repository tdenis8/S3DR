#ifndef _COMBINED_OPERATOR_H_
#define _COMBINED_OPERATOR_H_

#include "operator/camera_operator.hpp"
#include "operator/select_operator.hpp"

#include <memory>

class CombinedOperator: public Operator {
	public:
		CombinedOperator(View & view);
		virtual ~CombinedOperator();

		int OnLeftButtonDown(const MouseEventInfo & info);
		int OnLeftButtonUp(const MouseEventInfo & info);
		
		int OnKeyDown(const KeyboardEventInfo & info);
		int OnKeyUp(const KeyboardEventInfo & info);

		int OnLeftButtonDownAndMove(const MouseEventInfo & info);
		int OnRightButtonDownAndMove(const MouseEventInfo & info);
		int OnMouseWheel(const MouseEventInfo & info);

	private:
		std::unique_ptr<CameraOperator> camera_operator;
		std::unique_ptr<SelectOperator> select_operator;
};

#endif