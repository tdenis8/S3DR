#include "mouse_events_dispatcher.hpp"

#include "operator/operator.hpp"

MouseEventsDispatcher::MouseEventsDispatcher():
	opr(nullptr),
	x_position(0),
	y_position(0),
	left_btn_state(0),
	right_btn_state(0),
	middle_btn_state(0),
	left_dbl_clk(0),
	right_dbl_clk(0)
{

}

MouseEventsDispatcher::~MouseEventsDispatcher(){

}

void MouseEventsDispatcher::AttachOperator(Operator * opr){
	this->opr = opr;
}

void MouseEventsDispatcher::DetachOperator(){
	opr = nullptr;
}

void MouseEventsDispatcher::OnMouseButton(int button, int state){
	if(opr){
		auto me_info = MouseEventInfo(x_position, y_position, 0, 0, 0);
		// Left mouse button
		if(button==0 && state==1) {
			opr->OnLeftButtonDown(me_info);
			left_dbl_clk++;
		}
		if(button==0 && state==0) {
			opr->OnLeftButtonUp(me_info);
			left_dbl_clk++;
		}
		if(left_dbl_clk==4){
			opr->OnLeftButtonDblClk(me_info);
			left_dbl_clk = 0;
		}

		// Right mouse button
		if(button==1 && state==1) {
			opr->OnRightButtonDown(me_info);
			right_dbl_clk++;
		}
		if(button==1 && state==0) {
			opr->OnRightButtonUp(me_info);
			right_dbl_clk++;
		}
		if(right_dbl_clk==4){
			opr->OnRightButtonDblClk(me_info);
			right_dbl_clk = 0;
		}

		// Middle mouse button
		if(button==2 && state==1) {
			opr->OnMiddleButtonDown(me_info);
		}
		if(button==2 && state==0) {
			opr->OnMiddleButtonUp(me_info);
		}
	}

	switch(button) {
		case 0:
			left_btn_state = state;
			break;
		case 1:
			right_btn_state = state;
			break;
		case 2:
			middle_btn_state = state;
			break;
		default:
			break;
	}
}

void MouseEventsDispatcher::OnMouseMove(int x, int y){	
	if(opr){
		auto me_info = MouseEventInfo(x, y, x-x_position, y-y_position, 0);
		if(left_btn_state) {
			opr->OnLeftButtonDownAndMove(me_info);
		}
		if(middle_btn_state) {
			opr->OnMiddleButtonDownAndMove(me_info);
		}
		if(right_btn_state) {
			opr->OnRightButtonDownAndMove(me_info);
		}
		if(left_btn_state && right_btn_state) {
			opr->OnLeftRightButtonDownAndMove(me_info);
		}
		if(!left_btn_state && !right_btn_state && !middle_btn_state) {
			opr->OnNoButtonDownAndMove(me_info);
		}
	}

	x_position = x;
	y_position = y;
	left_dbl_clk = 0;
	right_dbl_clk = 0;
}

void MouseEventsDispatcher::OnMouseWheel(int delta){
	if(opr){
		auto me_info = MouseEventInfo(x_position, y_position, 0, 0, delta);
		opr->OnMouseWheel(me_info);
	}
}