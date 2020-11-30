#include "../include/MapLoader.h"
#include "../include/Map.h"

using namespace std;

int main(){
    // create adapter and map objs
    string path;
    cin >> path;
    ConquestFileReader *conquestLoader = new ConquestFileReader(path);
    ConquestFileReaderAdapter *adapter = new ConquestFileReaderAdapter(conquestLoader);
    Map *map;
    // use overrided functions to create a map
    if (adapter->parse()){
        cout << "Map is loaded.\n";
        //conquestLoader->showResult();
        map = adapter->createMap();
        cout << "Map is created.\n";
    }
    

    // print out all the continents
    cout << "\nContinents:\n";
    for(int i = 0; i < map->getContinents().size(); i++){
        cout << map->getContinents()[i]->getName() << "\n";
    }
    // print out all the territories and its neighbours
    cout << "\nTerritories:\n";
    for(int i = 0; i < map->getTerritories().size(); i++){
        cout << map->getTerritories()[i]->getName() << ": ";
        cout << map->getTerritories()[i]->neighbours.size() << "\n";
        for(int j = 0; j < map->getTerritories()[i]->neighbours.size(); j++){
            cout << map->getTerritories()[i]->neighbours[j]->getName() << " ";
        }
        cout << "\n";
    }
    map->mapValidate();

    delete adapter;
    adapter = nullptr;
    delete map;
    map = nullptr;

    return 0;
}
