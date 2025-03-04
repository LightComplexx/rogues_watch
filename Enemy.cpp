#include "Enemy.h"
#include "WorldManager.h"
#include "KillPoints.h"
Enemy::Enemy() {
    // All Enemies should have type enemy
    setType("Enemy");

    // All enemies should register interest for Collisions and Out events
    registerInterest(df::COLLISION_EVENT);
    registerInterest(df::OUT_EVENT);

    // Points is initialized to 10
    points = 10;
}

Enemy::~Enemy() {
    new KillPoints(points, getPosition());
}

int Enemy::eventHandler(const df::Event* p_e) {
    if (p_e->getType() == df::COLLISION_EVENT) {
        const df::EventCollision* p_collision_event = dynamic_cast <df::EventCollision const*> (p_e);
        hit(p_collision_event);
        return 1;
    }
}

void Enemy::hit(const df::EventCollision* p_collision_event) {
    // All enemies should ignore other enemy types
    if ((p_collision_event->getObject1()->getType() == "Enemy") &&
        (p_collision_event->getObject2()->getType() == "Enemy")) {
        return;
    }

    // All enemies should die on being hit by the projectile, projectile has piercing properties
    if ((p_collision_event->getObject1()->getType() == "Arrow") ||
        (p_collision_event->getObject2()->getType() == "Arrow")) {
        WM.markForDelete(this);
    }
}

void Enemy::setPoints(int new_points) {
    points = new_points;
}

int Enemy::getPoints() {
    return points;
}
