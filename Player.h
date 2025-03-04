// Engine includes
#include "Object.h"
#include "EventMouse.h"
#include "EventKeyboard.h"
#include "EventStep.h"

// Game includes
#include "Reticle.h"

class Player : public df::Object {
	private:
		void kbd(const df::EventKeyboard* p_kbd_event); // keyboard events
		void mse(const df::EventMouse* p_mouse_event); // mouse events
		void step(); // step event
		void aim(df::Vector init_position, df::Vector curr_position);
		void fire(df::Vector target);
		int draw() override;
		int fire_slowdown;
		int fire_countdown;
		bool is_aiming;
		bool mouse_pressed;
		df::Vector start;
		df::Vector curr;
		float aim_time;
		Reticle* p_reticle;

	public:
		Player();
		~Player();
		int eventHandler(const df::Event* p_e) override;
};