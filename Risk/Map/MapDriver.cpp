#include <iostream>
#include <string>
#include <vector>
#include "Map.h"

using namespace std;

int main() {

    //Hardcoded map
    vector<Territory*> territories;
    vector<Continent*> continents;
    Map map(territories, continents);
    
    Territory* canada = new Territory("Canada", "North America");
    Territory* us = new Territory("United States", "North America");
    Territory* mexico = new Territory("Mexico", "North America");

    map.addTerritory(canada);
    map.addTerritory(us);
    map.addTerritory(mexico);

    Continent* na = new Continent("North America", 3);
    Continent* sa = new Continent("South America", 3);

    map.addContinent(na);
    map.addContinent(sa);

    int naID = map.getContinentIndex(na);
    int saID = map.getContinentIndex(sa);

    map.addTerritoryToContinent(canada, naID);
    map.addTerritoryToContinent(us, naID);
    map.addTerritoryToContinent(mexico, naID);
    //map.addTerritoryToContinent(canada, saID);

    territories = map.getTerritories();

    map.addBorder(canada, us);
    map.addBorder(us, mexico);

    // check for neighbours
    for (size_t i = 0; i < territories.size(); i++) {
        cout << territories[i]->getName() + " has " + to_string(territories[i]->neighbours.size()) + " neighbours." << endl;
        cout << territories[i]->getName() + "'s neighbours:" << endl;
        for (size_t j = 0; j < territories[i]->neighbours.size(); j++) {
            cout << "- " + territories[i]->neighbours[j]->getName() << endl;
        }
    }

    if (map.checkContinentMembership() == true)
        cout << "Territories have unique membership!" << endl;
    else
        cout << "Map is not valid!" << endl;

    cin.get();
}
