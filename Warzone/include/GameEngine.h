#pragma once

#include "Player.h"
#include "Map.h"
#include "MapLoader.h"
#include <vector>
#include <iostream>

class GameEngine;

class GameEngine {
//private attributes for GameEngine class
private:

// public attributes for GameEngine class
public:
    int numberOfPlayers;
	// int* numberOfRounds;
    vector<Player*> players; // list of players for the game
    MapLoader* maploader; // to load the map
    Map* map; // choose map
    // vector<Observer> observers*; // need Part 5 to complete
    GameEngine(); // default constructor
    ~GameEngine(); // destructor
    GameEngine(const GameEngine &gameEngine); // copy constructor
    GameEngine& operator=(const GameEngine &gameEngine); // overloading assignment
    friend ostream& operator<<(ostream& out, const GameEngine &gameEngine); // string insertion
    GameEngine(int numberOfPlayers, vector<Player*> players, MapLoader* maploader, Map* map);
    void chooseMap(); // let user choose map from path
    void setPlayerNum(); // set the number of player (2 to 5 only)
    void toggleObserver(); // turn on/off any observers
    // void addPlayer(Player* p);
    // void gameLoop(Map gameMap);
};
