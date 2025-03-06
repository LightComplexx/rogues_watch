// Engine includes
#include "Object.h"
#include "EventCollision.h"

// Game includes
#include "Reticle.h"
#include "HealthBar.h"

class Tower : public df::Object {
private:
	void damaged(const df::EventCollision* p_c);
	int max_hp;
	int tower_hp;
	HealthBar* p_bar;

public:
	Tower();
	~Tower();
	int eventHandler(const df::Event* p_e) override;
};
