//GameStart.cpp

//include:
#include "Color.h"
#include "EventKeyboard.h"
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

#include "GameStart.h"
#include "Frog.h"
#include "Block.h"
#include "Music.h"
#include "Points.h"


GameStart::GameStart() {
    setType("GameStart");

    // Link to string message sprite
    setSprite("gamestart");

    // Put in center of screen
    setLocation(df::CENTER_CENTER);

    // Register for keyboard click
    registerInterest(df::KEYBOARD_EVENT);

    // Log creation
    LM.writeLog("GameStart object created.");

    //Play start music
    p_music = RM.getMusic("StartMusic");
    m_music = RM.getMusic("maingametheme");
    playMusic();
    music_playing = true;

}

void GameStart::playMusic() {
    if (p_music) {
        p_music->play();
    }
}//playing intro music

void GameStart::pauseMusic() {
    df::Sound* main_music = df::ResourceManager::getInstance().getSound("maingametheme");
    if (main_music && music_playing) {
        main_music->pause();
        music_playing = false;
    }
}

// Handle gamestart events
int GameStart::eventHandler(const df::Event* p_e) {

    if (p_e->getType() == df::KEYBOARD_EVENT) {
        df::EventKeyboard* p_keyboard_event = (df::EventKeyboard*)p_e;
        switch (p_keyboard_event->getKey()) {
        case df::Keyboard::P: 			// play
            start();
            break;
        case df::Keyboard::Q:			// quit
            GM.setGameOver();
            break;
        default:
            break;
        }
        return 1;
    }

    // Ignored event if 0 is returned
    return 0;
}

void GameStart::start() {

    // Create hero.
    new Frog;

    // Spawn some saucers to shoot.
    for (int i = 0; i < 8; i++)
        new Block;

    // Setup heads-up display.
    new Points;		                     // Points display.

    // When game starts, become inactive
    setActive(false);

    //Pause start music
    p_music->pause();

    //Play start music
    playMusic();
}

// Override default draw
int GameStart::draw() {
    return df::Object::draw();
}