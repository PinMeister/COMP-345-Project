#include <iostream>

#include "../include/MapLoader.h"
#include "../include/Map.h"
#include "../include/Player.h"
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

    // create players
    cout << "\nCreating players" << "\n";
    vector<Player*> *players = new vector<Player*>;
    for(int i = 0; i < 5; i++){
        Player *player = new Player(i);
        players->push_back(player);
        cout << "Player " << i + 1 << " id: " << player->getPlayerID() << "\n";
    }

    // create GameEngine
    cout << "\nCreating game" << "\n";
    GameEngine *gameEngine = new GameEngine();
    gameEngine->setMap(map); // create a ref to map
    gameEngine->setPlayers(players); // create a ref to players

    Startup *startUp = new Startup(players, map);
    cout << "startup phase completed" << "\n\n";

    for(int i = 0; i < 5; i++){
        Territory* temp = players->at(i)->getTerritories()[0];
        cout << "Player " << i + 1 << " id: " << players->at(i)->getPlayerID() << "\n" << "In " << temp->getName() << " with " << temp->getArmyNum() << " armies \n";
        temp = NULL;
        delete temp;
    }
}