#include "../Player/Player.h"
#include "../Orders/Orders.h"
#include "../Deck/Cards.h"
#include "../Map/Map.h"

#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

using namespace std;

int main() {
	vector<Territory*> territories;
	Hand* hand = new Hand();
	vector<Order*> orders;
	int playerID = 1;
	vector<Territory*> toDefendTerritory;
	vector<Territory*> toAttackTerritory;

	Territory* canada = new Territory("Canada", "North America");
    Territory* us = new Territory("United States", "North America");
    Territory* mexico = new Territory("Mexico", "North America");

	toDefendTerritory.push_back(canada);
	toDefendTerritory.push_back(us);
	toAttackTerritory.push_back(mexico);

	Player* player = new Player(territories, hand, orders, playerID); 
	cout << "Player being created: " << endl;
	cout << "Player has been created." << endl;
	cout << endl;
	cout << "Player territories to DEFEND: " << endl;
	player->toDefend();
	cout << " to Defend"<< "Canada, United States" << endl;

	player->toAttack();
	cout << "Player territories to ATTACK: " << endl;
	cout << " to Defend"<< "Mexico" << endl;

	cout << "Player orders list BEFORE adding a new ORDER: " << endl;

	Order* tempOrder = new Order(); // ADD params when this is done
	player->issueOrder(tempOrder);

	cout << "Player orders list AFTER adding a new ORDER: " << endl;

	cin.get();

	delete canada;
	delete us;
	delete mexico;
	delete hand;
	delete player;

	return 0;
}