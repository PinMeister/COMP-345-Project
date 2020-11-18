#include <iostream>
#include <algorithm>
#include <random>
#include <stdlib.h>
#include <time.h>
#include <chrono>

#include "../include/GameEngine.h"

using namespace std;

// constructor with no parameter
Startup::Startup(){
    // nothing
}

// constructor takes in a vector pointer of player pointers and a pointer to map
Startup::Startup(vector<Player*> *players, Map *map){
    setPlayerNum(players->size());
    startupPhase(players, map);
}

// copy constructor
Startup::Startup(const Startup& startup){
    Startup* copy = new Startup();
    copy->playerNum = startup.playerNum;
    copy->setPlayerNum(copy->playerNum);
}

// destructor
Startup::~Startup(){
    //nothing
}

// assignment operator
Startup& Startup::operator=(const Startup &startUp){
    playerNum = startUp.playerNum;
    return *this;
}

// stream insertion operator
ostream& operator<<(ostream& out, const Startup &startUp){
    out << "Player Number: " << startUp.playerNum << "\nGame started: " << startUp.started << "\n";
    return out;
}

// set player num to an int
void Startup::setPlayerNum(int num){
    playerNum = num;
}

// return player num
int Startup::getPlayerNum(){
    return playerNum;
}

// use player num to get initial army num
int Startup::getInitialArmyNum(){
    return ((playerNum * 5) + 10 * (5 - playerNum));
}

// start up the game
void Startup::startupPhase(vector<Player*> *players, Map *map){
    // shuffle player order in vector
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(players->begin(), players->end(), default_random_engine(seed));
    int initialArmyNum = getInitialArmyNum(); // get initial army num

    // assign territories
    int size = map->getTerritories().size(); // get territory num
    vector<int> randomTerritoryId;
    // get random territory id and push to the vector
    for(int i = 0; i < playerNum; i++){
        srand(time(NULL)); // set seed a runtime value
        int temp = rand() % size;
        // find a match
        vector<int>::iterator it = find (randomTerritoryId.begin(), randomTerritoryId.end(), temp);
        // if num exists, repeat
        while(it != randomTerritoryId.end()){
            temp = rand() % size;
            it = find (randomTerritoryId.begin(), randomTerritoryId.end(), temp);
        }
        randomTerritoryId.push_back(temp); // push it to the vector
        players->at(i)->addTerritory(map->getTerritories()[temp]); // give player the territory
        map->getTerritories()[temp]->addArmyNum(initialArmyNum); // assign army to territory
    }
    started = true;
}