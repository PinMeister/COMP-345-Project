#pragma once
#include "Observer.h"
#include "GameEngine.h"

class PhaseObserver : public Observer {
    public:
        PhaseObserver();
        PhaseObserver(GameEngine* game);
        ~PhaseObserver();
        void Update(Player* player, string phase, string info);
    private:
        GameEngine *subject;
        Player *player;
        string phase;
        string info;
};

class StatsObserver : public Observer {
    public:
        StatsObserver();
        StatsObserver(GameEngine* game);
        ~StatsObserver();
        void Update();
        void display();
    private:
        GameEngine *subject;
};
