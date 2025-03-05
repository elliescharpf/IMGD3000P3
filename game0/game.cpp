//
// game.cpp
// 

// Engine includes.
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "EventKeyboard.h"

#include "vs-2022/Block.h"
#include "vs-2022/Frog.h"
#include "vs-2022/GameStart.h"
#include "vs-2022/GameOver.h"
#include "vs-2022/Dust.h"

// Function prototypes.
void loadResources(void);
void populateWorld(void);

int main(int argc, char* argv[]) {

    // Start up game manager.
    if (GM.startUp()) {
        LM.writeLog("Error starting game manager!");
        GM.shutDown();
        return 1;
    }

    // Set flush of logfile during development (when done, make false).
    LM.setFlush(true);

    // Show splash screen.
    df::splash();

    // Load game resources.
    loadResources();

    // Populate game world with some objects.
    populateWorld();

    // Run game (this blocks until game loop is over).
    GM.run();

    // Shut everything down.
    GM.shutDown();

    return 0;
}

// Load resources (sprites, sound effects, music).
void loadResources(void) {
    RM.loadSprite("sprites/gamestart-spr.txt", "gamestart");
    RM.loadSprite("sprites/block-spr.txt", "block");
    RM.loadSprite("sprites/frog-spr.txt", "frog");
    RM.loadSprite("sprites/gameover-spr.txt", "gameover");

    RM.loadMusic("sounds/StartMusic.wav", "StartMusic");
    //RM.loadMusic("sounds/maingametheme", "maingametheme");
}

// Populate world with some objects.q
void populateWorld(void) {

    //spawn dust background
    for (int i = 0; i < 16; i++) {
        new Dust();
    }
    new GameStart();
}