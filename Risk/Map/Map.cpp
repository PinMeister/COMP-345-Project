#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Map.h"

using namespace std;

Map::Map() {}

Map::Map(vector<Territory*> territories, vector<Continent*> continents) {
    this->territories = territories;
    this->continents = continents;
}

Map::Map(const Map &map) {
    this->territories = map.territories;
    this->continents = map.continents;
}

void Map::addContinent(Continent *continent) {
    continents.push_back(continent);
}

int Map::getContinentIndex(Continent *continent) {
    auto iterator = find(continents.begin(), continents.end(), continent);
    if (iterator != continents.end()) 
        return distance(continents.begin(), iterator);
    else
        return -1;
}

void Map::addTerritoryToContinent(Territory *territory, int continentId) {
    continents[continentId]->addTerritory(territory);
}

void Map::addTerritory(Territory *territory) {
    territories.push_back(territory);
}

void Map::addBorder(Territory *t1, Territory *t2) {
    t1->neighbours.push_back(t2);
    t2->neighbours.push_back(t1);
}

// connect t2 to t1 using index
void Map::addBorderIndex(int t1, int t2) {
    territories[t1]->neighbours.push_back(territories[t2]);
}

vector<Continent*> Map::getContinents() {
    return continents;
}

vector<Territory*> Map::getTerritories() {
    return territories;
}

/*bool Map::checkConnectedGraphs() {

}*/

bool Map::checkContinentMembership() {
    map<string, string> listOfCountries;
    for (size_t i = 0; i < continents.size(); i++) {
        vector<Territory*> continentMembers = continents[i]->getMembers();
        for (size_t j = 0; j < continentMembers.size(); j++)
            if (listOfCountries.count(continentMembers[j]->getName()) > 0) {
                return false;
            }
            else {
                listOfCountries[continentMembers[j]->getName()] = continentMembers[j]->getContinent();
            }
    }
    return true;    
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

string Territory::getContinent() {
    return continent;
}

Continent::Continent() {};

Continent::Continent(string name, int armies) {
    this->name = name;
    numOfArmies = armies;
}

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

void Continent::addTerritory(Territory* territory) {
    members.push_back(territory);
}

vector<Territory*> Continent::getMembers() {
    return members;
}
