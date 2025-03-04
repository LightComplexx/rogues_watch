// Engine includes
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "GameManager.h"
#include "DisplayManager.h"

// Game includes
#include "Player.h"
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
	df::Vector p(13, WM.getBoundary().getVertical() * 0.2f);
	setPosition(p);

	// Intialize variables
	// Sets the slowdown and countdown time for firing arrows
	fire_slowdown = 2;
	fire_countdown = fire_slowdown;

	is_aiming = false;

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
	}
}

void Player::mse(const df::EventMouse* p_mouse_event) {
	is_aiming = false;
	// Currently only for when mouse is immediately released
	if ((p_mouse_event->getMouseAction() == df::PRESSED) && (p_mouse_event->getMouseButton() == df::Mouse::LEFT)) {
		// Create offset vector
		//df::Vector offset(100, 100);

		// Pass start and current position to aim function
		aim(getPosition(), p_mouse_event->getMousePosition());

		// Set is_aiming state to true
		is_aiming = true;

		if (aim_time < 2) {
			aim_time = aim_time + 0.05;
		}
	}
}

void Player::step() {
	// Fire countdown
	fire_countdown--;
	if (fire_countdown < 0) {
		fire_countdown = 0;
	}

	if (!is_aiming && aim_time > 0.0) {
		fire(p_reticle->getPosition());
		aim_time = 0;
	}
}

void Player::fire(df::Vector target) {
	if (fire_countdown > 0) {
		return;
	}
	fire_countdown = fire_slowdown;

	df::Vector v = target - getPosition();
	v.normalize();
	v.scale(1.0 * (1.0 + aim_time));
	Projectile* p = new Projectile(getPosition(), aim_time);
	p->setVelocity(v);
}

void Player::aim(df::Vector init_position, df::Vector curr_position) {
	int Xscale = df::Config::getInstance().getWindowHorizontalPixels() / 10;
	int Yscale = df::Config::getInstance().getWindowVerticalPixels() / 10;

	sf::Vector2f start(init_position.getX(), init_position.getY() * Yscale);
	sf::Vector2f curr(curr_position.getX() * Xscale, curr_position.getY() * Yscale);

	sf::Vertex line[]{
		{{start}, sf::Color::Red},
		{{curr}, sf::Color::Red}
	};
		
	DM.getWindow()->draw(line, 2, sf::PrimitiveType::Lines);
}
