#include "../include/GameObservers.h"
#include "../include/GameEngine.h"
#include <iostream>
using namespace std;

// Default constructor
PhaseObserver::PhaseObserver() {};

// Constructor with GameEngine parameter
PhaseObserver::PhaseObserver(GameEngine* game) {
    subject = game;
    subject->Attach(this);
}

// Copy constructor
PhaseObserver::PhaseObserver(const PhaseObserver &phaseObserver) {
	   this->subject = phaseObserver.subject;
	   this->player = phaseObserver.player;
	   this->phase = phaseObserver.phase;
       this->info = phaseObserver.info;
}

// Assignment operator
PhaseObserver& PhaseObserver::operator = (const PhaseObserver &phaseObserver) { 
	   this->subject = phaseObserver.subject;
	   this->player = phaseObserver.player;
	   this->phase = phaseObserver.phase;
       this->info = phaseObserver.info;
	return *this;
}

// Stream insertion operator
ostream& operator << (ostream &os, PhaseObserver &phaseObserver) { 
	return os << "\n Current game engine:" << phaseObserver.subject 
    << "\n Current player: " << phaseObserver.player  
    << "\n Current phase: " << phaseObserver.phase  
    << "\n Relevent information: " << phaseObserver.info;
}

// Destructor
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

GameEngine* PhaseObserver::getSubject() {
    return subject;
}

Player* PhaseObserver::getPlayer() {
    return player;
};

string PhaseObserver::getPhase() {
    return phase;
};

string PhaseObserver::getInfo() {
    return info;
};

// Default constructor
StatsObserver::StatsObserver() {};

// Constructor with GameEngine parameter
StatsObserver::StatsObserver(GameEngine* game) {
    subject = game;
    subject->Attach(this);
}

// Copy constructor
StatsObserver::StatsObserver(const StatsObserver &statsObserver) {
	   this->subject = statsObserver.subject;
}

// Assignment operator
StatsObserver& StatsObserver::operator = (const StatsObserver &statsObserver) { 
	   this->subject = statsObserver.subject;
	return *this;
}

// Stream insertion operator
ostream& operator << (ostream &os, StatsObserver &statsObserver) { 
	return os << "\n Current game engine:" << statsObserver.subject;
}

// Destructor
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

GameEngine* StatsObserver::getSubject() {
    return subject;
}
