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
    Hand* hand = new Hand();
    vector<Order*> orders;
    Player* player = new Player(territories, hand, orders, 1);
    Territory* target = new Territory("Luxemburg", "Europe");

    Bomb* bomb = new Bomb(player, target);
    bomb->execute();

    delete territory;
    delete hand;
    delete player;

    territory = NULL;
    hand = NULL;
    player = NULL; 

    return 0;
};
