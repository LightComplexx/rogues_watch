//
// game.cpp
// 

// Engine includes.
#include "GameManager.h"
#include "ResourceManager.h"
#include "LogManager.h"
#include "Player.h"

void loadResources();
void populateWorld();

int main(int argc, char* argv[]) {

    // Start up game manager.
    df::GameManager& game_manager = df::GameManager::getInstance();
    if (game_manager.startUp()) {
        df::LogManager& log_manager = df::LogManager::getInstance();
        log_manager.writeLog("Error starting game manager!");
        game_manager.shutDown();
        return 0;
    }

    // Testing

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