#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include "../include/Orders.h"
#include "../include/GameEngine.h"
#include "../include/Map.h"
#include "../include/Player.h"
#include "../include/MapLoader.h"

using namespace std;
    //will be changed in assignment 2
int main(){

    vector <Territory*> territories;
    Territory* territory1 = new Territory("Luxemborg", "Europe");
    Territory* territory2 = new Territory("Canada", "North America");
    territories.push_back(territory1);
    territories.push_back(territory2);
    vector<Order*> orders;
    Territory* target = territory1;
    Territory* start = territory2;
    territory1->setArmyNum(10);
    territory2->setArmyNum(10);
    Player* player = new Player(territories, NULL, orders, 1);
    Airlift* airlift = new Airlift(player, start, target, 5);
    airlift->execute();
    int i = territory2->getArmyNum();
    int j = territory1->getArmyNum();
    cout << i << endl;
    cout << j << endl;

return 0;
};
