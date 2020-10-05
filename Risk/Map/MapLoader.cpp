#include "MapLoader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct continents {
    vector<string> names;
    vector<string> armyNums;
} continents;

struct countries {
    vector<string> names;
    vector<string> onContinent;
    vector<vector<string>> pos;
} countries;

struct borders {
    vector<vector<string>> adjacent;
} borders;


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
                        parseContinent(line);
                        break;
                    case 1:
                        
                        break;
                    case 2:
                        
                        
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

void parseContinent(string line){
    vector<string> result = split(line, ' ');
    continents.names.push_back(result[0]);
    continents.armyNums.push_back(result[1]);
}

void parseCountry(string line){
    vector<string> result = split(line, ' ');
    countries.names.push_back(result[1]);
    countries.onContinent.push_back(result[2]);
    countries.pos.push_back({result[3], result[4]});
}

void parseBorder(string line){
    vector<string> result = split(line, ' ');
    borders.adjacent.push_back(result);
}