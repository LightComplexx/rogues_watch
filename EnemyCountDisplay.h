// Engine includes
#include "Event.h"
#include "ViewObject.h"

#define ENEMIES_STRING "Enemies"

class EnemyCountDisplay : public df::ViewObject {
private:
    void step(); // step event function
    bool level_completed;
public:
    EnemyCountDisplay(int count);
    int eventHandler(const df::Event* p_e) override;
};
