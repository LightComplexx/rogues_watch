// Engine includes
#include "GameManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "EventStep.h"
#include "EventView.h"
#include "Sound.h"

// Game includes
#include "EnemyCountDisplay.h"
#include "LevelCompleteDisplay.h"
#include "EventGameOver.h"

EnemyCountDisplay::EnemyCountDisplay(int count) {
	// set type
	setType("EnemyCountDisplay");

	// Sets points to display at top right of window
	setPosition(df::Vector(WM.getBoundary().getHorizontal() - 25, 1));

	// Sets POINTS_STRING to be displayed
	setViewString(ENEMIES_STRING);

	// Sets value to input enemy count
	setValue(count);

	// Sets the text to the color yellow
	setColor(df::YELLOW);

	// Need to update score each second, so count "step" events
	registerInterest(df::STEP_EVENT);

	// set level completed to false
	level_completed = false;
	player_died = false;
}

int EnemyCountDisplay::eventHandler(const df::Event* p_e) {
	// Parent handles event if score update
	if (df::ViewObject::eventHandler(p_e)) {
		return 1;
	}

	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}

	if (p_e->getType() == GAME_OVER_EVENT) {
		player_died = true;
		return 1;
	}

	return 0;
}

void EnemyCountDisplay::step() {
	if (getValue() <= 0 && !level_completed && !player_died) {
		df::Sound* p_sound = RM.getSound("levelup");
		if (p_sound)
			p_sound->play();

		level_completed = true;
		LevelCompleteDisplay* completetext = new LevelCompleteDisplay();
		completetext->draw();
	}
}