#pragma once

#include <iostream>


class GameEngine{
    public:
        GameEngine();
        GameEngine(const GameEngine& gameEngine);
        ~GameEngine();

    private:
        Startup *startup = new Startup();
};

class Startup{
    public:
        const int MIN_PLAYER_NUM = 2;
        const int MAX_PLAYER_NUM = 5;

        Startup();
        Startup(const Startup& startup);
        ~Startup();

        void setPlayerNum(int num);
        int getPlayerNum();
        int getInitialArmyNum();

    private:
        int playerNum = MIN_PLAYER_NUM;

        void startupPhase();
        void deterPlayerOrder();
        void assignTerritories();
        void assignArmies();        
};