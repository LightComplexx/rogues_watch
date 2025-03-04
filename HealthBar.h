// Engine includes
#include "Object.h"

class HealthBar : public df::Object {
private:
	int max_hp; // maximum health amount (set to health bar frame count)
	int current_hp; // current health amount
	int damage_slowdown;
	int damage_countdown;
	void step(); // step event

public:
	HealthBar(df::Vector position);
	~HealthBar();
	int draw() override;
	void decreaseHealth();
	int eventHandler(const df::Event* p_e) override;
};