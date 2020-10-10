#include <iostream>
#include <fstream>
#include <vector>

#include "MapLoader.cpp"

using namespace std;

int main(){
    // array of all file paths
    vector<string> files {"Risk/maps/artic.map", "Risk/maps/bigeurope.map", "Risk/maps/google.map", "Risk/maps/google_copy.map", "Risk/maps/solar.map"};

    // create a MapLoader obj for each file and parse before deleting them
    for(int i = 0; i < files.size(); i++){
        MapLoader *loader = new MapLoader(files[i]);
        loader->parse();
        delete loader;
    }
}