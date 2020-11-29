#include "../include/MapLoader.h"
#include "../include/Map.h"

using namespace std;

int main(){
    ConquestFileReader *conquestLoader = new ConquestFileReader("Warzone/maps/Conquest_3D.map");
    ConquestFileReaderAdapter *adapter = new ConquestFileReaderAdapter(conquestLoader);
    Map *map;
    if (adapter->parse()){
        cout << "Map is loaded.\n";
        map = adapter->createMap();
        cout << "Map is created.\n";
    }
    //conquestLoader->showResult();

    cout << "\nContinents:\n";
    for(int i = 0; i < map->getContinents().size(); i++){
        cout << map->getContinents()[i]->getName() << "\n";
    }
    cout << "\nTerritories:\n";
    
    
    for(int i = 0; i < map->getTerritories().size(); i++){
        cout << map->getTerritories()[i]->getName() << ": \n";
        /*
        for(int j = 0; i < map->getTerritories()[i]->neighbours.size(); j++){
            cout << map->getTerritories()[i]->neighbours[j]->getName() << " ";
        }*/
        cout << "\n";
    }
    map->mapValidate();

    return 0;
}
