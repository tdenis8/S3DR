#ifndef _KEYBOARD_EVENTS_DISPATCHER_H_
#define _KEYBOARD_EVENTS_DISPATCHER_H_

class Operator;

class KeyboardEventsDispatcher {
	public:
		KeyboardEventsDispatcher();
		virtual ~KeyboardEventsDispatcher();

		void OnKeyboardKey(int key, int state);

	protected:
		void AttachOperator(Operator * opr);
		void DetachOperator();

	private:
		Operator * opr;
};

#endif