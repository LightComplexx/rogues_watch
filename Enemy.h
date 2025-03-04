#pragma once
#include "Object.h"
#include "EventOut.h"
#include "EventCollision.h"
#include "ResourceManager.h"

// The enemy class will be a parent class to other enemy types
class Enemy : public df::Object {
	private:
		// The amount of points the enemy gives on death
		int points;
		void hit(const df::EventCollision* p_collision_event);

	public:
		Enemy();
		~Enemy();
		virtual int eventHandler(const df::Event* p_e) override;

		// Setters/Getters for points
		void setPoints(int new_points);
		int getPoints();
		

};