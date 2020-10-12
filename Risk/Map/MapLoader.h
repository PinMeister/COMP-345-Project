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
        // overloading assignment and string insertion
        MapLoader& operator=(const MapLoader &mapLoader);
        friend ostream& operator<<(std::ostream& out, const MapLoader &mapLoader);

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
            vector<vector<string> > pos;
        } countriesData;
        // data container for borders
        struct borders {
            vector<vector<string> > adjacent;
        } bordersData;
        string mapPath; // path to the .map file
        int error; // number of errors found when parsing and creating the map

        vector<string> split(const string &line, char delim); // split string
        bool parseContinent(string line); // parse continents block in the .map file
        bool parseCountry(string line); // parse countries block in the .map file
        bool parseBorder(string line); // parse borders block in the .map file
        bool isDigit(const string &str); // check if a string is a number
        void clearData();
};
