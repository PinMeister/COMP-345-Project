#pragma once

#include <iostream>
#include <string>

using namespace std;

class MapLoader{
    public:
        string mapPath;
        MapLoader(std::string path);
        ~MapLoader();
        string parse();
        vector<string> split(const string &line, char delim);
    private:
};
