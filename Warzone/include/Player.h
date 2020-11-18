#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "../include/Orders.h"
#include "../include/Cards.h"
#include "../include/Map.h"

using namespace std;

class Player {
	private:
		vector<Territory*> territories;
		Hand* hand; // player's cards
		OrdersList* orderList;
		vector<Order*> orders;
		int playerID;
		vector<Territory*> toDefendTerritory;
		vector<Territory*> toAttackTerritory;
	public:
		vector<Territory*> toDefend();
		vector<Territory*> toAttack();
		void issueOrder(Order* order);
		Player(int playerID);
		Player(vector<Territory*> territories, Hand* hand, vector<Order*> orders, int playerID);
		Player(const Player &player); // copy constructor
		Player& operator=(const Player &player); //assignment operator
		friend ostream& operator << (ostream &os, const Player &player); //stream insertion operator for Player
		void addTerritory(Territory* territory);
		vector<Territory*> getTerritories();
		int getPlayerID();
		void setOrdersRef(vector<Order*> orders);
};