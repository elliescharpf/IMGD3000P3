//Points.cpp

//Includes:
#include "Event.h"
#include "EventStep.h"
#include "LogManager.h"
#include "Points.h"

Points::Points() {
	setLocation(df::TOP_RIGHT);
	setViewString(POINTS_STRING);
	setColor(df::CYAN);
	setSolidness(df::SOFT);
	//update score each second, count "step" events
	registerInterest(df::STEP_EVENT);
}

//Point event handler
int Points::eventHandler(const df::Event* p_e) {

	if (df::ViewObject::eventHandler(p_e)) {
		return 1;
	}

	if (p_e->getType() == df::STEP_EVENT) {
		if (dynamic_cast <const df::EventStep*> (p_e)->getStepCount() % 30 == 0)
			setValue(getValue() + 1);
		return 1;
	}

	//ignored event
	return 0;
}