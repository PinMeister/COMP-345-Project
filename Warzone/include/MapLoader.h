#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "../include/Map.h"

using namespace std;

// Load a .map file and create a Map obj
class MapLoader{
    public:
        MapLoader(string path); // constructor
        MapLoader(const MapLoader &mapLoader); // copy constructor
        ~MapLoader(); // destructor
        // overloading assignment and string insertion
        MapLoader& operator=(const MapLoader &mapLoader);
        friend ostream& operator<<(ostream& out, const MapLoader &mapLoader);

        bool parse(); // parse the .map file
        Map* createMap(); // create a Map obj
    private:
        // data container for continents
        struct continents {
            vector<string> names;
            vector<string> armyNums;
        } continentsData;
        // data container for countries
        struct countries {
            vector<string> names;
            vector<string> continentId;
            vector<vector<string>> pos;
        } countriesData;
        // data container for borders
        struct borders {
            vector<vector<string>> adjacent;
        } bordersData;

        string mapPath; // path to the .map file
        int error; // number of errors found when parsing and creating the map

        bool parseContinent(string line); // parse continents block in the .map file
        bool parseCountry(string line); // parse countries block in the .map file
        bool parseBorder(string line); // parse borders block in the .map file
        void clearData(); // clear arrays in data containers
};

// Load a conquest map file
class ConquestFileReader{
    public:
        // constructors
        ConquestFileReader(string path);
        ConquestFileReader(const ConquestFileReader &conquestLoader);
        ~ConquestFileReader();
        // overloading assignment and string insertion
        ConquestFileReader& operator=(const ConquestFileReader &conquestLoader);
        friend ostream& operator<<(ostream& out, const ConquestFileReader &conquestLoader);

        bool parse();
        string getPath();
        bool parseContinent(string line); // parse continents block in the .map file
        bool parseTerritory(string line); // parse territories block in the .map file
        void showResult(); // for debug
        void convertTerritoryToInt(); // change territory name to its index in vector
        int getTerritoryId(const string &name); // get territory index in the vector
        vector<string> getContinentsData(int id); // return struct continentsData
        vector<string> getTerritoriesData(int id); // return struct territoriesData
        vector<vector<string>> getBordersData(); // return struct bordersData
    private:
        string mapPath; // path to the .map file
        int error;
        // data container for continents
        struct continents {
            vector<string> names;
            vector<string> armyNums;
        } continentsData;
        // data container for territories
        struct territories {
            vector<string> names;
            vector<string> continentId;
        } territoriesData;
        // data container for borders
        struct borders {
            vector<vector<string> > adjacent;
        } bordersData;
};

// Adapter for loading a conqest map file and create a Map obj
class ConquestFileReaderAdapter : public MapLoader{
    public:
        ConquestFileReaderAdapter(ConquestFileReader *conquestLoader); // construtor
        ConquestFileReaderAdapter(const ConquestFileReaderAdapter &conquestLoaderAdapter); // copy constructor
        ~ConquestFileReaderAdapter(); // destructor
        // overloading assignment and string insertion
        ConquestFileReaderAdapter& operator=(const ConquestFileReaderAdapter &conquestLoaderAdapter);
        friend ostream& operator<<(ostream& out, const ConquestFileReaderAdapter &conquestLoaderAdapter);
        bool parse(); // override MapLoader parse
        Map* createMap(); // override MapLoader createMap
    private:
        ConquestFileReader *conquestLoader;

};

// free functions
vector<string> split(const string &line, char delim);
bool isDigit(const string &str);
