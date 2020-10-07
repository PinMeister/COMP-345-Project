#pragma once

#include <iostream>
#include <string>

using namespace std;

// Load a .map file and create a Map obj
class MapLoader{
    public:
        MapLoader(string path); // constructor
        MapLoader(const MapLoader &mapLoader); // copy constructor
        ~MapLoader(); // destructor
        bool parse(); // parse the .map file
        int createMap(); // create a Map obj
    private:
        string mapPath; // path to the .map file
        int error;
        vector<string> split(const string &line, char delim); // split string
        bool parseContinent(string line); // parse continents block in the .map file
        bool parseCountry(string line); // parse countries block in the .map file
        bool parseBorder(string line); // parse borders block in the .map file
        bool isDigit(const string &str); // check if a string is a number
};
