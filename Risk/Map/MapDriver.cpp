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
    Territory* guatemala = new Territory("Guatemala", "Central America");
    Territory* belize = new Territory("Belize", "Central America");
    Territory* elSalvador = new Territory("El Salvador", "Central America");
    Territory* honduras = new Territory("Honduras", "Central America");
    Territory* nicaragua = new Territory("Nicaragua", "Central America");

    map.addTerritory(canada);
    map.addTerritory(us);
    map.addTerritory(mexico);
    map.addTerritory(guatemala);
    map.addTerritory(belize);
    map.addTerritory(elSalvador);
    map.addTerritory(honduras);
    map.addTerritory(nicaragua);

    Continent* na = new Continent("North America", 3);
    Continent* ca = new Continent("Central America", 3);

    map.addContinent(na);
    map.addContinent(ca);

    int naID = map.getContinentIndex(na);
    int caID = map.getContinentIndex(ca);

    map.addTerritoryToContinent(canada, naID);
    map.addTerritoryToContinent(us, naID);
    map.addTerritoryToContinent(mexico, naID);
    //map.addTerritoryToContinent(canada, caID);
    map.addTerritoryToContinent(guatemala, caID);
    map.addTerritoryToContinent(belize, caID);
    map.addTerritoryToContinent(elSalvador, caID);
    map.addTerritoryToContinent(honduras, caID);
    map.addTerritoryToContinent(nicaragua, caID);

    territories = map.getTerritories();

    map.addBorder(canada, us);
    map.addBorder(us, mexico);
    map.addBorder(mexico, guatemala);
    map.addBorder(mexico, belize);
    map.addBorder(guatemala, belize);
    map.addBorder(guatemala, elSalvador);
    map.addBorder(guatemala, honduras);
    map.addBorder(belize, honduras);
    map.addBorder(elSalvador, honduras);
    map.addBorder(honduras, nicaragua);

    // Check for neighbours
    for (size_t i = 0; i < territories.size(); i++) {
        cout << "\n" + territories[i]->getName() + " has " + to_string(territories[i]->neighbours.size()) + " neighbour(s):" << endl;
        for (size_t j = 0; j < territories[i]->neighbours.size(); j++) {
            cout << "- " + territories[i]->neighbours[j]->getName() << endl;
        }
    }

    map.mapValidate();

    cin.get();
}
