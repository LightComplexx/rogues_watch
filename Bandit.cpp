#include "Bandit.h"
#include "WorldManager.h"

Bandit::Bandit() {

	// Set speed in horizontal direction.
	setVelocity(df::Vector(-0.25, 0));

	// Setup sprite. currently using player sprite as template
	setSprite("player");

	// Move to start location
	moveToStart();

}

Bandit::~Bandit() {
	new Bandit;
}

void Bandit::moveToStart() {
	df::Vector temp_pos;

	// Get world boundaries.
	int world_horiz = (int)WM.getBoundary().getHorizontal();
	int world_vert = (int)WM.getBoundary().getVertical();

	// x is off right side of window.
	temp_pos.setX(world_horiz + rand() % (int)(world_horiz + 10.0f));

	// y is in vertical range.
	temp_pos.setY(rand() % (int)((world_vert - 4) + 4.0f));

	// If collision, move right slightly until empty space.
	df::ObjectList collision_list = WM.getCollisions(this, temp_pos);
	while (!collision_list.isEmpty()) {
		temp_pos.setX(temp_pos.getX() + 1);
		collision_list = WM.getCollisions(this, temp_pos);
	}

	WM.moveObject(this, temp_pos);
}