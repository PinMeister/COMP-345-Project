#include <iostream>
#include <string>
#include <vector>
#include "Map.h"

using namespace std;

Map::Map() {}

Map::Map(vector<Territory*> territories) {
    this->territories = territories;
}

Map::Map(const Map &map) {
    this->territories = map.territories;
}

void Map::addTerritory(Territory *territory) {
    territories.push_back(territory);
}

void Map::addBorder(Territory *t1, Territory *t2) {
    t1->neighbours.push_back(t2);
    t2->neighbours.push_back(t1);
}

vector<Territory*> Map::getTerritories() {
    return territories;
}

Territory::Territory() {};

Territory::Territory(string name, string continent) {
    this->name = name;
    this->continent = continent;
}

Territory::Territory(string name, string continent, vector<Territory*> neighbours) {
    this->name = name;
    this->continent = continent;
    this->neighbours = neighbours;
}

Territory::Territory(const Territory &territory) {
    this->name = territory.name;
    this->continent = territory.continent;
    this->neighbours = territory.neighbours;
}

string Territory::getName() {
    return name;
}

Continent::Continent() {};

Continent::Continent(string name, int armies, vector<Territory*> members) {
    this->name = name;
    numOfArmies = armies;
    this->members = members;
}

Continent::Continent(const Continent &continent) {
    this->name = continent.name;
    this->numOfArmies = continent.numOfArmies;
    this->members = continent.members;
}
