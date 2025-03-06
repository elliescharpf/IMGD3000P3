#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "EventCollision.h"
#include "EventOut.h"
#include "Block.h"

Block::Block() {
	// Setup "block" sprite.
	setSprite("block");

	// Set object type.
	setType("Block");

	// Set solidness.
	setSolidness(df::HARD);

	// Set speed in vertical direction (falling down).
	setVelocity(df::Vector(0, 0.25)); // Moves downward

	// Set starting location at a random x at the top.
	int world_horiz = (int)WM.getBoundary().getHorizontal();
	df::Vector p(rand() % world_horiz, -5); // Slightly above screen to prevent immediate collision
	setPosition(p);
}

int Block::eventHandler(const df::Event* p_e) {
	// Handle collision events
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event =
			dynamic_cast<const df::EventCollision*>(p_e);
		hit(p_collision_event);
		return 1;
	}

	// Handle out-of-bounds events
	if (p_e->getType() == df::OUT_EVENT) {
		out(); // Reset block position
		return 1;
	}

	return 0;
}

//If moved past bottom edge, move back up to far top
void Block::out() {

	// If block is still on screen, do nothing
	if (getPosition().getY() < WM.getBoundary().getVertical()) {
		return;
	}

	//Otherwise, move back to far top
	moveToStart();

	//spawn new block
	new Block;
}


// Handle collisions.
void Block::hit(const df::EventCollision* p_collision_event) {
	// If Block collides with another Block, ignore it.
	if (p_collision_event->getObject1()->getType() == "Block" &&
		p_collision_event->getObject2()->getType() == "Block")
		return;

	// If it collides with a "Frog", delete both.
	if (p_collision_event->getObject1()->getType() == "Frog" ||
		p_collision_event->getObject2()->getType() == "Frog") {
		WM.markForDelete(p_collision_event->getObject1());
		WM.markForDelete(p_collision_event->getObject2());
	}
}

// Move Block to a new position at the top when it goes out of bounds.
void Block::moveToStart() {
	df::Vector temp_pos;

	// Get world boundaries.
	int world_horiz = (int)WM.getBoundary().getHorizontal();

	// X is random within screen width.
	temp_pos.setX(rand() % world_horiz);

	// Y is slightly above the top boundary.
	temp_pos.setY(-5);

	// Ensure no immediate collision.
	df::ObjectList collision_list = WM.getCollisions(this, temp_pos);
	while (!collision_list.isEmpty()) {
		temp_pos.setX(rand() % world_horiz); // Pick another random Y position
		collision_list = WM.getCollisions(this, temp_pos);
	}

	WM.moveObject(this, temp_pos);
}