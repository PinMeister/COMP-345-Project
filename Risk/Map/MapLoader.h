#pragma once

#include <iostream>
#include <string>

class MapLoader{
    public:
        MapLoader(string path);
        MapLoader(const MapLoader &mapLoader);
        ~MapLoader();
        int parse();
        int createMap();
    private:
        string mapPath;
        vector<string> split(const string &line, char delim);
        int parseContinent(string line);
        int parseCountry(string line);
        int parseBorder(string line);
};
