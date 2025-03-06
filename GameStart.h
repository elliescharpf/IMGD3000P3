//GameStart.h

#include "ViewObject.h"

class GameStart : public df::ViewObject {

private:
	void start();
	df::Music* p_music; //introduction music before game begins

public:
	GameStart();
	int eventHandler(const df::Event* p_e) override;
	int draw() override; //drawing the start screen
	void playMusic(); //playing intro music
};