#include "combined_operator.hpp"

CombinedOperator::CombinedOperator(View & view):
	Operator(view),
	camera_operator(nullptr),
	select_operator(nullptr)
{
	camera_operator.reset(new CameraOperator(view));
	select_operator.reset(new SelectOperator(view));
}

CombinedOperator::~CombinedOperator(){

}

int CombinedOperator::OnLeftButtonDown(const MouseEventInfo & info){
	return select_operator->OnLeftButtonDown(info);
}

int CombinedOperator::OnLeftButtonUp(const MouseEventInfo & info){
	return select_operator->OnLeftButtonUp(info);
}

int CombinedOperator::OnKeyDown(const KeyboardEventInfo & info){
	return select_operator->OnKeyDown(info);
}

int CombinedOperator::OnKeyUp(const KeyboardEventInfo & info){
	return select_operator->OnKeyUp(info);
}

int CombinedOperator::OnLeftButtonDownAndMove(const MouseEventInfo & info){
	return camera_operator->OnLeftButtonDownAndMove(info);
}

int CombinedOperator::OnRightButtonDownAndMove(const MouseEventInfo & info){
	return camera_operator->OnRightButtonDownAndMove(info);
}

int CombinedOperator::OnMouseWheel(const MouseEventInfo & info){
	return camera_operator->OnMouseWheel(info);
}
