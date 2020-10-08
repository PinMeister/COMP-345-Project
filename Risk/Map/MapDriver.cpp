#include <iostream>
#include <string>
#include <vector>
#include "Map.h"

using namespace std;

int main() {

    //Hardcoded map
    vector<Territory*> territories;
    Map map(territories);
    
    Territory* canada = new Territory("Canada", "North America");
    Territory* us = new Territory("United States", "North America");
    Territory* mexico = new Territory("Mexico", "North America");

    map.addTerritory(canada);
    map.addTerritory(us);
    map.addTerritory(mexico);

    territories = map.getTerritories();

    for (size_t i = 0; i < territories.size(); i++) {
        cout << territories[i]->getName() << endl;
    }

    cin.get();
    //map.addBorder(canada, us);
    //map.addBorder(us, mexico);
}