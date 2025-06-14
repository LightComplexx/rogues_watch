//
// GameOver.cpp
//

// Engine includes
#include "GameManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "EventStep.h"

// Game includes
#include "GameStart.h"
#include "GameOver.h"

GameOver::GameOver() {
	// Sets object to type GameOver
	setType("GameOver");

	// Link to "message" sprite
	if (setSprite("gameover") == 0)
		time_to_live = getAnimation().getSprite()->getFrameCount() * getAnimation().getSprite()->getSlowdown();
	else
		time_to_live = 0;

	// Puts in center of window
	setLocation(df::CENTER_CENTER);

	// Registers for step event
	registerInterest(df::STEP_EVENT);
}

// When object exits, indicate game over.
GameOver::~GameOver() {
	// Remove Enemies, Player, Tower and ViewObjects, re-activate GameStart.
	df::ObjectList object_list = WM.getAllObjects(true);
	df::ObjectListIterator i(&object_list);
	for (i.first(); !i.isDone(); i.next()) {
		df::Object* p_o = i.currentObject();
		if (p_o->getType() == "Enemy" || p_o->getType() == "Player" || p_o->getType() == "ViewObject" || p_o->getType() == "EnemyCountDisplay" || p_o->getType() == "LevelDisplay" || p_o->getType() == "PointsDisplay")
			WM.markForDelete(p_o);
		if (p_o->getType() == "GameStart") {
			p_o->setActive(true);
		}
	}
}

// Override default draw so as not to display "value"
int GameOver::draw() {
	return df::Object::draw();
}

int GameOver::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}
	return 0;
}

// Count down to end of "message"
void GameOver::step() {
	time_to_live--;
	if (time_to_live <= 0)
		WM.markForDelete(this);
}