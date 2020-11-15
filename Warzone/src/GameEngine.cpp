#include <iostream>
#include <algorithm>
#include <random>
#include <stdlib.h>
#include <time.h>
#include <chrono>

#include "../include/GameEngine.h"

using namespace std;

GameEngine::GameEngine(){
    
}

void GameEngine::setPlayers(vector<Player*> *players){
    this->players = players;
}

void GameEngine::setMap(Map *map){
    this->map = map;
}

Startup::Startup(vector<Player*> *players, Map *map){
    setPlayerNum(players->size());
    startupPhase(players, map);
}

Startup::Startup(const Startup& startup){
    playerNum = startup.playerNum;
}

Startup::~Startup(){

}

void Startup::setPlayerNum(int num){
    playerNum = num;
}

int Startup::getPlayerNum(){
    return playerNum;
}

int Startup::getInitialArmyNum(){
    return ((playerNum * 5) + 10 * (5 - playerNum));
}

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
        srand(time(NULL));
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
}