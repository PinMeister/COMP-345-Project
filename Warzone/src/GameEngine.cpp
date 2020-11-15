#include <iostream>
#include <algorithm>
#include <random>
#include <stdlib.h>

#include "../include/GameEngine.h"

using namespace std;

Startup::Startup(){

}

Startup::Startup(const Startup& startup){

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
    auto rng = std::default_random_engine{};
    shuffle(players->begin(), players->end(), rng);

    int initialArmyNum = getInitialArmyNum(); // get initial army num

    // assign territories
    int size = map->getTerritories().size(); // get territory num
    vector<int> randomTerritoryId;
    // get random territory id and push to the vector
    for(int i = 0; i < playerNum; i++){
        int temp = rand() % size;
        // find a match
        vector<int>::iterator it = find (randomTerritoryId.begin(), randomTerritoryId.end(), temp);
        // if num exists, repeat
        while(it != randomTerritoryId.end()){
            temp = rand() % size;
            it = find (randomTerritoryId.begin(), randomTerritoryId.end(), temp);
        }
        randomTerritoryId.push_back(temp); // push it to the vector
        players->at(i)->addTerritory(map->getTerritories()[i]); // give player the territory
        map->getTerritories()[i]->addArmyNum(initialArmyNum); // assign army to territory
    }
}