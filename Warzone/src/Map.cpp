#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>


#include "../include/Map.h"
#include "../include/Player.h"

using namespace std;

// Empty constructor
Map::Map() {}

// Constructor with all arguments
Map::Map(vector<Territory*> territories, vector<Continent*> continents) {
    this->territories = territories;
    this->continents = continents;
}

// Copy constructor
Map::Map(const Map &map) {
    this->territories = map.territories;
    this->continents = map.continents;

}// Assignment operator
Map& Map::operator=(const Map &map) {
    this->territories = map.territories;
    this->continents = map.continents;
    return *this;
}

// Stream insertion operator
ostream& operator<<(ostream& out, Map map) {
    vector<Territory*> territories = map.getTerritories();
    vector<Continent*> continents = map.getContinents();
    for (size_t i = 0; i < territories.size(); i++)
        out << "Territory name: " + territories[i]->getName();
    for (size_t i = 0; i < continents.size(); i++)
        out << "Continent name: " + continents[i]->getName();
    return out;
}

// Add continent to map
void Map::addContinent(Continent *continent) {
    continents.push_back(continent);
}

// Iterate through continent list to obtain continent index
int Map::getContinentIndex(Continent *continent) {
    auto iterator = find(continents.begin(), continents.end(), continent);
    if (iterator != continents.end()) 
        return distance(continents.begin(), iterator);
    else
        return -1;
}

// Add territory to continent
void Map::addTerritoryToContinent(Territory *territory, int continentId) {
    continents[continentId]->addTerritory(territory);
}

// Add territory to map
void Map::addTerritory(Territory *territory) {
    territories.push_back(territory);
}

// Add bordering territory to territory's neighbours
void Map::addBorder(Territory *t1, Territory *t2) {
    t1->neighbours.push_back(t2);
    t2->neighbours.push_back(t1);
}

// Connect t2 to t1 using index
void Map::addBorderIndex(int t1, int t2) {
    territories[t1]->neighbours.push_back(territories[t2]);
}

// Get list of continents that map has
vector<Continent*> Map::getContinents() {
    return continents;
}

// Get list of territories that map has
vector<Territory*> Map::getTerritories() {
    return territories;
}

// Check that entire map is a connected graph
bool Map::checkMapConnectedGraph() {
    resetVisitedTerritories();
    int visited = 0;
    for (size_t i = 0; i < territories.size(); i++) {
        if (territories[i]->visited == false) {
            territories[i]->visited = true;
            if (territories[i]->neighbours.size() == 0) {
                cout << "\n***Map is NOT a connected graph!***" << endl;
                return false; 
            }
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

// Check that all continents are connected subgraphs
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
                if (continentMembers[j]->neighbours.size() == 0) {
                    cout << "\n***Continent " + continents[i]->getName() + " is NOT a connected subgraph!***" << endl;
                    return false; 
                }
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

// Recursive method that adds 1 to the number of visited territories for each unique territory that hasn't been already visited
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

// Similar method as above used to check continent subgraphs
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

// Check that each territory belongs to one and only one continent
bool Map::checkContinentMembership() {
    map<string, string> listOfCountries;
    for (size_t i = 0; i < continents.size(); i++) {
        vector<Territory*> continentMembers = continents[i]->getMembers();
        for (size_t j = 0; j < continentMembers.size(); j++)
            if (listOfCountries.count(continentMembers[j]->getName()) > 0) {
                cout << "\n***Territory " + continentMembers[j]->getName() + " DOES NOT have unique membership!" << endl;
                return false;
            }
            else {
                listOfCountries[continentMembers[j]->getName()] = continentMembers[j]->getContinent();
            }
    }
    cout << "\n***Territories have unique membership!***" << endl;
    return true;    
}

// Set all visited territories to false, used before checking connected graph
void Map::resetVisitedTerritories() {
    for (size_t i = 0; i < territories.size(); i++) {
        if (territories[i]->visited == true) {
            territories[i]->visited = false;
        }
    }
}

// Check if all 3 methods are true to determine if the map is valid
bool Map::mapValidate() {
    if (checkContinentMembership() && checkMapConnectedGraph() && checkContinentGraphs()) {
        cout << "\n***Map is valid!***" << endl;
        return true;
    }
    else {
        cout << "\n***Map is not valid!***" << endl;
        return false;
    }
}

// Empty constructor
Territory::Territory() {};

// Partial constructor
Territory::Territory(string name, string continent) {
    this->name = name;
    this->continent = continent;
    this->visited = false;
}

// Constructor with all arguments
Territory::Territory(string name, string continent, vector<Territory*> neighbours) {
    this->name = name;
    this->continent = continent;
    this->neighbours = neighbours;
    this->visited = false;
}

// Copy constructor
Territory::Territory(const Territory &territory) {
    this->name = territory.name;
    this->continent = territory.continent;
    this->neighbours = territory.neighbours;
    this->visited = territory.visited;
    this->armies = territory.armies;
    this->owner = territory.owner;
}

// Assignment operator
Territory& Territory::operator=(const Territory &territory) {
    this->name = territory.name;
    this->continent = territory.continent;
    this->neighbours = territory.neighbours;
    this->visited = territory.visited;
    this->armies = territory.armies;
    this->owner = territory.owner;
    return *this;
}

// Stream insertion operator     
ostream& operator << (ostream &out, Territory territory) {
    out << "Name: " << territory.getName() << " Continent: " << territory.getContinent();
    return out;
}

// Return name of territory
string Territory::getName() {
    return name;
}

// Return name of continent that territory is a part of
string Territory::getContinent() {
    return continent;
}

void Territory::addArmyNum(int num){
    armies += num;
}

void Territory::subtractArmyNum(int num){
    armies -= num;
}

int Territory::getArmyNum(){
    return armies;
}

void Territory::setArmyNum(int num){
    armies = num;
}

vector<Territory*> Territory::getNeighbours() {
    return neighbours; 
}

// Empty constructor
Continent::Continent() {};

// Partial constructor
Continent::Continent(string name, int armies) {
    this->name = name;
    controlBonus = armies;
}

// Constructor with all arguments
Continent::Continent(string name, int armies, vector<Territory*> members) {
    this->name = name;
    controlBonus = armies;
    this->members = members;
}

// Copy constructor
Continent::Continent(const Continent &continent) {
    this->name = continent.name;
    this->controlBonus = continent.controlBonus;
    this->members = continent.members;
}


// Assignment operator
Continent& Continent::operator=(const Continent &continent) {
    this->name = continent.name;
    this->controlBonus = continent.controlBonus;
    this->members = continent.members;
    return *this;
}

// Stream insertion operator     
ostream& operator << (ostream &out, Continent continent) {
    out << "Name: " << continent.getName();
    return out;
}

// Add territory as a member of the continent
void Continent::addTerritory(Territory* territory) {
    members.push_back(territory);
}

// Return name of continent
string Continent::getName() {
    return name;
}

// Return list of territories that are a part of continent
vector<Territory*> Continent::getMembers() {
    return members;
}

int Continent::getControlBonus() {
    return controlBonus;
}

void Territory::addOwner(Player *player){
    owner = player;
}

void Territory::removeOwner(){
    owner = nullptr;
}

Player* Territory::getOwner(){
    return owner;
}