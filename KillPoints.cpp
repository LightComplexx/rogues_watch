#include "KillPoints.h"
#include "DisplayManager.h"
#include "WorldManager.h"
#include "EventStep.h"
#include "EventOut.h"
KillPoints::KillPoints(int new_points, df::Vector pos) {

	// Set start position of object
	setPosition(pos);

	// Set altitude to max
	setAltitude(df::MAX_ALTITUDE);

	// KillPoints are spectral
	setSolidness(df::SPECTRAL);

	// Set points string to given points
	points = std::to_string(new_points);

	// Points are colored yellow
	color = df::YELLOW;

	// Move upward slightly after being created
	setVelocity(df::Vector(0, -0.10f));

	// Time the object lives for
	lifetime = 0;
	life_length = 5;

	// register interest in step event
	registerInterest(df::STEP_EVENT);
}

int KillPoints::draw(void) {
	for (int i = 0; i < points.size(); i++) {
		df::Vector temp_pos(getPosition().getX() + i, getPosition().getY());
		DM.drawCh(temp_pos, points[i], color);
	}
	return 1;
}

int KillPoints::eventHandler(const df::Event* p_e) {
	// Step events
	if (p_e->getType() == df::STEP_EVENT) {
		lifetime = lifetime+1;
		if (lifetime > life_length) {
			WM.markForDelete(this);
		}
		return 1;
	}
	if (p_e->getType() == df::OUT_EVENT) {
		WM.markForDelete(this);
		return 1;
	}
	return 0;
}


