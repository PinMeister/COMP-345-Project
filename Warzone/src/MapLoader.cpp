#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

#include "../include/Map.h"
#include "../include/MapLoader.h"

using namespace std;

//**************** MapLoader ****************

// constructor
MapLoader::MapLoader(string path){
    mapPath = path;
    error = 0;
}

// copy constructor
MapLoader::MapLoader(const MapLoader &mapLoader){
    // copy everything
    mapPath = mapLoader.mapPath;
    error = mapLoader.error;
    continentsData = mapLoader.continentsData;
    countriesData = mapLoader.countriesData;
    bordersData = mapLoader.bordersData;
}

// destructor
MapLoader::~MapLoader(){
    mapPath = "";
    error = 0;
    clearData(); // empty all arrays
}

// assignment operator
MapLoader& MapLoader::operator=(const MapLoader &mapLoader){
    mapPath = mapLoader.mapPath;
    error = mapLoader.error;
    continentsData = mapLoader.continentsData;
    countriesData = mapLoader.countriesData;
    bordersData = mapLoader.bordersData;

    return *this;
}

// stream insertion operator
ostream& operator<<(ostream& out, const MapLoader &mapLoader){
    out << "Path: " << mapLoader.mapPath << "\nError(s): " << mapLoader.error;
    return out;
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
            // if the line contains continents block,
            if (line.find("[continents]") != string::npos){
                currentBlock = 0; // update state
                continue; // skip this line
            // if the line contains countries block
            }else if (line.find("[countries]") != string::npos){
                currentBlock = 1;
                continue;
            // if the line contains borders block
            }else if (line.find("[borders]") != string::npos){
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
        cout << "Parse completed, " << error << " errors found.\n";
        if (error > 0){
            return 0;
        }
    // if not successful
    }else{
        cout << "Unable to open map file " << mapPath << endl;
        return 0;
    }
    return 1;
}

// create a Map obj using data continers
Map* MapLoader::createMap(){
    Map *map = new Map(); // new Map
    // add continents to the Map
    for (int i = 0; i < continentsData.names.size(); i++){
        Continent *continent = new Continent(continentsData.names[i], stoi(continentsData.armyNums[i]));
        map->addContinent(continent);
    }

    // add territories to the Map
    for (int i = 0; i < countriesData.names.size(); i++){
        Territory *country = new Territory(countriesData.names[i], continentsData.names[stoi(countriesData.continentId[i]) - 1]);
        map->addTerritory(country);
        // add territories to the continent
        map->addTerritoryToContinent(country, stoi(countriesData.continentId[i]) - 1);
    } 
    
    // add borders
    for(int i = 0; i < bordersData.adjacent.size(); i++){
        for(int j = 1; bordersData.adjacent[i].size() > 1 && j < bordersData.adjacent[i].size(); j++){
            if (isDigit(bordersData.adjacent[i][j])){
             map->addBorderIndex(i, stoi(bordersData.adjacent[i][j]) - 1);
            }
        }
    }
    return map;
}

// parse a single line in continents block
// return bool
bool MapLoader::parseContinent(string line){
    // split the line
    vector<string> result = split(line, ' ');
    // if the size of result array is 2
    if (result.size() >= 2){
        // if the continent already exists
        if (find(continentsData.names.begin(), continentsData.names.end(), result[0]) != continentsData.names.end()){
            error += 1;
            cout << result[0] << " continent already exists!\n";
        }
        // if the second element is not a number
        if (!isDigit(result[1])){
            error += 1;
            cout << result[0] << " Bonus is not a number!\n";
        }
        // store the data in the continents data container
        continentsData.names.push_back(result[0]);
        continentsData.armyNums.push_back(result[1]);
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
        if (find(countriesData.names.begin(), countriesData.names.end(), result[1]) != countriesData.names.end()){
            error += 1;
            cout << result[1] << " country already exists!\n";
        }
        // if the third element is not a number
        if (!isDigit(result[2])){
            error += 1;
            cout << result[2] << " continent id is not a number!\n";
        }else{
            // if it is a number, check if it is less than 0 or too big
            if (stoi(result[2]) <= 0 || stoi(result[2]) > continentsData.names.size()){
                error += 1;
                cout << result[2] << " continent id is not valid!\n";
            }
        }
        // store the data in the conuntries data container
        countriesData.names.push_back(result[1]);
        countriesData.continentId.push_back(result[2]);
        //countriesData.pos.push_back({result[3], result[4]});
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
        bordersData.adjacent.push_back(result);
        return 1;
    }
    return 0;
}

