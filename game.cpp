//
// game.cpp
// 

// Engine includes.
#include "GameManager.h"
#include "ResourceManager.h"
#include "DisplayManager.h"
#include "LogManager.h"
#include "Player.h"

void loadResources();
void populateWorld();

int main(int argc, char* argv[]) {

    // Start up game manager.
    if (GM.startUp()) {
        LM.writeLog("Error starting game manager!");
        GM.shutDown();
        return 0;
    }

    LM.setFlush(true);

    // Show splash screen.
    df::splash();

    // Load game resources.
    loadResources();

    // Populate game world with some objects.
    populateWorld();

    // Run the game
    GM.run();

    // Shut everything down
    GM.shutDown();
}

void loadResources() {
    RM.loadSprite("sprites/player-spr.txt", "player");
}

void populateWorld() {
    new Player;
}