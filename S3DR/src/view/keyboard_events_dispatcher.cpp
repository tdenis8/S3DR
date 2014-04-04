#include "keyboard_events_dispatcher.hpp"

#include "operator/operator.hpp"

KeyboardEventsDispatcher::KeyboardEventsDispatcher(){

}

KeyboardEventsDispatcher::~KeyboardEventsDispatcher(){

}

void KeyboardEventsDispatcher::AttachOperator(Operator * opr){
	this->opr = opr;
}

void KeyboardEventsDispatcher::DetachOperator(){
	opr = nullptr;
}

void KeyboardEventsDispatcher::OnKeyboardKey(int key, int state){
	if(opr){
		auto ke_info = KeyboardEventInfo(key);
		if(state){
			opr->OnKeyDown(ke_info);
		}
		else{
			opr->OnKeyUp(ke_info);
		}
	}
}