// clear all the arrays from the structs
void MapLoader::clearData(){
    continentsData.names.clear();
    continentsData.armyNums.clear();
    countriesData.names.clear();
    countriesData.continentId.clear();
    countriesData.pos.clear();
    bordersData.adjacent.clear();
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


//**************** ConquestFileReader ****************


ConquestFileReader::ConquestFileReader(string path){
    mapPath = path;
    error = 0;
}

ConquestFileReader::ConquestFileReader(const ConquestFileReader &conquestLoader){
    mapPath = conquestLoader.mapPath;
    error = conquestLoader.error;
}

ConquestFileReader::~ConquestFileReader(){
    mapPath = "";
    error = 0;
}

ConquestFileReader& ConquestFileReader::operator=(const ConquestFileReader &conquestLoader){
    if (this != &conquestLoader){
        this->mapPath = conquestLoader.mapPath;
        this->error = conquestLoader.error;
    }
    return *this;
}

ostream& operator<<(ostream& out, const ConquestFileReader &conquestLoader){
    out << "Path: " << conquestLoader.mapPath << "\nError(s): " << conquestLoader.error;
    return out;
}

bool ConquestFileReader::parse(){
    ifstream mapFile(mapPath); // open .map file
    // if successful
    if (mapFile.is_open()){
        string line;
        int currentBlock = -1; // current state
        // read the whole text file, 1 line at a time
        while (getline(mapFile, line)) {
            // if the line contains continents block,
            if (line.find("[Continents]") != string::npos){
                currentBlock = 0; // update state
                continue; // skip this line
            // if the line contains countries block
            }else if (line.find("[Territories]") != string::npos){
                currentBlock = 1;
                continue;
            }

            if (!line.empty()){
                line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
                // check for state
                switch(currentBlock){
                    case 0:
                        parseContinent(line); // parse a single line in continents block
                        break;
                    case 1:
                        parseTerritory(line); // parse a single line in territories block
                        break;
                }
            }
        }
        mapFile.close();
        convertTerritoryToInt();
        cout << "Parse completed, " << error << " errors found." << endl;
        if (error > 0){
            return 0;
        }
    // if not successful
    }else{
        cout << "Unable to open map file " << mapPath << endl;
        return 0;
    }
    return 1;
}

string ConquestFileReader::getPath(){
    return mapPath;
}

bool ConquestFileReader::parseContinent(string line){
    vector<string> result = split(line, '=');
    // if the size of result array is 2
    if (result.size() >= 2){
        // if the continent already exists
        if (find(continentsData.names.begin(), continentsData.names.end(), result[0]) != continentsData.names.end()){
            error += 1;
            cout << result[0] << " continent already exists!" << endl;
        }
        // store the data in the continents data container
        continentsData.names.push_back(result[0]);
        continentsData.armyNums.push_back(result[1]);
        return 1;
    }
    return 0;
}

bool ConquestFileReader::parseTerritory(string line){
    vector<string> result = split(line, ',');
    if (result.size() >= 5){
        // if the territory already exists
        if (find(territoriesData.names.begin(), territoriesData.names.end(), result[0]) != territoriesData.names.end()){
            error += 1;
            cout << result[0] << " territory already exists!" << endl;
        }
        // find continent
        if (find(continentsData.names.begin(), continentsData.names.end(), result[3]) == continentsData.names.end()) {
            error += 1;
            cout << result[3] << " continent does not exist!" << endl;
        }
        // store the data in the territories data container
        territoriesData.names.push_back(result[0]);
        territoriesData.continentId.push_back(result[3]);

        // borders
        vector<string> temp;
        temp.push_back(result[0]);
        for(int i = 4; i < result.size(); i++){
            temp.push_back(result[i]);
        }
        bordersData.adjacent.push_back(temp);
        return 1;
    }
    return 0;
}

void ConquestFileReader::convertTerritoryToInt(){
    for(int i = 0; i < bordersData.adjacent.size(); i++){
        for(int j = 1;j < bordersData.adjacent[i].size(); j++){
            string id = to_string(getTerritoryId(bordersData.adjacent[i][j]));
            bordersData.adjacent[i][j] = id;
        }
    }
}

int ConquestFileReader::getTerritoryId(const string &name){
    auto it = find(territoriesData.names.begin(), territoriesData.names.end(), name);
    if (it != territoriesData.names.end()) {
        return (it - territoriesData.names.begin()) + 1;
    }
    return 0;
}

void ConquestFileReader::showResult(){
    for(int i = 0; i < continentsData.names.size(); i++){
        cout << continentsData.names[i] << " ";
    }
    cout << "\n\n";

    for(int i = 0; i < territoriesData.names.size(); i++){
        cout << territoriesData.names[i] << " - " << territoriesData.continentId[i] << endl;
    }

    cout << "\n";

    for(int i = 0; i < bordersData.adjacent.size(); i++){
        for(int j = 0; j < bordersData.adjacent[i].size(); j++){
            cout << bordersData.adjacent[i][j] << " - ";
        }
        cout << "\n";
    }
}

vector<string> ConquestFileReader::getContinentsData(int id){
    if (id == 0){
        return continentsData.names;
    }else{
        return continentsData.armyNums;
    }
}

vector<string> ConquestFileReader::getTerritoriesData(int id){
    if (id == 0){
        return territoriesData.names;
    }else{
        return territoriesData.continentId;
    }
}

vector<vector<string>> ConquestFileReader::getBordersData(){
    return bordersData.adjacent;
}


//**************** ConquestFileReaderAdapter ****************

ConquestFileReaderAdapter::ConquestFileReaderAdapter(ConquestFileReader *conquestLoader) : MapLoader(conquestLoader->getPath()){
    this->conquestLoader = conquestLoader;
}

ConquestFileReaderAdapter::ConquestFileReaderAdapter(const ConquestFileReaderAdapter &conquestLoaderAdapter) : MapLoader(conquestLoaderAdapter){
    delete this->conquestLoader;
    this->conquestLoader = conquestLoaderAdapter.conquestLoader;
}

ConquestFileReaderAdapter& ConquestFileReaderAdapter::operator=(const ConquestFileReaderAdapter &conquestReaderAdapter){
    if (this != &conquestReaderAdapter){
        delete this->conquestLoader;
        this->conquestLoader = conquestReaderAdapter.conquestLoader;
    }
    return *this;
}

ConquestFileReaderAdapter::~ConquestFileReaderAdapter(){
    delete this->conquestLoader;
    this->conquestLoader = nullptr;
}

ostream& operator<<(ostream& out, const ConquestFileReaderAdapter &conquestLoaderAdapter){
    out << conquestLoaderAdapter.conquestLoader;
    return out;
}

bool ConquestFileReaderAdapter::parse(){
    return conquestLoader->parse();
}

Map* ConquestFileReaderAdapter::createMap(){
    Map *map = new Map(); // new Map
    // add continents to the Map
    for (int i = 0; i < conquestLoader->getContinentsData(0).size(); i++){
        Continent *continent = new Continent(conquestLoader->getContinentsData(0)[i], stoi(conquestLoader->getContinentsData(1)[i]));
        map->addContinent(continent);
    }
    
    // add territories to the Map
    for (int i = 0; i < conquestLoader->getTerritoriesData(0).size(); i++){
        Territory *country = new Territory(conquestLoader->getTerritoriesData(0)[i], conquestLoader->getTerritoriesData(1)[i]);
        map->addTerritory(country);
        // add territories to the continent
        int contId = 0;
        auto it = find(conquestLoader->getContinentsData(0).begin(), conquestLoader->getContinentsData(0).end(), conquestLoader->getTerritoriesData(1)[i]);
        if (it != conquestLoader->getContinentsData(0).end()){
            contId = it - conquestLoader->getContinentsData(0).begin();
        }
        map->addTerritoryToContinent(country, contId);
    } 
    
    // add borders
    for(int i = 0; i < conquestLoader->getBordersData().size(); i++){
        for(int j = 1; conquestLoader->getBordersData()[i].size() > 1 && j < conquestLoader->getBordersData()[i].size(); j++){
             map->addBorderIndex(i, stoi(conquestLoader->getBordersData()[i][j]) - 1);
            }
        }

    return map;
}