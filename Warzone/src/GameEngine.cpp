#include <iostream>

#include "../include/GameEngine.h"


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

void Startup::startupPhase(){
    deterPlayerOrder();
    assignTerritories();
    assignArmies();
}

void Startup::deterPlayerOrder(){

}

void Startup::assignTerritories(){
    
}

void Startup::assignArmies(){
    int armyNum = getInitialArmyNum();
}