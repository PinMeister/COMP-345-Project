#include "../Player/Player.h"
#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

using namespace std;

void print(list<Territory*> const &list)
{
	for (auto const& i: list) {
		std::cout << i << "\n";
	}
}


int main() {
	list<Territory*> territories;
	Hand hand;
	list<Orders*> orders;
	int playerID = 1;
	cout << "Player being created: " << endl;
	Player player(territories, hand, orders, playerID);
	cout << "Player has been created." << endl;

	cout << endl;
	cout << "Player territories to DEFEND: " << endl;
	cout << print(player.toDefend()) << endl;

	cout << "Player territories to ATTACK: " << endl;
	cout << print(player.toAttack()) << endl;

	cout << "Player orders list BEFORE adding a new ORDER: " << endl;
	cout << print(player.orders) << endl;

	Orders tempOrder = new Orders(); // ADD params when this is done
	palyer.issueOrder(tempOrder);

	cout << "Player orders list AFTER adding a new ORDER: " << endl;
	print(player.orders);

	return 0;
}