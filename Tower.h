// Engine includes
#include "Object.h"
#include "EventStep.h"

// Game includes
#include "Reticle.h"

class Tower : public df::Object {
private:
	void step();
	int max_hp;
	int tower_hp;

public:
	Tower();
	int eventHandler(const df::Event* p_e) override;
};
