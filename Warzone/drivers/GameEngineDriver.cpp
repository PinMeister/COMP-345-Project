#include <iostream>
#include <ctime>
#include <algorithm>
#include <random>
#include <stdlib.h>
#include <time.h>
#include <chrono>

#include "../include/MapLoader.h"
#include "../include/Map.h"
#include "../include/Player.h"
#include "../include/GameEngine.h"


// main driver
int main() {
    int numberOfPlayers = 0;
    vector<Player*> tempPlayers;
    MapLoader* maploader;
    Map* map;
    GameEngine* gameEngine = new GameEngine(numberOfPlayers, tempPlayers, maploader, map);

    cout << "Map BEFORE user chooses: " << gameEngine->map << endl;
    map = gameEngine->chooseMap(); // choose map to start the game
    gameEngine->setMap(map); // set the new map from the maploader
    cout << "Map AFTER user chooses: " << gameEngine->map << endl;

    cout << "Number of player before user chooses: " << gameEngine->numberOfPlayers << endl;
    gameEngine->setPlayerNum(); // let user choose number of players
    cout << "Number of player after user chooses: " << gameEngine->numberOfPlayers << endl;

    cout << "Creating the players and required items for the game: " << endl;
    gameEngine->createPlayers();
    cout << "Players have been created" << endl;

    // free memory and dangling ptr
    delete gameEngine;
    gameEngine = NULL;

	return 0;
}