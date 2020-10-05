#pragma once

#include <iostream>
#include <string>

class MapLoader{
    public:
        string mapPath;
        MapLoader(string path);
        ~MapLoader();
        int parse();
        int createMap();
    private:
        vector<string> split(const string &line, char delim);
        int parseContinent(string line);
        int parseCountry(string line);
        int parseBorder(string line);
};
