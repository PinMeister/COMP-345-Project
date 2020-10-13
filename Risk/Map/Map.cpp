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

bool Map::checkMapConnectedGraph() {
    resetVisitedTerritories();
    int visited = 0;
    for (size_t i = 0; i < territories.size(); i++) {
        if (territories[i]->visited == false) {
            territories[i]->visited = true;
            visited = visitNeighbours(territories[i], visited);
        }
    }
    cout << "\nTotal territories in map: " + to_string(visited) << endl;
    if (visited == territories.size()) {
        cout << "\n***Map is a connected graph!***" << endl;
        return true;
    }
    else {
        cout << "\n***Map is NOT a connected graph!***" << endl;
        return false; 
    }
}

bool Map::checkContinentGraphs() {
    resetVisitedTerritories();
    for (size_t i = 0; i < continents.size(); i++) {
        string continentName = continents[i]->getName();
        vector<Territory*> continentMembers = continents[i]->getMembers();
        cout << "\nChecking " + continentName + " which has " + to_string(continentMembers.size()) + " members..." << endl;
        int visited = 0;
        for (size_t j = 0; j < continentMembers.size(); j++) {
            if (continentMembers[j]->visited == false) {
                continentMembers[j]->visited = true;
                visited = visitContinentNeighbours(continentMembers[j], continentName, visited);
            }
        }
        cout << "\nTotal territories in continent: " + to_string(visited) << endl;
        if (visited == continentMembers.size()) {
            cout << "\n***Continent " + continents[i]->getName() + " is a connected subgraph!***" << endl;
        }
        else {
            cout << "\n***Continent " + continents[i]->getName() + " is NOT a connected subgraph!***" << endl;
            return false;
        }
    }
    cout << "\n***All continents are connected subgraphs!***" << endl;
    return true;
}

int Map::visitNeighbours(Territory* territory, int visited) {
    vector<Territory*> neighbours = territory->neighbours;
    for (size_t i = 0; i < neighbours.size(); i++) {
        if (neighbours[i]->visited == false) {
            neighbours[i]->visited = true;
            visited = visitNeighbours(neighbours[i], visited);
        }
    }
    cout << "\nVisiting " + territory->getName() + "..." << endl;
    cout << "Total territories visited: " + to_string(visited + 1) << endl;
    return visited + 1;
}

int Map::visitContinentNeighbours(Territory* territory, string continent, int visited) {
    vector<Territory*> neighbours = territory->neighbours;
    for (size_t i = 0; i < neighbours.size(); i++) {
        if (neighbours[i]->visited == false && neighbours[i]->getContinent() == continent) {
            neighbours[i]->visited = true;
            visited = visitContinentNeighbours(neighbours[i], continent, visited);
        }
    }
    cout << "\nVisiting " + territory->getName() + "..." << endl;
    cout << "Total territories visited: " + to_string(visited + 1) << endl;
    return visited + 1;
}

bool Map::checkContinentMembership() {
    map<string, string> listOfCountries;
    for (size_t i = 0; i < continents.size(); i++) {
        vector<Territory*> continentMembers = continents[i]->getMembers();
        for (size_t j = 0; j < continentMembers.size(); j++)
            if (listOfCountries.count(continentMembers[j]->getName()) > 0) {
                cout << "***Territories DO NOT have unique membership!" << endl;
                return false;
            }
            else {
                listOfCountries[continentMembers[j]->getName()] = continentMembers[j]->getContinent();
            }
    }
    cout << "\n***Territories have unique membership!***" << endl;
    return true;    
}

void Map::resetVisitedTerritories() {
    for (size_t i = 0; i < territories.size(); i++) {
        if (territories[i]->visited == true) {
            territories[i]->visited = false;
        }
    }
}

bool Map::mapValidate() {
    if (checkMapConnectedGraph() && checkContinentGraphs() && checkContinentMembership()) {
        cout << "\n***Map is valid!***" << endl;
        return true;
    }
    else {
        cout << "\n***Map is not valid!***" << endl;
        return false;
    }
}

Territory::Territory() {};

Territory::Territory(string name, string continent) {
    this->name = name;
    this->continent = continent;
    this->visited = false;
}

Territory::Territory(string name, string continent, vector<Territory*> neighbours) {
    this->name = name;
    this->continent = continent;
    this->neighbours = neighbours;
    this->visited = false;
}

Territory::Territory(const Territory &territory) {
    this->name = territory.name;
    this->continent = territory.continent;
    this->neighbours = territory.neighbours;
    this->visited = territory.visited;
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

string Continent::getName() {
    return name;
}

vector<Territory*> Continent::getMembers() {
    return members;
}
