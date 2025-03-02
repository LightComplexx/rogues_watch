#include "Player.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "GameManager.h"
#include "Reticle.h"

Player::Player() {
	// Set type
	setType("Player");

	// Set starting location
	df::Vector p(7, WM.getBoundary().getVertical() / 2);
	setPosition(p);

	// Set sprite
	setSprite("player");

	// Register event interests
	registerInterest(df::KEYBOARD_EVENT);
	registerInterest(df::MSE_EVENT);
	registerInterest(df::STEP_EVENT);

	new Reticle;
}

int Player::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const df::EventKeyboard* p_keyboard_event = dynamic_cast <const df::EventKeyboard*> (p_e);
		kbd(p_keyboard_event);
		return 1;
	}
	if (p_e->getType() == df::MSE_EVENT) {
		const df::EventMouse* p_mouse_event = dynamic_cast <const df::EventMouse*> (p_e);
		mse(p_mouse_event);
		return 1;
	}
	return 0;
}

void Player::kbd(const df::EventKeyboard* p_kbd_event) {
	switch (p_kbd_event->getKey()) {
		case df::Keyboard::Q:
			if (p_kbd_event->getKeyboardAction() == df::KEY_PRESSED) {
				GM.setGameOver();
			}
			break;
	}
}

void Player::mse(const df::EventMouse* p_mouse_event) {
	if ((p_mouse_event->getMouseAction() == df::PRESSED) && (p_mouse_event->getMouseButton() == df::Mouse::LEFT)) {

	}
}

void Player::step(const df::EventStep* p_step_event) {

}
