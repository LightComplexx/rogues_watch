// Engine includes
#include "Event.h"
#include "ViewObject.h"

#define POINTS_STRING "Points"

class PointsDisplay : public df::ViewObject {
public:
    PointsDisplay();
    int eventHandler(const df::Event* p_e) override;
};
