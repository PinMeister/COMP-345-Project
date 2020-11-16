#pragma once

#include <iostream>
#include <vector>
#include "../include/Player.h"
#include "../include/Orders.h"

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