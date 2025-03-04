// Engine includes
#include "GameManager.h"
#include "WorldManager.h"
#include "LogManager.h"

// Game includes
#include "HealthBar.h"

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

	// Makes the Timebar spectral so it can pass through objects 
	// and not impede movement
	setSolidness(df::SPECTRAL);

	// Draws the Timebar in the background
	setAltitude(df::MAX_ALTITUDE);

	// Set position
	setPosition(position);
}

HealthBar::~HealthBar() {
	GM.setGameOver();
}

int HealthBar::draw()
{
	if (current_hp <= 0) {
		WM.markForDelete(this);
	}
	getAnimation().getSprite()->draw(current_hp, getPosition(), 0);
	return 0;
}

void HealthBar::decreaseHealth() {
	if (current_hp > 0) {
		current_hp--;
	}
}
