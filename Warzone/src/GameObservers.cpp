#include "GameObservers.h"
#include "GameEngine.h"
#include <iostream>
using namespace std;

PhaseObserver::PhaseObserver() {};

PhaseObserver::PhaseObserver(GameEngine* game) {
    subject = game;
    subject->Attach(this);
}

PhaseObserver::~PhaseObserver() {
    subject->Detach(this);
}

// Update observer every time some new info comes up
void PhaseObserver::Update(Player* player, string phase, string info) { 
    if (this->player != player && this->phase != phase) { // Prevent repetition of player and phase if there is new info in same phase
        this->player = player;
        this->phase = phase;
        cout << endl << "Player " + to_string(player->getPlayerID()) + " " + phase << endl; // Display player and their current phase
    }
    this->info = info;
    cout << info << endl; // Display relevant information
}

StatsObserver::StatsObserver() {};

StatsObserver::StatsObserver(GameEngine* game) {
    subject = game;
    subject->Attach(this);
}

StatsObserver::~StatsObserver() {
    subject->Detach(this);
}

// Update observer every time a territory is captured
void StatsObserver::Update() { 
    vector<Player*> players = subject->players;
    int totalTerritories = subject->map->getTerritories().size();
    for (int i; i < players.size(); i++) {
        if (players[i]->getTerritories().size() > 0) { // Display player name only if they possess at least one territory
            int percentage = players[i]->getTerritories().size() / totalTerritories * 100;
            if (percentage = 100) { // Return if capture percentage is 100
                cout << endl << "Player " + to_string(players[i]->getPlayerID()) + " has captured the whole map! Congratulations!" << endl;
                return;
            }
            else {
                cout << endl << "Player " + to_string(players[i]->getPlayerID()) + "'s capture percentage: " + to_string(percentage) + "%" << endl;
            }
        }
    }
}
