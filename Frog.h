//
// Frog.h
//

#include "EventKeyboard.h"
#include "Object.h"
#include "EventCollision.h"

class Frog : public df::Object {

private:
	int move_slowdown;
	int move_countdown;
	void kbd(const df::EventKeyboard* p_keyboard_event);
	void move(int dy);
	void step();


public:
	Frog();
	~Frog();
	int eventHandler(const df::Event* p_e) override;
	void handleCollision(const df::EventCollision* p_collision_event);
};