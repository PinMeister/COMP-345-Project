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
    
    // objects for players
    vector<Territory*> defaultTerritories; // players have no territories at first
    Hand* defaultHand = new Hand(); // to make default empty hand
    vector<Order*> defaultOrders; // default set of battle orders
    vector<Card*> defaultCards; // some cards
    Deck* defaultDeck = new Deck(); // default deck of cards

    gameEngine->deck = defaultDeck; // set the default deck to the new initialized one

    // create players
    vector<Player*> players;
    for(int i = 0; i < gameEngine->numberOfPlayers; i++){
        Player *player = new Player(defaultTerritories, defaultHand, defaultOrders, i);
        players.push_back(player);
        cout << "Player " << i + 1 << " id: " << player->getPlayerID() << "\n";
    }
    
    gameEngine->players = players;
    cout << "Players have been created" << endl;
    cout << "GameEngine player size " << gameEngine->players.size() << endl;

    // above code is the driver for game start - Part 1

    // free memory and dangling ptr
    delete gameEngine;
    gameEngine = NULL;

	return 0;
}