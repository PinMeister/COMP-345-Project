#include <iostream>
#include <string>
#include <list>
#include <string>

#include "../Orders/Orders.h"
#include "../Cards/Cards.h" 

using namespace std;

class Player {
private:
	list<Territory*> _territories;
	Hand _hand; // or to change to deck cards to validate when Part 5 is done
	list<Orders*> _orders;
	int playerID;

public:
	list<Territory> toDefend();
	list<Territory> toAttack();
	void issueOrder(Orders* order);
	Player(const Player &player); // copy constructor
	Player& operator=(const Player &player); //assignment operator
	friend ostream& operator << (ostream &os, const Player &player); //stream insertion operator for Player
};