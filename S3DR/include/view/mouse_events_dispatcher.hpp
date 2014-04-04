#ifndef _MOUSE_EVENTS_DISPATCHER_H_
#define _MOUSE_EVENTS_DISPATCHER_H_

class Operator;

class MouseEventsDispatcher {
	public:
		MouseEventsDispatcher();
		virtual ~MouseEventsDispatcher();

		//lb = 0, rb = 1, mb = 2, up/down btn = 0/1
		void OnMouseButton(int button, int state);
		void OnMouseMove(int x, int y);
		void OnMouseWheel(int delta);

	protected:
		void AttachOperator(Operator * opr);
		void DetachOperator();

	private:
		Operator * opr;

		int x_position;
		int y_position;
		int left_btn_state;
		int right_btn_state;
		int middle_btn_state;
		int left_dbl_clk;
		int right_dbl_clk;
};

#endif