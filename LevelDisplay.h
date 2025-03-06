// Engine includes
#include "Event.h"
#include "ViewObject.h"

#define LEVEL_STRING "Level"

class LevelDisplay : public df::ViewObject {
public:
    LevelDisplay(int level);
    int eventHandler(const df::Event* p_e) override;
};
