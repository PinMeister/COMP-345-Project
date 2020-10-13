#include "Player.h"
#include <vector>
#include <iostream>

using namespace std;

Player::Player(list<Territory*> territories, Hand* hand, list<Orders*> orders, int playerID) {
       this.territories = new list<Territory*>;
	   this.hand = hand;
	   this.orders = new list<Orders*>;
	   this.playerID = playerID;
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