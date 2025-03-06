//
// game.cpp
// 

// Engine includes.
#include "GameManager.h"
#include "ResourceManager.h"
#include "LogManager.h"
#include "DisplayManager.h"

// Game includes
#include "GameStart.h"

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
    return 0;
}

void loadResources() {
    RM.loadSprite("sprites/player-spr.txt", "player");
    RM.loadSprite("sprites/tower-spr.txt", "tower");
    RM.loadSprite("sprites/gamestart-spr.txt", "gamestart");
    RM.loadSprite("sprites/gameover-spr.txt", "gameover");
    RM.loadSprite("sprites/arrow-spr.txt", "arrow");
    RM.loadSprite("sprites/healthbar-spr.txt", "healthbar");
    RM.loadSprite("sprites/bandit-spr.txt", "bandit");
    RM.loadSprite("sprites/bird-spr.txt", "bird");
    RM.loadSprite("sprites/completetext-spr.txt", "completetext");
    RM.loadSound("sounds/Bow.wav", "fire");
    RM.loadSound("sounds/EnemyKill.wav", "die");
    RM.loadSound("sounds/NextLevel.wav", "levelup");
    RM.loadSound("sounds/TowerExplode.wav", "gameover");
}

void populateWorld() {
    new GameStart();
}