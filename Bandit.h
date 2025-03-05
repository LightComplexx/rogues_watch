#pragma once
#include "Enemy.h"

// Bandits are an enemy that just walk forward near the bottom of the screen
class Bandit : public Enemy {
	private:
		void moveToStart();
		void hit(const df::EventCollision* p_collision_event);

	public:
		Bandit();
		~Bandit();
		virtual int eventHandler(const df::Event* p_e) override;
};