#include "operator.hpp"

#include <iostream>

Operator::Operator(View & view):
	view(view)
{

}

Operator::~Operator(){

}

int Operator::OnLeftButtonDown(const MouseEventInfo & info) { return 0; }
int Operator::OnLeftButtonUp(const MouseEventInfo & info) { return 0; }
int Operator::OnLeftButtonDblClk(const MouseEventInfo & info) { return 0; }
int Operator::OnLeftButtonDownAndMove(const MouseEventInfo & info) { return 0; }

int Operator::OnMiddleButtonDown(const MouseEventInfo & info) { return 0; }
int Operator::OnMiddleButtonUp(const MouseEventInfo & info) { return 0; }
int Operator::OnMiddleButtonDblClk(const MouseEventInfo & info) { return 0; }
int Operator::OnMiddleButtonDownAndMove(const MouseEventInfo & info) { return 0; }

int Operator::OnRightButtonDown(const MouseEventInfo & info) { return 0; }
int Operator::OnRightButtonUp(const MouseEventInfo & info) { return 0; }
int Operator::OnRightButtonDblClk(const MouseEventInfo & info) { return 0; }
int Operator::OnRightButtonDownAndMove(const MouseEventInfo & info) { return 0; }

int Operator::OnLeftRightButtonDownAndMove(const MouseEventInfo & info) { return 0; }
int Operator::OnNoButtonDownAndMove(const MouseEventInfo & info) { return 0; }

int Operator::OnMouseWheel(const MouseEventInfo & info) { return 0; }

int Operator::OnKeyDown(const KeyboardEventInfo & info) { return 0; }
int Operator::OnKeyUp(const KeyboardEventInfo & info) { return 0; }