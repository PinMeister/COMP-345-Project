#include "../include/GameEngine.h"
#include "../include/Map.h"
#include "../include/Player.h"
#include "../include/MapLoader.h"
#include "../include/GameObservers.h"
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
int main(){
    int numberOfPlayers = 0;
    vector<Player*> tempPlayers;
    MapLoader* maploader;
    Map* map;
    GameEngine* gameEngine = new GameEngine(numberOfPlayers, tempPlayers, maploader, map);

    PhaseObserver* phaseObserver = new PhaseObserver(gameEngine);
    StatsObserver* statsObserver = new StatsObserver(gameEngine);

    char phaseToggle; // Set phase 
    do {
        cout << "Turn off phase observer? (Y/N)";
		cin >> phaseToggle;
	} while (phaseToggle != 'Y' || phaseToggle != 'N');
    if (phaseToggle == 'Y') {
        delete phaseObserver;
        phaseObserver = NULL;
    }

    char statsToggle;
    do {
        cout << "Turn off game stats observer? (Y/N)";
		cin >> statsToggle;
	} while (statsToggle != 'Y' || statsToggle != 'N');
    if (statsToggle == 'Y') {
        delete statsObserver;
        statsObserver = NULL;
    }

    cout << "Map BEFORE user chooses: " << gameEngine->map << endl;
    map = gameEngine->chooseMap(); // choose map to start the game
    gameEngine->setMap(map); // set the new map from the maploader
    cout << "Map AFTER user chooses: " << gameEngine->map << endl;

    cout << "Number of player before user chooses: " << gameEngine->numberOfPlayers << endl;
    gameEngine->setPlayerNum(); // let user choose number of players
    cout << "Number of player after user chooses: " << gameEngine->numberOfPlayers << endl;

    // above code is the driver for game start - Part 1

    // below code is for gameplay and maingameloop - Part 3
    int playerNum = gameEngine->numberOfPlayers;

    cout << "Creating the players and required items for the game: " << endl;

    // objects for players
    vector<Territory*> defaultTerritories; // players have no territories at first
    Hand* defaultHand = new Hand(); // to make default empty hand
    vector<Order*> defaultOrders; // default set of battle orders
    vector<Card*> defaultCards; // some cards
    Deck* defaultDeck = new Deck(); // default deck of cards

    gameEngine->deck = defaultDeck; // set the default deck to the new initialized one

    // create players
    vector<Player*> players;
    for(int i = 0; i < playerNum; i++){
        Player *player = new Player(defaultTerritories, defaultHand, defaultOrders, i);
        players.push_back(player);
        cout << "Player " << i + 1 << " id: " << player->getPlayerID() << "\n";
    }
    
    gameEngine->players = players;

    cout << "Players have been created" << endl;
    cout << "GameEngine player size " << gameEngine->players.size() << endl;

    // create GameEngine
    cout << "\nCreating game" << "\n";
    Startup *startUp = new Startup(&players, map);
    cout << "startup phase completed" << "\n\n";

    for(int i = 0; i < playerNum; i++){
        cout << "Player " << i + 1 << " has " << players[i]->getReinforcementPool() <<  " armies" << endl;
    }

    cout << endl << "Beginning of reinforcement phase " << endl;
    if (phaseObserver != NULL) {
        phaseObserver->setPhase("Reinforcement Phase");
        gameEngine->reinforcementPhase(phaseObserver);
    }
    cout << "End of reinforcement phase " << endl;

    // free memory and dangling ptr
    delete startUp;
    delete gameEngine;
    delete defaultHand;
    delete defaultDeck;

    startUp = NULL;
    gameEngine = NULL;
    defaultHand = NULL;
    defaultDeck = NULL;

    return 0;
}