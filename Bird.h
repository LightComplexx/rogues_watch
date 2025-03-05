#pragma once
#include "Enemy.h"

// Bandits are an enemy that just walk forward near the bottom of the screen
class Bird : public Enemy {
	private:
		void moveToStart();
		void step();
		void hit(const df::EventCollision* p_collision_event);
		int direction_countdown;
		int direction_slowdown;

	public:
		Bird();
		~Bird();
		virtual int eventHandler(const df::Event* p_e) override;
};
