// Engine includes
#include "GameManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "EventStep.h"

// Game includes
#include "Level.h"
#include "Player.h"
#include "Tower.h"
#include "Bandit.h"
#include "Bird.h"
#include "EnemyCountDisplay.h"
#include "LevelDisplay.h"
#include "PointsDisplay.h"
#include "EventLevelComplete.h"

Level::Level() {
	// Sets object to type GameOver
	setType("Level");

	// Puts in center of window
	setLocation(df::CENTER_CENTER);

	// Registers for step and level complete events
	registerInterest(df::STEP_EVENT);
	registerInterest(LEVEL_COMPLETE_EVENT);

	// Initialize variables
	current_level = 0;
	enemy_count = 0;
	points_count = 0;

	// Start first level
	begin();
}

int Level::draw()
{
	return df::Object::draw();
}

int Level::eventHandler(const df::Event* p_e)
{
	// Level complete event
	if (p_e->getType() == LEVEL_COMPLETE_EVENT) {
		nextLevel();
		return 1;
	}

	return 0;
}

// When object exits, indicate game over.
void Level::nextLevel() {
	// Remove everything on screen
	df::ObjectList object_list = WM.getAllObjects(true);
	df::ObjectListIterator i(&object_list);
	for (i.first(); !i.isDone(); i.next()) {
		df::Object* p_o = i.currentObject();
		if (p_o->getType() == "EnemyCountDisplay" || p_o->getType() == "LevelDisplay")
			WM.markForDelete(p_o);
	}

	// Increment and progress to next level
	current_level++;
	enemy_count = 0;
	begin();
}

void Level::begin() {
	// Spawn enemies
	int enemy_cap = 1 + (current_level);

	for (int i = 0; i < enemy_cap; i++) {
		// spawn Bird every 3 enemies if past level 2
		if (current_level > 1 && (i % 3 == 0)) {
			new Bird;
		}
		else {
			new Bandit;
		}
		enemy_count++;
	}

	// Spawn all displays
	new EnemyCountDisplay(enemy_count);
	new LevelDisplay(current_level + 1);
}