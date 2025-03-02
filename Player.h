// Engine includes
#include "Object.h"
#include "EventMouse.h"
#include "EventKeyboard.h"
#include "EventStep.h"

// Game includes
#include "Reticle.h"

class Player : public df::Object {
	private:
		// 
		void kbd(const df::EventKeyboard* p_kbd_event);
		void mse(const df::EventMouse* p_mouse_event);
		void step();
		void move(int dy);
		void fire(df::Vector target);
		int move_countdown;
		int move_slowdown;
		int fire_slowdown;
		int fire_countdown;
		Reticle* p_reticle;

	public:
		Player();
		int eventHandler(const df::Event* p_e) override;
};