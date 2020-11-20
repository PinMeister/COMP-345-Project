#include "../include/Orders.h"
#include "../include/Map.h"
#include "../include/Player.h"
#include "../include/MapLoader.h"
#include "../include/GameEngine.h"

int main(){
    Territory* canada = new Territory("Canada", "North America");
    Territory* us = new Territory("United States", "North America");
    canada->setArmyNum(10);
    us->setArmyNum(5);

    vector<Territory*> territories;
    vector<Continent*> continents;
    Map map(territories, continents);
    map.addBorder(canada, us);

    Continent* na = new Continent("North America", 3);
    Continent* ca = new Continent("Central America", 3);

    map.addContinent(na);
    map.addContinent(ca);

    int naID = map.getContinentIndex(na);
    int caID = map.getContinentIndex(ca);

    map.addTerritoryToContinent(canada, naID);
    map.addTerritoryToContinent(us, naID);

    Player* player = new Player(1);
    Player* player2 = new Player(2);
    player->addTerritory(canada);
    //player->addTerritory(us);
    player2->addTerritory(us);
    cout << "Canada " << canada ->getArmyNum() << "\n";
    cout << "US " << us ->getArmyNum() << "\n\n";
    Advance* advance = new Advance(player, canada, us, 7);
    advance->execute();
    cout << "Canada " << canada ->getArmyNum() << "\n";
    cout << "US " << us ->getArmyNum();
    return 0;
}