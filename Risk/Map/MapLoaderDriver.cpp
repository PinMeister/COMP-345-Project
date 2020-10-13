#include <iostream>
#include <fstream>
#include <vector>

#include "MapLoader.cpp"
#include "Map.cpp"

using namespace std;

int main(){
    // array of all file paths
    vector<string> files = {"Risk/maps/artic.map", "Risk/maps/bigeurope.map", "Risk/maps/google.map", "Risk/maps/google_copy.map", "Risk/maps/solar.map"};

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