#include "MapLoader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;


MapLoader::MapLoader(string path){
    mapPath = path;
}

string MapLoader::parse(){
    ifstream mapFile(mapPath);
    if (mapFile.is_open()){
        string line;
        int currentBlock = -1;
        while (getline(mapFile, line)) {
            if (line.find("[continents]") != string::npos){
                currentBlock = 0;
            }
            else if (line.find("[countries]") != string::npos){
                currentBlock = 1;
            }
            else if (line.find("[borders]") != string::npos){
                currentBlock = 2;
            }

            vector<string> elements;
            if (!line.empty()){
                switch(currentBlock){
                    case 0:
                        elements = split(line, ' ');
                        break;
                    case 1:
                        elements = split(line, ' ');
                        break;
                    case 2:
                        elements = split(line, ' ');
                        
                }
            }
        }
        mapFile.close();
    }else{
        cout << "Unable to open map file " << mapPath << endl;
    }
    return "";
}

vector<string> split(const string &line, char delim) {
    vector<string> result;
    stringstream sstream(line);
    string element;

    while (getline(sstream, element, delim)) {
        result.push_back (element);
    }

    return result;
}
