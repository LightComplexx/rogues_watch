#pragma once
#include "Object.h"

class KillPoints : public df::Object {
	private:
		// The amount of points the enemy gives on death
		std::string points;

		// Color of the kill points
		df::Color color;

		// Time the points exist for
		int lifetime;
		int life_length;

	public:
		KillPoints(int new_points, df::Vector pos);
		int draw(void) override;
		int eventHandler(const df::Event* p_e) override;


};