#pragma once
//Star.h

//include:
#include "Object.h"

#define DUST_CHAR '.'

class Dust : public df::Object { //animating the background to simulate space

private:
	void out();

public:
	Dust();
	int eventHandler(const df::Event* p_e) override;
};