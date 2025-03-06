// Engine includes
#include "GameManager.h"
#include "WorldManager.h"
#include "EventStep.h"
#include "EventView.h"

// Game includes
#include "LevelDisplay.h"

LevelDisplay::LevelDisplay(int level) {
	// Sets points to display at top center of window
	setLocation(df::TOP_CENTER);

	// Sets POINTS_STRING to be displayed
	setViewString(LEVEL_STRING);

	// Sets the text to the color yellow
	setColor(df::YELLOW);

	// Sets display value to current level
	setValue(level);

	// Need to update score each second, so count "step" events
	registerInterest(df::STEP_EVENT);
}

int LevelDisplay::eventHandler(const df::Event* p_e) {
	// Parent handles event if score update
	if (df::ViewObject::eventHandler(p_e)) {
		return 1;
	}

	return 0;
}