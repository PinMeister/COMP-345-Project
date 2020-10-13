#include <iostream>
#include <string>
#include <list>
#include <string>

#include "../Orders/Orders.h"
#include "../Cards/Cards.h" // need part 3 to be done

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
};