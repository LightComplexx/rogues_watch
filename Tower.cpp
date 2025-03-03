// Engine includes
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "GameManager.h"

// Game includes
#include "Tower.h"
#include "Reticle.h"

Tower::Tower() {
	// Set sprite
	setSprite("tower");

	// Set type
	setType("Tower");

	// Set visibility
	setSolidness(df::SOFT);

	// Register event interests
	registerInterest(df::STEP_EVENT);

	// Set starting location
	df::Vector p(0, 0);
	setPosition(p);

	// Initialize variables
	max_hp = 100;
	tower_hp = max_hp;
}

int Tower::eventHandler(const df::Event* p_e) {
	// Step events
	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}

	return 0;
}

void Tower::step() {

}