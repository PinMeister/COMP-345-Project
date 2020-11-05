#pragma once

#include "../include/Player.h"
#include "../include/Map.h"
#include <vector>
#include <iostream>

using namespace std;

class GameEngine;

class GameEngine {
//private attributes for GameEngine class
private:
    Player player*;
    Map map*;
};
