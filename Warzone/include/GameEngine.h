#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <vector>
#include <iostream>

#include "../include/Orders.h"
#include "../include/Player.h"
#include "../include/Orders.h"
#include "../include/Map.h"
#include "../include/MapLoader.h"
#include "../include/Subject.h"
#include "../include/GameObservers.h"

class GameEngine;
class PhaseObserver;

class GameEngine : public Subject {
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
    Player* currentPlayer; // current player
    Order* lastOrder; // the last order
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
    void toggleObserver(); // turn on/off any observers
    // void addPlayer(Player* p);
    // void gameLoop(Map gameMap);
    void mainGameLoop(); // main gameloop which will contain reinforcementPhase(), issueOrdersPhase(), executeOrdersPhase()
    void reinforcementPhase(PhaseObserver* phaseObserver); // reinforce game with current game state
    void issueOrdersPhase(PhaseObserver* phaseObserver); // issue order from player
    void executeOrdersPhase(PhaseObserver* phaseObserver); // execute order when issuing is over
};

class Startup{
    public:
        Startup(); // default constructor
        Startup(vector<Player*> *players, Map *map); // constructor
        Startup(const Startup& startup); // copy constructor
        ~Startup(); // destructor
        // overloading assignment and string insertion
        Startup& operator=(const Startup &startUp);
        friend ostream& operator<<(ostream& out, const Startup &startUp);

        void setPlayerNum(int num);
        int getPlayerNum();
        int getInitialArmyNum();
    private:
        int playerNum = 2;
        bool started = false;
        void startupPhase(vector<Player*> *players, Map *map); // start up function 
};
 #endif 
