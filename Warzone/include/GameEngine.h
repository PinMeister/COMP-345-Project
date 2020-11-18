#pragma once

#include <iostream>
#include <vector>
#include "../include/Player.h"
#include "../include/Orders.h"

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