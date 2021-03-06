#include <iostream>
#include <fstream>
#include <vector>

#include "../include/MapLoader.h"
#include "../include/Map.h"

using namespace std;

int main(){
    // array of all file paths
    vector<string> files = {"Warzone/maps/artic.map", "Warzone/maps/bigeurope.map", "Warzone/maps/google.map", "Warzone/maps/google_copy.map", "Warzone/maps/solar.map"};

    // create a MapLoader obj for each file and parse
    for(int i = 0; i < files.size(); i++){
        MapLoader *loader = new MapLoader(files[i]);
        // create a Map obj if .map file is correct
        if (loader->parse()){
            loader->createMap();
            cout << "Map created.\n";
        }
        cout << *loader << "\n\n";
        delete loader;
    }
    return 0;
}