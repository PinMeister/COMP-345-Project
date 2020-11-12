#pragma once

#include <iostream>
#include <vector>
#include "../include/Player.h"
#include "../include/Orders.h"

class GameEngine{
    public:
        const int MIN_PLAYER_NUM = 2;
        const int MAX_PLAYER_NUM = 5;
        GameEngine();
        GameEngine(const GameEngine& gameEngine);
        ~GameEngine();
    private:
        int playerNum = MIN_PLAYER_NUM;
        vector<Player*> players;
        Map *map;
        friend class Startup;
};

class Startup{
    public:
        Startup();
        Startup(const Startup& startup);
        ~Startup();

        void setPlayerNum(int num);
        int getPlayerNum();
        int getInitialArmyNum();

    private:
        vector<Player*> *players;
        int playerNum = 2;
        void startupPhase(vector<Player*> *players, Map *map);      
};