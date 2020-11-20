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
    Territory* territory = new Territory("Luxemborg", "Europe");
    // territories.push_back(territory);
    vector<Order*> orders;
    Territory* target = territory;
    Player* player = new Player(territories, NULL, orders, 1);
    target->setArmyNum(10);
    Bomb* bomb = new Bomb(player, target);
    bomb->validate();
    bomb->execute();
    int i = target->getArmyNum();
    cout << i << " armies in territory" <<endl;

return 0;
};
