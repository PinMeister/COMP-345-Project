#include <iostream>
#include <string>
#include <vector>

#include "../Orders/Orders.h"
#include "../Deck/Cards.h"
#include "../Map/Map.h"


using namespace std;

class Player {
private:
	vector<Territory*> territories;
	Hand* hand; // or to change to deck cards to validate when Part 5 is done
	vector<Order*> orders;
	int playerID;
	vector<Territory*> toDefendTerritory;
	vector<Territory*> toAttackTerritory;


public:
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
	void issueOrder(Order* order);
	Player(vector<Territory*> territories, Hand* hand, vector<Order*> orders, int playerID);
	Player(const Player &player); // copy constructor
	Player& operator=(const Player &player); //assignment operator
	friend ostream& operator << (ostream &os, const Player &player); //stream insertion operator for Player
};