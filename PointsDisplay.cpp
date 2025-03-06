// Engine includes
#include "GameManager.h"
#include "WorldManager.h"
#include "EventStep.h"
#include "EventView.h"

// Game includes
#include "PointsDisplay.h"

PointsDisplay::PointsDisplay() {
	// set type
	setType("PointsDisplay");

	// Sets points to display at top right of window
	setPosition(df::Vector(WM.getBoundary().getHorizontal() - 10, 1));

	// Sets POINTS_STRING to be displayed
	setViewString(POINTS_STRING);

	// Sets the text to the color yellow
	setColor(df::YELLOW);

	// Need to update score each second, so count "step" events
	registerInterest(df::STEP_EVENT);
}

int PointsDisplay::eventHandler(const df::Event* p_e) {
	// Parent handles event if score update
	if (df::ViewObject::eventHandler(p_e)) {
		return 1;
	}

	return 0;
}