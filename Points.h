//Points.h

//Include:
#include "ViewObject.h"
#include "Event.h"

#define POINTS_STRING "Points"

class Points : public df::ViewObject { //point system

public:
	Points();
	int eventHandler(const df::Event* p_e) override;
};