// Engine includes
#include "GameManager.h"
#include "WorldManager.h"
#include "EventStep.h"

// Game includes
#include "LevelCompleteDisplay.h"
#include "EventLevelComplete.h"

LevelCompleteDisplay::LevelCompleteDisplay() {
	// Sets object to type Slash
	setType("LevelCompleteDisplay");

	// Sets sprite for 'Dimensional Slash' text
	if (setSprite("completetext") == 0)
		time_to_live = getAnimation().getSprite()->getFrameCount() * getAnimation().getSprite()->getSlowdown() * 4;
	else
		time_to_live = 0;

	// Makes the Slash text spectral so it can pass through objects 
	// and not impede movement
	setSolidness(df::SPECTRAL);

	// Draws the Slash text in the foreground
	setAltitude(df::MAX_ALTITUDE);

	// Sets location to top center of window
	setLocation(df::CENTER_CENTER);

	// Registers step event
	registerInterest(df::STEP_EVENT);
}

LevelCompleteDisplay::~LevelCompleteDisplay() {
	// Create level complete event and send to interested objects
	EventLevelComplete complete;
	WM.onEvent(&complete);
}

int LevelCompleteDisplay::eventHandler(const df::Event* p_e) {
	// Life countdown
	if (p_e->getType() == df::STEP_EVENT) {
		time_to_live--;
		return 1;
	}

	return 0;
}

int LevelCompleteDisplay::draw() {
	// Flash text until time delay ends
	if (time_to_live <= 0) {
		WM.markForDelete(this);
		return -1;
	}
	return df::Object::draw();
}
