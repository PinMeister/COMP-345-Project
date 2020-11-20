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
    cout << "Player 1 owns " << player->getTerritories()[0]->getName() << " " << canada->getArmyNum() << "\n";
    cout << "Player 2 owns " << player2->getTerritories()[0]->getName() << " " << us ->getArmyNum() << "\n\n";
    Advance* advance = new Advance(player, canada, us, 7);
    advance->execute();
    cout << "Player 1 now owns ";
    for(auto&& t : player->getTerritories()){
        cout << t->getName() << " " << t->getArmyNum() << "\n";
    }
    cout << "Player 2 now owns ";
    for(auto&& t : player2->getTerritories()){
        cout << t->getName() << " " << t->getArmyNum() << "\n";
    }
    return 0;
}