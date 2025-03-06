#pragma once
//GameStart.h

#include "ViewObject.h"
//#include "Music.h"

class GameStart : public df::ViewObject {

private:
	void start();
	df::Music* p_music; //introduction music before game begins
	df::Music* m_music;
	bool music_playing = false;

public:
	GameStart();
	int eventHandler(const df::Event* p_e) override;
	int draw() override; //drawing the start screen
	void playMusic(); //playing intro music
	void pauseMusic();
};
