#pragma once
//GameOver.h

//include:
#include "ViewObject.h"


class GameOver : public df::ViewObject {

private:
	int time_to_live; //handling game over animation length
	void step();

public:
	GameOver();
	~GameOver(); //game over destructor
	int eventHandler(const df::Event* p_e) override;
	int draw() override; //drawing the game over animation
};
