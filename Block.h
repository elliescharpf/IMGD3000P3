//
// Block.h
//

#include "Object.h"
#include "EventCollision.h"


class Block : public df::Object {
private:
	void hit(const df::EventCollision* p_collision_event);
	void out();

public:
	Block();
	int eventHandler(const df::Event* p_e) override;
	void moveToStart();
};