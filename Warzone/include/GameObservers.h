#pragma once
#include "Observer.h"
#include "GameEngine.h"
using namespace std;

class PhaseObserver : public Observer {
    public:
        PhaseObserver();
        PhaseObserver(GameEngine* game);
        ~PhaseObserver();
        PhaseObserver(const PhaseObserver &phaseObserver);
        PhaseObserver& operator = (const PhaseObserver &phaseObserver);
        friend ostream& operator << (ostream &os, PhaseObserver &phaseObserver);
        void Update();
        void Update(Player* player, string phase, string info);
        GameEngine* getSubject();
        Player* getPlayer();
        string getPhase();
        string getInfo();
        void setPhase(string phase);
        void setInfo(string info);
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
        StatsObserver(const StatsObserver &statsObserver);
        StatsObserver& operator = (const StatsObserver &statsObserver);
        friend ostream& operator << (ostream &os, StatsObserver &statsObserver);
        void Update();
        GameEngine* getSubject();
    private:
        GameEngine *subject;
};
