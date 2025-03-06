// Engine includes
#include "Event.h"
#include "ViewObject.h"

class LevelCompleteDisplay : public df::ViewObject {
private:
    int time_to_live;
public:
    LevelCompleteDisplay();
    ~LevelCompleteDisplay();
    int draw() override;
    int eventHandler(const df::Event* p_e) override;
};
