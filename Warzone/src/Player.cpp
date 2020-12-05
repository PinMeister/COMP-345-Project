#include "../include/Player.h"
#include <vector>
#include <string>
#include <iostream>
#include <algorithm> 
#include <stdlib.h> 
#include <time.h>

using namespace std;

// default constructor
Player::Player(int playerID){
	this->playerID = playerID;
	this->reinforcementPool = 0;
}

// construtor with parameters
Player::Player(vector<Territory*> territories, Hand* hand, vector<Order*> orders, int playerID) {
	this->territories = territories;
	for(int i = 0; i < territories.size(); i++){
		territories[i]->addOwner(this);
	}
	this->hand = hand;
	this->orders = orders;
	this->playerID = playerID;
	this->reinforcementPool = 0;
}

// copy constructor
Player::Player(const Player &player){
	this->territories = player.territories;
	this->hand = player.hand;
	this->orders = player.orders;
	this->playerID = player.playerID;
	this->reinforcementPool = player.reinforcementPool;
	this->strategy = player.strategy;
}

//assignment operator
Player& Player::operator=(const Player &player){ 
	this->territories = player.territories;
	this->hand = player.hand;
	this->orders = player.orders;
	this->playerID = player.playerID;
	this->reinforcementPool = player.reinforcementPool;
	return *this;
}


//stream insertion operator for Player
ostream& operator << (ostream &os, const Player &player){ 
	return os << "Player:" << player.playerID << " Player territories: " << player.territories.size()  << " Player hand: " << player.hand  << "Player orders: " << player.orders.size();
}

vector<Territory*> Player::toDefend(PhaseObserver* phaseObserver) {
	return strategy->toDefend(phaseObserver);
}

// creates vector of countries to attack
// 1. get all territories controlled by player 
// 2. neigbours not in controlled are non_allied_neighbours
// 3. pick from non_allied_neighbours randomly and add to toAttackTerritory
vector<Territory*> Player::toAttack(PhaseObserver* phaseObserver) {
	return strategy->toAttack(phaseObserver);
}

void Player::issueOrder(GameEngine* gameEngine, PhaseObserver* phaseObserver) {
	return strategy->issueOrder(gameEngine, phaseObserver);
}

// add territory to player and remove the territory from the another player
void Player::addTerritory(Territory* territory){
	// if someone owns the territory, remove it from them
	if (territory->getOwner() != nullptr){
		territory->getOwner()->removeTerritory(territory);
		territory->removeOwner();
	}
	// add this to this player
	territory->addOwner(this);
	territories.push_back(territory);
}

// remove a territory from player
void Player::removeTerritory(Territory* territory){
	// find the territory and remove it
	for(int i = 0; i < territories.size(); i++){
		if (territories[i] == territory){
			territories.erase(territories.begin()+i);
		}
	}
}

// return player's territories
vector<Territory*> Player::getTerritories(){
	return territories;
}

// return players hand
Hand* Player::getHand()
{
	return hand;
}

// returns neighbours not controlled by player
vector<Territory*> Player::get_neighbour_territories(Player* p) {
	vector<Territory*> controlled = p->getTerritories(); 
	vector<Territory*> neighbouring_terrritories; 

	// Get neighbour territories ( territories to attack )
	for (Territory* c : controlled) {
		vector<Territory*> attacking = c->getNeighbours();
        
        // for territories to attack find if it's controlled by you
		for (Territory* neighbour : attacking) {
			auto result = find(controlled.begin(), controlled.end(), neighbour);
			auto exists = find(neighbouring_terrritories.begin(), neighbouring_terrritories.end(), neighbour);
			// vector doesn't contain element and doesn't already exist in vector
			if (result == controlled.end() && exists == neighbouring_terrritories.end())
			{
				neighbouring_terrritories.push_back(neighbour); // push to neighbouring territories vector
			}
			else 
			{
				continue;
			}
		}
	}
	return neighbouring_terrritories;
}


// returns neighbours controlled by player
vector<Territory*> Player::get_friendly_neighbour(Player* p) {
	vector<Territory*> controlled = p->getTerritories(); 
	vector<Territory*> friendly_neighbours; 

	// Get neighbour territories ( territories to attack )
	for (Territory* c : controlled) {
		vector<Territory*> all_neighbours = c->getNeighbours();
        
        // for territories to attack find if it's controlled by you
		for (Territory* neighbour : all_neighbours) {
			auto result = find(controlled.begin(), controlled.end(), neighbour);
            if (result != controlled.end()) // vector contains the element
            {
				friendly_neighbours.push_back(neighbour); // push to neighbouring territories vector
            }
            else 
            {
                continue;
            }
		}
	}
	return friendly_neighbours;
}

int Player::getPlayerID(){
	return playerID;
}

vector<Order*> Player :: getPlayerOrders(){
	return orders;
}

int Player::getReinforcementPool(){
	return reinforcementPool;
}

void Player::setReinforcementPool(int i){
	this->reinforcementPool = i;
}

void Player::setOrdersRef(vector<Order*> ordersRef){
	orders = ordersRef;
}

void Player::setStrategy(PlayerStrategy *newStrat) {
	// delete the player's strategy and set it to new one
	delete this->strategy;
	this->strategy = newStrat;
}
