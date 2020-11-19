#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <vector>

#include "../include/Orders.h"
#include "../include/Cards.h"
#include "../include/Map.h"

using namespace std;

class Order;
class Hand;
class OrdersList;

class Player {
	private:
		vector<Territory*> territories;
		Hand* hand; // player's cards
		OrdersList* orderList;
		vector<Order*> orders;
		int playerID;
		vector<Territory*> toDefendTerritory;
		vector<Territory*> toAttackTerritory;
		int reinforcementPool;
		
	public:
		vector<Territory*> toDefend();	// returns list of territories to be defended
		vector<Territory*> toAttack();	// returns list of territories to be attacked		
		void issueOrder();	// generates an order to add to order list
		Player(int playerID);
		Player(vector<Territory*> territories, Hand* hand, vector<Order*> orders, int playerID);
		Player(const Player &player); // copy constructor
		Player& operator=(const Player &player); //assignment operator
		friend ostream& operator << (ostream &os, const Player &player); //stream insertion operator for Player
		void addTerritory(Territory* territory);
		vector<Territory*> getTerritories();
		int getPlayerID();
		vector<Order*> getPlayerOrders();
		int getReinforcementPool();
		void setReinforcementPool(int i);
		void setOrdersRef(vector<Order*> orders);
		vector<Territory*> get_neighbour_territories(Player* p);
		vector<Territory*> get_friendly_neighbour(Player* p);
};
#endif 
