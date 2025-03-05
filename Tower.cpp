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
	//setSolidness(df::SOFT);

	// Register event interests

	// Set starting location
	df::Vector p(WM.getBoundary().getVertical() * 0.1f, WM.getBoundary().getVertical() * 0.6f);
	setPosition(p);

	// Initialize variables
	max_hp = 100;
	tower_hp = max_hp;

	// Set healthbar location
	df::Vector bar_p(WM.getBoundary().getVertical() * 0.5f, 1.0f);

	p_bar = new HealthBar(bar_p);
	p_bar->draw();
}

int Tower::eventHandler(const df::Event* p_e) {
	// Step events
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event =
			dynamic_cast <const df::EventCollision*> (p_e);
		damaged(p_collision_event);
		return 1;
	}

	return 0;
}

void Tower::damaged(const df::EventCollision* p_c) {
	if (((p_c->getObject1()->getType()) == "Enemy") ||
		((p_c->getObject2()->getType()) == "Enemy")) {
		p_bar->decreaseHealth();
	}
}