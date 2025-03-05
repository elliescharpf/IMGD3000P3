//
// Frog.cpp
//

// Engine includes.
#include "EventStep.h"
#include "EventView.h"
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "GameOver.h"
#include "DisplayManager.h"

// Game includes.
#include "Frog.h"

Frog::Frog() {

    // Link to "frog" sprite.
    setSprite("frog");

    // Player controls frog, so register for input events.
    registerInterest(df::KEYBOARD_EVENT);

    // Need to update rate control each step.
    registerInterest(df::STEP_EVENT);

    // Set object type.
    setType("Frog");

    // Set solidness
    setSolidness(df::HARD);

    // Set starting location at the bottom center.
    int world_horiz = WM.getBoundary().getHorizontal();
    int world_vert = WM.getBoundary().getVertical();
    df::Vector p(world_horiz / 2, world_vert - 3);
    setPosition(p);

    // Set attributes that control actions.
    move_slowdown = 2;
    move_countdown = move_slowdown;
}

Frog::~Frog() {
    //create GameOver object
    new GameOver;

    //mark Reticle to delete
    WM.markForDelete(this);

    // Shake screen (severity 20 pixels x&y, duration 10 frames)
    DM.shake(20, 20, 10);
}

// Handle event.
// Return 0 if ignored, else 1.
int Frog::eventHandler(const df::Event* p_e) {
    if (p_e->getType() == df::KEYBOARD_EVENT) {
        const df::EventKeyboard* p_keyboard_event = dynamic_cast<const df::EventKeyboard*>(p_e);
        kbd(p_keyboard_event);
        return 1;
    }
    return 0;

}


// Take appropriate action according to key pressed.
void Frog::kbd(const df::EventKeyboard* p_keyboard_event) {
    switch (p_keyboard_event->getKey()) {
    case df::Keyboard::A:       // move left
        if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN) {
            move(-1);
        }
        break;
    case df::Keyboard::D:       // move right
        if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN) {
            move(1);
        }
        break;
    case df::Keyboard::Q:			// quit
        if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
            WM.markForDelete(this);
        break;
    }
}


// Move left or right.
void Frog::move(int dx) {
    df::Vector new_pos(getPosition().getX() + dx, getPosition().getY());
    if (new_pos.getX() >= 0 && new_pos.getX() < WM.getBoundary().getHorizontal()) {
        WM.moveObject(this, new_pos);
    }
}


// Decrease rate restriction counters.
void Frog::step() {
    if (move_countdown > 0) {
        move_countdown--;
    }
}


void Frog::handleCollision(const df::EventCollision* p_collision_event) {
    // Check if the collision involves a block.
    if ((p_collision_event->getObject1()->getType() == "Block") ||
        (p_collision_event->getObject2()->getType() == "Block")) {

        WM.markForDelete(this);  // Mark frog for deletion
    }
}