//GameOver.cpp

//Includes:
#include "EventStep.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "GameOver.h"
#include "GameStart.h"
#include "GameManager.h"

GameOver::GameOver() {

	setType("GameOver");

	if (setSprite("gameover") == 0)
		time_to_live = getAnimation().getSprite()->getFrameCount() * getAnimation().getSprite()->getSlowdown();
	else
		time_to_live = 0;

	//center in window
	setLocation(df::CENTER_CENTER);

	//step event
	registerInterest(df::STEP_EVENT);

	//// Play "game over" sound.
	//df::Sound* p_sound = RM.getSound("game over");
	//if (p_sound)
	//	p_sound->play();

}

//Game over, reset for game start again
GameOver::~GameOver() {

	df::ObjectList object_list = WM.getAllObjects(true);
	for (int i = 0; i < object_list.getCount(); i++) {
		df::Object* p_o = object_list[i];
		if (p_o->getType() == "Block" || p_o->getType() == "ViewObject")
			WM.markForDelete(p_o);
		if (p_o->getType() == "GameStart") {
			p_o->setActive(true);
			//dynamic_cast <GameStart*> (p_o)->playMusic(); // Resume start music.
		}
	}
}

//Game Over event handler
int GameOver::eventHandler(const df::Event* p_e) {

	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}

	//ignored event
	return 0;
}

//count down
void GameOver::step() {
	time_to_live--;
	if (time_to_live <= 0)
		WM.markForDelete(this);
}

//override default
int GameOver::draw() {
	return df::Object::draw();
}