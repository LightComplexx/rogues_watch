#include "Projectile.h"
#include "EventOut.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

Projectile::Projectile(df::Vector player_pos, float charge) {

	// Projectile set to soft
	setSolidness(df::SOFT);

	setType("Arrow");

	setSprite("arrow");

	// Set starting location, based on players' position passed in.
	df::Vector p(player_pos.getX() + 3, player_pos.getY());
	setPosition(p);

	// The direction is set when the player fires.
	setSpeed(1.0);

	// Projectiles should be affected by gravity
	df::Vector a(0, 0.05);
	setAcceleration(a);
}

int Projectile::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = dynamic_cast <const df::EventCollision*> (p_e);
		hit(p_collision_event);
		return 1;
	}
	return 0;
}

void Projectile::out() {
	WM.markForDelete(this);
}

void Projectile::hit(const df::EventCollision* p_collision_event) {

}
