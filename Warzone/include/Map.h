#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Player;

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
        void subtractArmyNum(int num);
        int getArmyNum();
        void setArmyNum(int num);
        vector<Territory*> neighbours;
        vector<Territory*> getNeighbours();
        bool visited;
        void addOwner(Player *player);
        void removeOwner();
        Player* getOwner();
        bool static moreArmiesDeployed(const Territory* first, const Territory* second);
        bool static lessArmiesDeployed(const Territory* first, const Territory* second);
        vector<Territory*> getAllies();
        vector<Territory*> getEnemies();
        bool static isEnemy(const Territory* first, const Territory* second);
        bool static isAlly(const Territory* first, const Territory* second);

    private:
        string name;
        string continent;
        int armies = 0;
        Player* owner = nullptr;
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
        int getControlBonus();
    private:
        string name;
        int controlBonus;
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