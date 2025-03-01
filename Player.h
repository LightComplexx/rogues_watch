#pragma once
#include "Object.h"
#include "EventMouse.h"
#include "EventKeyboard.h"
class Player : public df::Object {
	private:
		// 
		void kbd(const df::EventKeyboard* p_kbd_event);
		void mse(const df::EventMouse* p_mouse_event);
		void move(int dy);

	public:
		Player();
		int eventHandler(const df::Event* p_e) override;
};