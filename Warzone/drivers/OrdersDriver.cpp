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
    
int main(){

    vector <Territory*> territories;
    Territory* us = new Territory("United States", "North America");
    Territory* belize = new Territory("Belize", "Central America");
    us->setArmyNum(3);
    belize->setArmyNum(0);
    territories.push_back(us);
    territories.push_back(belize);
    vector<Order*> orders;
    Player* player = new Player(territories, NULL, orders, 1); //player created with territories us and belize

    Deploy* deploy = new Deploy(player, 5, us); //player deploys 5 to its territory us
    deploy->execute();
    int i = us->getArmyNum();
    cout << "After deploying, armies in the territory are " << i << endl << endl;

    Territory* canada = new Territory("Canada", "North America");   //player bombs a territory not held by it
    Bomb* bomb = new Bomb(player, canada);
    canada->setArmyNum(10);
    bomb->execute();
    int j = canada->getArmyNum();
    cout << "The armies in bombed territory are " << j << endl << endl;

    Blockade* blockade = new Blockade(player, us);  //player blockades its own territory
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
    Player* player2 = new Player(territories2, NULL, orders2, 2);   //player 2 created with territories mexico and guatemala
    Airlift* airlift = new Airlift(player2, mexico, guatemala, 5);  //player2 airlifts armies from between its own territories
    airlift->execute();
    cout << "The armies in the start territory after airlift are " << mexico->getArmyNum() << " and in the target territory after airlift are "<< guatemala->getArmyNum() <<endl << endl;

    vector <Territory*> territories3;
    vector <Territory*> territories4;
    vector<Order*> orders3;
    vector<Order*> orders4;
    Player* player3 = new Player(territories3, NULL, orders3, 3);
    Player* player4 = new Player(territories4, NULL, orders4, 4);
    Negotiate* negotiate = new Negotiate(player3, player4); //negotiating between two different players should be valid
    negotiate->execute();

return 0;
};
