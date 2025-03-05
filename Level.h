// Engine includes
#include "ViewObject.h"
#include "TextBox.h"

class Level : public df::ViewObject {

private:
    void step(); // step event
    void begin(); // begins level
    void nextLevel(); // marks all objects for deletion, updates level count, and progress to next level
    void displayText();
    int current_level;
    int enemy_count;
    df::TextBox* level_display;

public:
    Level();
    int eventHandler(const df::Event* p_e) override;
};
