#include "../include/Player.h"
#include <vector>
#include <iostream>
#include <algorithm> 
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

// creates vector of countries to attack
// 1. get all territories controlled by player 
// 2. neigbours not in controlled are non_allied_neighbours
// 3. pick from non_allied_neighbours randomly and add to toAttackTerritory
vector<Territory*> Player::toAttack() {
	vector<Territory*> controlled = this->getTerritories(); // territories controlled by player
	vector<Territory*> non_allied_neighbours = this->get_neighbour_territories(this); // neighbouring territories not controlled by player
	
	// 1. check if you have enough army to deploy to areas to add
	// 2. if toAttackTerritory size is 0, pick index and check
	// 3. if toAttackTerritory size is 1+, make decision (odd/even) to decide whether to continue picking or not
	int deploy_limit = this->getReinforcementPool(); // get reinforcement pool to deploy

	if (non_allied_neighbours.size() > 0) 
	{
		//	Show possible territories to attack
		cout << " Territories to attack:";
		for (int i = 0; i < non_allied_neighbours.size(); i++)
			cout << "  (" << i << ") " + non_allied_neighbours[i]->getName() + "   " << non_allied_neighbours[i]->getArmyNum();
		cout << endl;

		cout << "Choose the territory to attack: ";
	}
	else 
	{
		cout << "You don't have any neighbours."<< endl;
		return this->toAttackTerritory;	
	}

	srand(time(NULL)); // different random outputs everytime it's run
	int index = rand() % non_allied_neighbours.size(); // generate random number
	while (true)
	{
		if (this->toAttackTerritory.size() <1 && deploy_limit>0) // if toAttackTerritory size is 0 and have armies to deploy
		{
			vector<Territory*>::iterator it;
			it = find(this->toAttackTerritory.begin(), this->toAttackTerritory.end(), non_allied_neighbours[index]);

			if (it != this->toAttackTerritory.end()) // if the territory pick is already in toAttackTerritory
			{
				cout << non_allied_neighbours[index]->getName() << " already picked." << endl;
				index = rand() % controlled.size();
				continue;
			}
			else 
			{
				this->toAttackTerritory.push_back(non_allied_neighbours[index]);
				cout << non_allied_neighbours[index]->getName() << " added to attacking territories." <<  endl;
				deploy_limit--;
			}	
		}
		else if (deploy_limit == 0) // if none to deploy, break the loop
		{
			cout << "No more reinforcements to deploy, finished picking." << endl;
			break;
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
				index = rand() % non_allied_neighbours.size();
			}
		}	
	}
	
	return this->toAttackTerritory;
}

void Player::issueOrder(Order* order) {
	this->orders.push_back(order);
}

void Player::addTerritory(Territory* territory){
	territories.push_back(territory);
}

vector<Territory*> Player::get_neighbour_territories(Player* p) {
	vector<Territory*> controlled = p->getTerritories(); 
	vector<Territory*> neighbouring_terrritories; 

	// Get neighbour territories ( territories to attack )
	for (Territory* c : controlled) {
		vector<Territory*> attacking = c->get_neighbours();
        
        // for territories to attack find if it's controlled by you
		for (Territory* neighbour : attacking) {
			auto result = find(controlled.begin(), controlled.end(), neighbour);
            if (result == controlled.end()) // vector doesn't contain element
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


vector<Territory*> Player::getTerritories(){
	return territories;
}

int Player::getPlayerID(){
	return playerID;
}

void Player::setOrdersRef(vector<Order*> ordersRef){
	orders = ordersRef;
}

int Player::getReinforcementPool(){
	return reinforcementPool;
}

void Player::setReinforcementPool(int i){
	this->reinforcementPool = i;
}