//
// GameStart.cpp
//

// Engine includes
#include "GameManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "EventKeyboard.h"
#include "Color.h"

// Game includes
#include "GameStart.h"
#include "Player.h"
#include "Tower.h"
#include "Level.h"
#include "PointsDisplay.h"

GameStart::GameStart() {
	// Link to "gamestart" sprite
	setSprite("gamestart");

	// Sets object to type GameStart
	setType("GameStart");

	// Registers keyboard events
	registerInterest(df::KEYBOARD_EVENT);

	// Sets location to center of window
	df::Vector p(WM.getBoundary().getHorizontal() / 2, WM.getBoundary().getVertical() / 2);
	setPosition(p);
}

// Override default draw so as not to display "value"
int GameStart::draw() {
	return df::Object::draw();
}

int GameStart::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		df::EventKeyboard* p_keyboard_event = (df::EventKeyboard*)p_e;
		switch (p_keyboard_event->getKey()) {
		case df::Keyboard::P: 			// play
			start();
			break;
		case df::Keyboard::Q:			// quit
			GM.setGameOver();
			break;
		default: // Key is not handled.
			break;
		}
		return 1;
	}

	return 0;
}

// Count down to end of "message"
void GameStart::start() {
	// Spawn Tower
	new Tower;

	// Spawn player archer
	new Player;

	// Spawn Level
	new Level;

	// Spawn points
	new PointsDisplay;

	// When game starts, become inactive
	setActive(false);
}