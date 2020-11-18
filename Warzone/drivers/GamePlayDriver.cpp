#include "../include/GameEngine.h"
#include "../include/Map.h"
#include "../include/Player.h"
#include "../include/MapLoader.h"
#include <iostream>
#include <ctime>
#include <algorithm>
#include <random>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <cmath>

using namespace std;

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
    cout << "GameEngine player size " << gameEngine->players.size() << endl;

    // above code is the driver for game start - Part 1

    // below code is for gameplay and maingameloop - Part 3
    // vector<Player*> *tempPlayersPointer = ;
    cout << "Beginning of startup phase" << endl;
    Startup *startUp = new Startup(&(gameEngine->players), gameEngine->map);
    cout << "startup phase completed" << "\n\n";

    cout << "Beginning of reinforcement phase" << endl;
    gameEngine->reinforcementPhase();
    cout << "End of reinforcement phase" << endl;

    // free memory and dangling ptr
    delete gameEngine;
    gameEngine = NULL;

	return 0;
}