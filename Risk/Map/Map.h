#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Territory {
public:
    Territory();
    Territory(string name, string continent);
    Territory(string name, string continent, vector<Territory*> neighbours);
    Territory(const Territory &territory);
    string getName();
    string getContinent();
    vector<Territory*> neighbours;
private:
    string name;
    string continent;
};

class Continent {
public:
    Continent();
    Continent(string name, int armies);
    Continent(string name, int armies, vector<Territory*> members);
    Continent(const Continent &continent);
    void addTerritory(Territory* territory);
    vector<Territory*> getMembers();
private:
    string name;
    int numOfArmies;
    vector<Territory*> members;
};

class Map {
public:
    Map();
    Map(vector<Territory*> territories, vector<Continent*> continents);
    Map(const Map &map);
    void addContinent(Continent* continent);
    int getContinentIndex(Continent* continent);
    void addTerritoryToContinent(Territory* territory, int continentId);
    void addTerritory(Territory* territory);
    void addBorder(Territory* t1, Territory* t2);
    void addBorderIndex(int t1, int t2);
    vector<Territory*> getTerritories();
    vector<Continent*> getContinents();
    bool mapValidate();
    bool checkConnectedGraphs();
    bool checkContinentGraphs();
    bool checkContinentMembership();
private:
    vector<Territory*> territories;
    vector<Continent*> continents;
};
