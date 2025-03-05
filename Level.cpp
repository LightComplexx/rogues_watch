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
#include "EventLevelComplete.h"

Level::Level() {
	// Sets object to type GameOver
	setType("Level");

	// Puts in center of window
	setLocation(df::CENTER_CENTER);

	// Registers for step and level complete events
	registerInterest(df::STEP_EVENT);

	// Initialize variables
	level_display = NULL;
	current_level = 0;
	enemy_count = 0;

	// Start first level
	begin();
}

int Level::eventHandler(const df::Event* p_e)
{
	// Step events
	if (p_e->getType() == df::STEP_EVENT) {
		step();
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
		if (p_o->getType() == "Enemy" || p_o->getType() == "Player" || p_o->getType() == "Tower" || p_o->getType() == "ViewObject" || p_o->getType() == "TextBox")
			WM.markForDelete(p_o);
	}

	// reset level display
	WM.markForDelete(level_display);

	// Progress to next level
	begin();
}

void Level::step()
{
	if (enemy_count <= 0) {
		displayText();
	}
}

void Level::displayText() {
	int time_to_live = 80;

	// Display text until time ends
	while (time_to_live > 0) {
		if (!level_display) { // If not already displaying
			level_display = new df::TextBox;
			level_display->setLocation(df::CENTER_CENTER);
			level_display->setViewString("Combination List");
			level_display->setSize(df::Vector(50, 10));
			level_display->setText("Level " + std::to_string(current_level) + " completed");
			level_display->setColor(df::GREEN);
		}

		time_to_live--;
	}

	nextLevel();
}

void Level::begin() {
	// Spawn Tower
	new Tower;

	// Spawn player archer
	new Player;

	// Spawn a bandit
	int enemy_cap = 10 + (current_level);

	for (int i = 0; i < enemy_cap; i++) {
		new Bandit;
		enemy_count++;
	}

	// level_count display
	df::ViewObject* p_vol = new df::ViewObject;
	p_vol->setLocation(df::TOP_RIGHT);
	p_vol->setViewString("Level");
	p_vol->setValue(current_level++);
	p_vol->setColor(df::YELLOW);

	// enemy_count display
	df::ViewObject* p_voe = new df::ViewObject;
	p_voe->setLocation(df::TOP_CENTER);
	p_voe->setViewString("Level");
	p_voe->setValue(enemy_count);
	p_voe->setColor(df::YELLOW);
}