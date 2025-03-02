//
// Block.cpp
//

// Engine includes.
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "EventCollision.h"

// Game includes.
#include "Block.h"


Block::Block() {

	// Setup "block" sprite.
	setSprite("block");

	// Set object type.
	setType("Block");

	// Set solidness
	setSolidness(df::HARD);

	// Set speed in horizontal direction.
	setVelocity(df::Vector(0, 0.25)); // 1 space down every 4 steps


	// Set starting location in middle of window.                             
	int world_horiz = (int)WM.getBoundary().getHorizontal();
	df::Vector p(rand() % world_horiz, 0); // Random x, y = 0
	setPosition(p);
}

	int Block::eventHandler(const df::Event * p_e) {
		if (p_e->getType() == df::COLLISION_EVENT) {
			const df::EventCollision* p_collision_event =
				dynamic_cast<const df::EventCollision*>(p_e);
			hit(p_collision_event);
			return 1;  // Return 1 if collision is handled.
		}
		return 0;  // No action if not a collision event.

		if (p_e->getType() == df::COLLISION_EVENT) {
			const df::EventCollision* p_collision_event = dynamic_cast <df::EventCollision const*> (p_e);
			hit(p_collision_event);
			return 1;
		}

	}
	
	// Called with Block collides.
	void Block::hit(const df::EventCollision* p_collision_event) {

		// If Block on Block, ignore.
		if ((p_collision_event->getObject1()->getType() == "Block") &&
			(p_collision_event->getObject2()->getType() == "Block"))
			return;


		// If Frog, mark both objects for destruction.
		if (((p_collision_event->getObject1()->getType()) == "Frog") ||
			((p_collision_event->getObject2()->getType()) == "Frog")) {
			WM.markForDelete(p_collision_event->getObject1());
			WM.markForDelete(p_collision_event->getObject2());
		}

	}

