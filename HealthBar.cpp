// Engine includes
#include "GameManager.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include "LogManager.h"
#include "EventStep.h"

// Game includes
#include "HealthBar.h"
#include "GameOver.h"

HealthBar::HealthBar(df::Vector position) {
	// Sets object to type Timebar
	setType("HealthBar");

	// Sets sprite and hp amounts
	if (setSprite("healthbar") == 0)
		max_hp = getAnimation().getSprite()->getFrameCount();
	else
		max_hp = 0;

	// Initialize variables
	current_hp = max_hp;
	damage_slowdown = 7;
	damage_countdown = damage_slowdown;

	// Makes the Timebar spectral so it can pass through objects 
	// and not impede movement
	setSolidness(df::SPECTRAL);

	// Draws the Timebar in the background
	setAltitude(df::MAX_ALTITUDE);

	// Set position
	setPosition(position);

	// register interest in step events
	registerInterest(df::STEP_EVENT);
}

HealthBar::~HealthBar() {
	// Destroys Hero and ends game
	// Create GameOver object
	new GameOver;

	// Shake screen (severity 20 pixels x&y, duration 10 frames).
	DM.shake(20, 20, 10);

	// Make a big explosion with particles.
	df::addParticles(df::SPARKS, getPosition(), 2, df::BLUE);
	df::addParticles(df::SPARKS, getPosition(), 2, df::YELLOW);
	df::addParticles(df::SPARKS, getPosition(), 3, df::RED);
	df::addParticles(df::SPARKS, getPosition(), 3, df::RED);
}

int HealthBar::eventHandler(const df::Event* p_e)
{
	// Step events
	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}

	return 0;
}

int HealthBar::draw()
{
	if (current_hp <= 0) {
		WM.markForDelete(this);
	}
	getAnimation().getSprite()->draw(max_hp - current_hp, getPosition(), 0);
	return 0;
}

void HealthBar::decreaseHealth() {
	if (damage_countdown > 0) {
		return;
	}
	damage_countdown = damage_slowdown;

	if (current_hp > 0) {
		current_hp--;
	}
}

void HealthBar::step() {
	damage_countdown--;
	if (damage_countdown < 0) {
		damage_countdown = 0;
	}

	getAnimation().setSlowdownCount(-1);
}