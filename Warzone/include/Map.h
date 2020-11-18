#ifndef MAP_H
#define MAP_H

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
        Territory& operator=(const Territory &territory);
        friend ostream& operator<<(ostream& out, Territory territory);
        string getName();
        string getContinent();
        void addArmyNum(int num);
        int getArmyNum();
        vector<Territory*> neighbours;
        bool visited;
    private:
        string name;
        string continent;
        int armies = 0;
};

class Continent {
    public:
        Continent();
        Continent(string name, int armies);
        Continent(string name, int armies, vector<Territory*> members);
        Continent(const Continent &continent);
        Continent& operator=(const Continent &continent);
        friend ostream& operator<<(ostream& out, Continent continent);
        void addTerritory(Territory* territory);
        string getName();
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
        Map& operator=(const Map &map);
        friend ostream& operator<<(ostream& out, Map map);
        void addContinent(Continent* continent);
        int getContinentIndex(Continent* continent);
        void addTerritoryToContinent(Territory* territory, int continentId);
        void addTerritory(Territory* territory);
        void addBorder(Territory* t1, Territory* t2);
        void addBorderIndex(int t1, int t2);
        vector<Territory*> getTerritories();
        vector<Continent*> getContinents();
        bool mapValidate();
        bool checkMapConnectedGraph();
        bool checkContinentGraphs();
        bool checkContinentMembership();
        int visitNeighbours(Territory* territory, int visited);
        int visitContinentNeighbours(Territory* territory, string continent, int visited);
        void resetVisitedTerritories();
    private:
        vector<Territory*> territories;
        vector<Continent*> continents;
};
#endif 