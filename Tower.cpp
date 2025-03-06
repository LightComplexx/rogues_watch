// Engine includes
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "DisplayManager.h"
#include "GameManager.h"
#include "GameOver.h"

// Game includes
#include "Tower.h"
#include "Reticle.h"
#include "EventGameOver.h"

Tower::Tower() {
	// Set sprite
	setSprite("tower");

	// Set type
	setType("Tower");

	// Set visibility
	//setSolidness(df::SOFT);

	// Register event interests
	registerInterest(GAME_OVER_EVENT);

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

Tower::~Tower() {
	// Destroys Hero and ends game
	// Create GameOver object
	new GameOver;

	// play die sound
	df::Sound* p_sound = RM.getSound("gameover");
	p_sound->play();

	// Shake screen (severity 20 pixels x&y, duration 10 frames).
	DM.shake(20, 20, 10);

	// Make a big explosion with particles.
	df::addParticles(df::SPARKS, getPosition(), 2, df::BLUE);
	df::addParticles(df::SPARKS, getPosition(), 2, df::YELLOW);
	df::addParticles(df::SPARKS, getPosition(), 3, df::RED);
	df::addParticles(df::SPARKS, getPosition(), 3, df::RED);

	WM.markForDelete(p_bar);
}

int Tower::eventHandler(const df::Event* p_e) {
	// Step events
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event =
			dynamic_cast <const df::EventCollision*> (p_e);
		damaged(p_collision_event);
		return 1;
	}

	// game over event
	if (p_e->getType() == GAME_OVER_EVENT) {
		WM.markForDelete(this);
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