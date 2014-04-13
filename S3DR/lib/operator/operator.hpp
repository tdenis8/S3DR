#ifndef _OPERATOR_H_
#define _OPERATOR_H_

class View;

class MouseEventInfo {
	public:
		MouseEventInfo()=delete;
		MouseEventInfo(int x, int y, int x_delta, int y_delta, int wheel_delta):
			x(x), y(y), x_delta(x_delta), y_delta(y_delta), wheel_delta(wheel_delta)
		{

		}
		~MouseEventInfo() {}
		const int & X() const { return x; }
		const int & Y() const { return y; }
		const int & XDelta() const { return x_delta; }
		const int & YDelta() const { return y_delta; }
		const int & WheelDelta() const { return wheel_delta; }

	private:
		int x, y, x_delta, y_delta, wheel_delta;
};

class KeyboardEventInfo {
	public:
		KeyboardEventInfo()=delete;
		KeyboardEventInfo(int key): key(key) {}
		~KeyboardEventInfo() {}
		const int & Key() const { return key; }

	private:
		int key;
};

class Operator {
	public:
		Operator(View & view);
		virtual ~Operator();

		// Mouse actions
		virtual int OnLeftButtonDown(const MouseEventInfo & info);
		virtual int OnLeftButtonUp(const MouseEventInfo & info);
		virtual int OnLeftButtonDblClk(const MouseEventInfo & info);
		virtual int OnLeftButtonDownAndMove(const MouseEventInfo & info);

		virtual int OnMiddleButtonDown(const MouseEventInfo & info);
		virtual int OnMiddleButtonUp(const MouseEventInfo & info);
		virtual int OnMiddleButtonDblClk(const MouseEventInfo & info);
		virtual int OnMiddleButtonDownAndMove(const MouseEventInfo & info);

		virtual int OnRightButtonDown(const MouseEventInfo & info);
		virtual int OnRightButtonUp(const MouseEventInfo & info);
		virtual int OnRightButtonDblClk(const MouseEventInfo & info);
		virtual int OnRightButtonDownAndMove(const MouseEventInfo & info);

		virtual int OnLeftRightButtonDownAndMove(const MouseEventInfo & info);
		virtual int OnNoButtonDownAndMove(const MouseEventInfo & info);

		virtual int OnMouseWheel(const MouseEventInfo & info);

		// Keyboard actions
		virtual int OnKeyDown(const KeyboardEventInfo & info);
		virtual int OnKeyUp(const KeyboardEventInfo & info);		

	protected:
		View & view;
};

#endif