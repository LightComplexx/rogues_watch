#include "Bandit.h"
#include "WorldManager.h"

Bandit::Bandit() {

	// Set speed in horizontal direction.
	setVelocity(df::Vector(-0.25, 0));

	// Setup sprite
	setSprite("bandit");

	// Move to start location
	moveToStart();

}

int Bandit::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = dynamic_cast <df::EventCollision const*> (p_e);
		hit(p_collision_event);
		return 1;
	}

	return 0;
}

void Bandit::hit(const df::EventCollision* p_collision_event)
{
	// All enemies should ignore other enemy types
	if ((p_collision_event->getObject1()->getType() == "Enemy") &&
		(p_collision_event->getObject2()->getType() == "Enemy")) {
		return;
	}

	// All enemies should die on being hit by the projectile, projectile has piercing properties
	if ((p_collision_event->getObject1()->getType() == "Arrow") ||
		(p_collision_event->getObject2()->getType() == "Arrow")) {
		new Bandit;
		WM.markForDelete(this);
	}
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

