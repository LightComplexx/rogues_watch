// Engine includes
#include "WorldManager.h"
#include "EventView.h"
#include "EventStep.h"

// Game includes
#include "Bird.h"

Bird::Bird() {

	// Set speed in horizontal direction.
	setVelocity(df::Vector(-0.3, 0));

	// Setup sprite
	setSprite("bird");

	// Move to start location
	moveToStart();

	direction_countdown = 0;
	direction_slowdown = 5;
}

Bird::~Bird()
{
	df::EventView ev("Points", +getPoints(), true);
	WM.onEvent(&ev);

	df::EventView ev_enemies("Enemies", -1, true);
	WM.onEvent(&ev_enemies);
}

int Bird::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = dynamic_cast <df::EventCollision const*> (p_e);
		hit(p_collision_event);
		return 1;
	}
	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}

	return 0;
}

void Bird::step() {

	direction_countdown++;
	if (direction_countdown >= direction_slowdown) {
		if (getVelocity().getY() != 0.0) {
			setVelocity(df::Vector(-0.3, 0));
			direction_countdown = 0;
		}
		else {
			float up_or_down = 0;
			if (rand() % 2 == 0) {
				float up_or_down = 0.25;
			}
			else {
				float up_or_down = -0.25;
			}
			setVelocity(df::Vector(-0.3, up_or_down));
			direction_countdown = 0;
		}
	}
}

void Bird::hit(const df::EventCollision* p_collision_event)
{
	// All enemies should ignore other enemy types
	if ((p_collision_event->getObject1()->getType() == "Enemy") &&
		(p_collision_event->getObject2()->getType() == "Enemy")) {
		return;
	}

	// All enemies should die on being hit by the projectile, projectile has piercing properties
	if ((p_collision_event->getObject1()->getType() == "Arrow") ||
		(p_collision_event->getObject2()->getType() == "Arrow")) {
		df::Sound* p_sound = RM.getSound("die");
		if (p_sound)
			p_sound->play();

		WM.markForDelete(this);
	}
}

void Bird::moveToStart() {
	df::Vector temp_pos;

	// Get world boundaries.
	int world_horiz = (int)WM.getBoundary().getHorizontal();
	int world_vert = (int)WM.getBoundary().getVertical();

	// x is off right side of window.
	temp_pos.setX(world_horiz + rand() % (int)(world_horiz));

	// y is in vertical range.
	temp_pos.setY(rand() % (int)((world_vert / 3.0)) + world_vert * (2.0 / 8.0));

	// If collision, move right slightly until empty space.
	df::ObjectList collision_list = WM.getCollisions(this, temp_pos);
	while (!collision_list.isEmpty()) {
		temp_pos.setX(temp_pos.getX() + 1);
		collision_list = WM.getCollisions(this, temp_pos);
	}

	WM.moveObject(this, temp_pos);
}

