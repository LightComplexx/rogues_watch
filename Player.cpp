#include "Player.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "GameManager.h"
#include "Reticle.h"
#include "Projectile.h"

Player::Player() {
	// Set sprite
	setSprite("player");

	// Set type
	setType("Player");

	// Register event interests
	registerInterest(df::KEYBOARD_EVENT);
	registerInterest(df::MSE_EVENT);
	registerInterest(df::STEP_EVENT);

	// Set starting location
	df::Vector p(7, WM.getBoundary().getVertical() / 3);
	setPosition(p);


	// Im not sure the player should be able to move?	
	
	// Intialize variables
	// Sets the slowdown and countdown time for moving the Hero
	move_slowdown = 2;
	move_countdown = move_slowdown;

	// Create reticle for firing bullets
	p_reticle = new Reticle();
	p_reticle->draw();
}

int Player::eventHandler(const df::Event* p_e) {
	// Keyboard events
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const df::EventKeyboard* p_keyboard_event = dynamic_cast <const df::EventKeyboard*> (p_e);
		kbd(p_keyboard_event);
		return 1;
	}

	// Mouse events
	if (p_e->getType() == df::MSE_EVENT) {
		const df::EventMouse* p_mouse_event = dynamic_cast <const df::EventMouse*> (p_e);
		mse(p_mouse_event);
		return 1;
	}

	// Step events
	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}

	return 0;
}

void Player::kbd(const df::EventKeyboard* p_kbd_event) {
	switch (p_kbd_event->getKey()) {
		case df::Keyboard::Q:    // quit
			if (p_kbd_event->getKeyboardAction() == df::KEY_PRESSED) {
				GM.setGameOver();
			}
			break;

		case df::Keyboard::W:    // up
			if (p_kbd_event->getKeyboardAction() == df::KEY_DOWN)
				move(-1);
			break;

		case df::Keyboard::S:    // down
			if (p_kbd_event->getKeyboardAction() == df::KEY_DOWN)
				move(+1);
			break;
	}
}

void Player::mse(const df::EventMouse* p_mouse_event) {
	// Currently only for when mouse is immediately released
	if ((p_mouse_event->getMouseAction() == df::CLICKED) && (p_mouse_event->getMouseButton() == df::Mouse::LEFT)) {
		fire(p_mouse_event->getMousePosition());
	}
}

void Player::step() {
	// Move countdown
	move_countdown--;
	if (move_countdown < 0) {
		move_countdown = 0;
	}
	fire_countdown--;
	if (fire_countdown < 0) {
		fire_countdown = 0;
	}
}

void Player::move(int dy)
{
	// See if time to move
	if (move_countdown > 0)
		return;
	move_countdown = move_slowdown;

	// If stays on window, allow move
	df::Vector new_pos(getPosition().getX(), getPosition().getY() + dy);
	if ((new_pos.getY() > 3) &&
		(new_pos.getY() < WM.getBoundary().getVertical() - (getBox().getVertical() / 2)))
		WM.moveObject(this, new_pos);
}

void Player::fire(df::Vector target) {
	if (fire_countdown > 0) {
		return;
	}
	fire_countdown = fire_slowdown;

	df::Vector v = target - getPosition();
	v.normalize();
	v.scale(1);
	Projectile* p = new Projectile(getPosition());
	p->setVelocity(v);
}
