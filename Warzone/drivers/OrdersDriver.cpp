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
    territories.push_back(territory);
    vector<Order*> orders;
    Player* player = new Player(territories, NULL, orders, 1);
    Territory* target = territory;
    Deploy* deploy = new Deploy(player, 5, target);
    deploy->validate();
    deploy->execute();

    int showArmies = target->getArmyNum();
    cout << showArmies << endl;
    
    delete territory;
    delete player;
    delete deploy;
    delete target;

    territory = NULL;
    player = NULL; 
    deploy = NULL;
    target = NULL;

return 0;
};
