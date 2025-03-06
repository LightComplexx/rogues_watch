// Engine includes
#include "ViewObject.h"

class Level : public df::ViewObject {

private:
    void begin(); // begins level
    void nextLevel(); // marks all objects for deletion, updates level count, and progress to next level
    int current_level;
    int enemy_count;
    int points_count;

public:
    Level();
    int eventHandler(const df::Event* p_e) override;
};
