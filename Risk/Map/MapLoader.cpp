#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "MapLoader.h"

using namespace std;

// data container for continents
struct continents {
    vector<string> names;
    vector<string> armyNums;
} continents;

// data container for countries
struct countries {
    vector<string> names;
    vector<string> continentId;
    vector<vector<string>> pos;
} countries;

// data container for borders
struct borders {
    vector<vector<string>> adjacent;
} borders;

// constructor
MapLoader::MapLoader(string path){
    mapPath = path;
    error = 0;
}

// copy constructor
MapLoader::MapLoader(const MapLoader &mapLoader){
    mapPath = mapLoader.mapPath;
    error = mapLoader.error;
}

// parse a .map file with a given path
// read data and store them in data containers
bool MapLoader::parse(){
    ifstream mapFile(mapPath); // open .map file
    // if successful
    if (mapFile.is_open()){
        string line;
        int currentBlock = -1; // current state
        // read the whole text file, 1 line at a time
        while (getline(mapFile, line)) {
            // if the line contains continents block, update state and skip
            if (line.find("[continents]") != string::npos){
                currentBlock = 0;
                continue;
            }
            // if the line contains countries block, update state and skip
            else if (line.find("[countries]") != string::npos){
                currentBlock = 1;
                continue;
            }
            // if the line contains borders block, update state and skip
            else if (line.find("[borders]") != string::npos){
                currentBlock = 2;
                continue;
            }

            if (!line.empty()){
                // check for state
                switch(currentBlock){
                    case 0:
                        parseContinent(line); // parse a single line in continents block
                        break;
                    case 1:
                        parseCountry(line); // parse a single line in countries block
                        break;
                    case 2:
                        parseBorder(line); // parse a single line in borders block
                        break;
                }
            }
        }
        mapFile.close();
    // if not successful
    }else{
        cout << "Unable to open map file " << mapPath << endl;
        return 0;
    }
    return 1;
}

int createMap(){

}

// parse a single line in continents block
// return bool
bool MapLoader::parseContinent(string line){
    // split the line
    vector<string> result = split(line, ' ');
    // if the size of result array is 2
    if (result.size() >= 2){
        // if the continent already exists
        if (find(continents.names.begin(), continents.names.end(), result[0]) != continents.names.end()){
            error += 1;
        }
        // if the second element is not a number
        if (!isDigit(result[1])){
            error += 1;
        }
        // store the data in the continents data container
        continents.names.push_back(result[0]);
        continents.armyNums.push_back(result[1]);
        return 1;
    }
    return 0;
}

// parse a single line in countries block
// return bool
bool MapLoader::parseCountry(string line){
    vector<string> result = split(line, ' ');
    // if the size of result array is 5
    if (result.size() >= 5){
        // if the country already exists
        if (find(countries.names.begin(), countries.names.end(), result[1]) != countries.names.end()){
            error += 1;
        }
        // if the third element is not a number
        if (!isDigit(result[2])){
            error += 1;
        }else{
            // if it is a number, check if it is less than 0 or too big
            if (stoi(result[2]) <= 0 || stoi(result[2]) > continents.names.size()){
                error += 1;
            }
        }
        // store the data in the conuntries data container
        countries.names.push_back(result[1]);
        countries.continentId.push_back(result[2]);
        countries.pos.push_back({result[3], result[4]});
        return 1;
    }
    return 0;
}

// parse a single line in borders block
// return bool
bool MapLoader::parseBorder(string line){
    vector<string> result = split(line, ' ');
    // if the size of result array is not 0
    if (result.size() > 0){
        // store the data in the borders data container
        // IMPORTANT NOTE: this array also contains the id of the country at the first index
        // When creating the Map obj, must ignore the first element
        borders.adjacent.push_back(result);
        return 1;
    }
    return 0;
}

// split a string with a specified delimiter and return an array of elements
vector<string> split(const string &line, char delim){
    vector<string> result;
    stringstream sstream(line);
    string element;
    
    while (getline(sstream, element, delim)){
        result.push_back(element);
    }
    return result;
}

// check if a string is a number
bool isDigit(const string &str){
    // return if a string contains a non-number character
    return (str.find_first_not_of("0123456789") == string::npos);
}