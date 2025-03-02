#pragma once
#include "EventCollision.h"
#include "Object.h"

class Projectile : public df::Object {

	private:
		void out();
		void hit(const df::EventCollision* p_collision_event);

	public:
		Projectile(df::Vector player_pos);
		int eventHandler(const df::Event* p_e) override;
};
