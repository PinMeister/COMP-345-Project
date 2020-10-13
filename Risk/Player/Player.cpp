#include "Player.h"
#include <vector>
#include <iostream>

using namespace std;

// default constructor
Player::Player(list<Territory*> territories, Hand* hand, list<Orders*> orders, int playerID) {
       this.territories = new list<Territory*>;
	   this.hand = hand;
	   this.orders = new list<Orders*>;
	   this.playerID = playerID;
}

// copy constructor
Player::Player(const Player &player){
	   this.territories = player._territories;
	   this.hand = player._hand;
	   this.orders = player._orders;
	   this.playerID = player.playerID;
}

//assignment operator
Player& Player::operator=(const Player &player){ 
	   this.territories = player._territories;
	   this.hand = player._hand;
	   this.orders = player._orders;
	   this.playerID = player.playerID;
	
	return *this;
}

//stream insertion operator for Player
ostream& operator << (ostream &os, const Player &player){ 
	return os << "Player:" << player.playerID << endl << "Player territories: " << player._territories << endl << "Player hand: " << player._hand << endl << "Player orders: " << player._orders;
}

list toDefend() {
	list<Territory*> toDefendTerritory;
	// MAKE A LOOP WITH THE LOGIC WHEN territories is impletemented
	// to check which have the flag to defend
	return toDefendTerritory;
}

list toAttack() {
	list<Territory*> toAttackTerritory;
	// MAKE A LOOP WITH THE LOGIC WHEN territories is impletemented
	// to check which have the flag to attack
	return toAttackTerritory;
}

void issueOrder(Orders* order) {
	this.orders.push_back(order);
}