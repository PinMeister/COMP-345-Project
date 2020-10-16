#include "../include/Player.h"
#include <vector>
#include <iostream>

using namespace std;

// default constructor
Player::Player(vector<Territory*> territories, Hand* hand, vector<Order*> orders, int playerID) {
       this->territories = territories;
	   this->hand = hand;
	   this->orders = orders;
	   this->playerID = playerID;
}

// copy constructor
Player::Player(const Player &player){
	   this->territories = player.territories;
	   this->hand = player.hand;
	   this->orders = player.orders;
	   this->playerID = player.playerID;
}

//assignment operator
Player& Player::operator=(const Player &player){ 
	   this->territories = player.territories;
	   this->hand = player.hand;
	   this->orders = player.orders;
	   this->playerID = player.playerID;
	
	return *this;
}

//stream insertion operator for Player
ostream& operator << (ostream &os, const Player &player){ 
	return os << "Player:" << player.playerID << " Player territories: " << player.territories.size()  << " Player hand: " << player.hand  << "Player orders: " << player.orders.size();
}

vector<Territory*> Player::toDefend() {
	// list<Territory*> toDefendTerritory;
	// MAKE A LOOP WITH THE LOGIC WHEN territories is impletemented
	// to check which have the flag to defend
	return this->toDefendTerritory;
}

vector<Territory*> Player::toAttack() {
	// list<Territory*> toAttackTerritory;
	// MAKE A LOOP WITH THE LOGIC WHEN territories is impletemented
	// to check which have the flag to attack
	return this->toAttackTerritory;
}

void Player::issueOrder(Order* order) {
	this->orders.push_back(order);
}