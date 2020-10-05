#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "MapLoader.h"

using namespace std;

struct continents {
    vector<string> names;
    vector<string> armyNums;
} continents;

struct countries {
    vector<string> names;
    vector<string> continentId;
    vector<vector<string>> pos;
} countries;

struct borders {
    vector<vector<string>> adjacent;
} borders;


MapLoader::MapLoader(string path){
    mapPath = path;
}
    
int MapLoader::parse(){
    ifstream mapFile(mapPath);
    if (mapFile.is_open()){
        string line;
        int currentBlock = -1;
        while (getline(mapFile, line)) {
            if (line.find("[continents]") != string::npos){
                currentBlock = 0;
                continue;
            }
            else if (line.find("[countries]") != string::npos){
                currentBlock = 1;
                continue;
            }
            else if (line.find("[borders]") != string::npos){
                currentBlock = 2;
                continue;
            }

            vector<string> elements;
            if (!line.empty()){
                switch(currentBlock){
                    case 0:
                        parseContinent(line);
                        break;
                    case 1:
                        parseCountry(line);
                        break;
                    case 2:
                        parseBorder(line);
                        break;
                }
            }
        }
        mapFile.close();
    }else{
        cout << "Unable to open map file " << mapPath << endl;
        return 0;
    }
    return 1;
}

vector<string> split(const string &line, char delim) {
    vector<string> result;
    stringstream sstream(line);
    string element;

    while (getline(sstream, element, delim)) {
        result.push_back(element);
    }

    return result;
}

int parseContinent(string line){
    vector<string> result = split(line, ' ');
    if (result.size() >= 2){
        continents.names.push_back(result[0]);
        continents.armyNums.push_back(result[1]);
        return 1;
    }
    return 0;
}

int parseCountry(string line){
    vector<string> result = split(line, ' ');
    if (result.size() >= 5){
        countries.names.push_back(result[1]);
        countries.continentId.push_back(result[2]);
        countries.pos.push_back({result[3], result[4]});
        return 1;
    }
    return 0;
}

int parseBorder(string line){
    vector<string> result = split(line, ' ');
    if (result.size() > 0){
        borders.adjacent.push_back(result);
        return 1;
    }
    return 0;
}