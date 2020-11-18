#include "../include/Player.h"
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

// default constructor
Player::Player(int playerID){
	this->playerID = playerID;
}

// construtor with parameters
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


void Player::addTerritory(Territory* territory){
	territories.push_back(territory);
}

vector<Territory*> Player::getTerritories(){
	return territories;
}

// returns picked list of territories to defend
vector<Territory*> Player::toDefend() {

	vector<Territory*> controlled = this->getTerritories(); // territories controlled by player
	
	// show territories controlled by player 
	if (controlled.size() > 0)
	{	
		cout << "Currently controlled Territories and armies: ";
		for (int i=0; i< controlled.size(); i++)
		{
			cout << " (" << i << ") "  + controlled[i]->getName()  + "   " << controlled[i]->getArmyNum() << endl;
		}
	}
	else 
	{
		cout << " You currently don't control any territories. " << endl;
		return this->toDefendTerritory;	
	}
	
	cout << "Choose a territory to defend (number corresponding to territory):" << endl;
	
	//choose territory(ies) to defend
	srand(time(NULL)); // different random outputs everytime it's run
	int index = rand() % controlled.size();
		while (true)
		{
			// 1. check if picked already 
			// 2. if not picked, push to toDefendTerritory vector
			vector<Territory*>::iterator it;
			it = find(this->toDefendTerritory.begin(), this->toDefendTerritory.end(), controlled[index]);

			if (it != this->toDefendTerritory.end())
			{
				cout << controlled[index]->getName() << " already picked." << endl;
			}
			else 
			{
				cout << controlled[index]->getName() + " picked."<< endl;
				this->toDefendTerritory.push_back(controlled[index]);
			}

			// 1. if toDefendTerritory size is 0, pick another index and check
			// 2. if toDefendTerritory size is 1*, make a decision (odd/even) to decide whether to continue picking or not
			if (this->toDefendTerritory.size() < 1) {
				index = rand() % controlled.size();
				continue;
			}
			else 
			{
				int decision = rand() % 100;  // take a random number from 0 to 100
				if (decision % 2 == 0) // if even, finish picking
				{
					cout << "Finished Picking." << endl;
					break;
				}
				else // if odd, continue picking
				{
					cout << "Pick another territory." << endl;
					index = rand() % controlled.size();
				}
			}	
		}
		return this->toDefendTerritory;
}

// list of territories to attack
vector<Territory*> Player::toAttack() {

	return this->toAttackTerritory;
}

// issue orders to deploy 
void Player::issueOrder(Order* order) {}


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
int Player::getPlayerID(){
	return playerID;
}

void Player::setOrdersRef(vector<Order*> ordersRef){
	orders = ordersRef;
}
