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
    Territory* us = new Territory("United States", "North America");
    Territory* belize = new Territory("Belize", "Central America");
    us->setArmyNum(3);
    belize->setArmyNum(0);
    territories.push_back(us);
    territories.push_back(belize);
    vector<Order*> orders;
    Player* player = new Player(territories, NULL, orders, 1);

    Deploy* deploy = new Deploy(player, 5, us);
    deploy->execute();
    int i = us->getArmyNum();
    cout << "After deploying, armies in the territory are " << i << endl << endl;

    Territory* canada = new Territory("Canada", "North America");
    Bomb* bomb = new Bomb(player, canada);
    canada->setArmyNum(10);
    bomb->execute();
    int j = canada->getArmyNum();
    cout << "The armies in bombed territory are " << j << endl << endl;

    Blockade* blockade = new Blockade(player, us);
    blockade->execute();
    cout << "The armies in the territory are now " << us->getArmyNum() << endl << endl;

    vector <Territory*> territories2;
    vector<Order*> orders2;
    Territory* mexico = new Territory("Mexico", "North America");
    Territory* guatemala = new Territory("Guatemala", "Central America");
    Territory* nicaragua = new Territory("Nicaragua", "Central America");
    mexico->setArmyNum(5);
    guatemala->setArmyNum(0);
    territories2.push_back(mexico);
    territories2.push_back(guatemala);
    Player* player2 = new Player(territories2, NULL, orders2, 2);
    Airlift* airlift = new Airlift(player2, mexico, guatemala, 5);
    airlift->execute();
    cout << "The armies in the start territory after airlift are " << mexico->getArmyNum() << " and in the target territory after airlift are "<< guatemala->getArmyNum() <<endl << endl;

return 0;
};
