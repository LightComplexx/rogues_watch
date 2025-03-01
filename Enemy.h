#pragma once
#include "Object.h"
#include "EventOut.h"
#include "ResourceManager.h"

// The enemy class will be a parent class to other enemy types
class Enemy : public df::Object {
	private:
		

	public:
		Enemy();
		int eventHandler(const df::Event* p_e) override;

};