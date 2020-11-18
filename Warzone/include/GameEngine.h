#pragma once

#include "Player.h"
#include "Map.h"
#include "MapLoader.h"
#include <vector>
#include <iostream>
#include <vector>
#include "../include/Player.h"
#include "../include/Orders.h"

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
    Deck* deck; // default deck for the game
    // vector<Observer> observers*; // need Part 5 to complete
    GameEngine(); // default constructor
    ~GameEngine(); // destructor
    GameEngine(const GameEngine &gameEngine); // copy constructor
    GameEngine& operator=(const GameEngine &gameEngine); // overloading assignment
    friend ostream& operator<<(ostream& out, const GameEngine &gameEngine); // string insertion
    GameEngine(int numberOfPlayers, vector<Player*> players, MapLoader* maploader, Map* map);
    Map* chooseMap(); // let user choose map from path
    void setMap(Map* map); // set the map after loading it
    void setPlayerNum(); // set the number of player (2 to 5 only)
    int getPlayerNum(); // retrieve number of player
    void createPlayers(); // create all players and required elements for the players
    void toggleObserver(); // turn on/off any observers
    // void addPlayer(Player* p);
    // void gameLoop(Map gameMap);

    void mainGameLoop(); // main gameloop which will contain reinforcementPhase(), issueOrdersPhase(), executeOrdersPhase()
    void reinforcementPhase(); // reinforce game with current game state
    void issueOrdersPhase(); // issue order from player
    void executeOrdersPhase(); // execute order whe issuing is over
};

class Startup{
    public:
        Startup(vector<Player*> *players, Map *map);
        Startup(const Startup& startup);
        ~Startup();

        void setPlayerNum(int num);
        int getPlayerNum();
        int getInitialArmyNum();

    private:
        int playerNum = 2;
        void startupPhase(vector<Player*> *players, Map *map);      
};

