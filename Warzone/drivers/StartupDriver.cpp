#include <iostream>

#include "../include/GameEngine.h"

using namespace std;

int main(){
    cout << "Loading Map" << "\n";
    // load and create a map
    MapLoader *loader = new MapLoader("Warzone/maps/google.map");
    Map* map;
    if (loader->parse()){
        map = loader->createMap();
        cout << "Map created.\n";
    }

    int playerNum = 5;

    // create players
    cout << "\nCreating players" << "\n";
    vector<Player*> players;
    for(int i = 0; i < playerNum; i++){
        Player *player = new Player(i);
        players.push_back(player);
        cout << "Player " << i + 1 << " id: " << player->getPlayerID() << "\n";
    }

    // create GameEngine
    cout << "\nCreating game" << "\n";
    Startup *startUp = new Startup(&players, map);
    cout << "startup phase completed" << "\n\n";

    // output all players' army nums and owned territories
    for(int i = 0; i < playerNum; i++){
        cout << "Player " << i + 1 << " id: " << players[i]->getPlayerID() << " with armies "  << players[i]->getReinforcementPool() << "\nTerritories: " << players[i]->getTerritories().size() << "\n";
        for(int j = 0; j < players[i]->getTerritories().size(); j++){
            cout << players[i]->getTerritories()[j]->getName() << " ";
        }
        cout << "\n\n";
    }

    cout << "\n" << *startUp;

    delete startUp;
    startUp = NULL;
    return 0;
}