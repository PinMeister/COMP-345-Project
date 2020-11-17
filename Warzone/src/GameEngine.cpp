#include "../include/GameEngine.h"
#include <iostream>
#include <ctime>
#include <algorithm>
#include <random>
#include <stdlib.h>
#include <time.h>
#include <chrono>

using namespace std;

// main driver
int main() {
    int numberOfPlayers = 0;
    vector<Player*> tempPlayers;
    MapLoader* maploader;
    Map* map;
    GameEngine* gameEngine = new GameEngine(numberOfPlayers, tempPlayers, maploader, map);

    cout << "Map BEFORE user chooses: " << gameEngine->map << endl;
    map = gameEngine->chooseMap(); // choose map to start the game
    gameEngine->setMap(map); // set the new map from the maploader
    cout << "Map AFTER user chooses: " << gameEngine->map << endl;

    cout << "Number of player before user chooses: " << gameEngine->numberOfPlayers << endl;
    gameEngine->setPlayerNum(); // let user choose number of players
    cout << "Number of player after user chooses: " << gameEngine->numberOfPlayers << endl;

    cout << "Creating the players and required items for the game: " << endl;
    gameEngine->createPlayers();
    cout << "Players have been created" << endl;

    // free memory and dangling ptr
    delete gameEngine;
    gameEngine = NULL;

	return 0;
}

// default constructor auto generated

// constructor with params 
GameEngine::GameEngine(int numberOfPlayers, vector<Player*> players, MapLoader* maploader, Map* map)  {
       this->numberOfPlayers = numberOfPlayers;
	   this->players = players;
	   this->maploader = maploader;
	   this->map = map;
       this->deck = NULL;
}

// copy constructor
GameEngine::GameEngine(const GameEngine &gameEngine){
       this->numberOfPlayers = gameEngine.numberOfPlayers;
	   this->players = gameEngine.players;
	   this->maploader = gameEngine.maploader;
	   this->map = gameEngine.map;
       this->deck = gameEngine.deck;
}

//assignment operator
GameEngine& GameEngine::operator=(const GameEngine &gameEngine){ 
       this->numberOfPlayers = gameEngine.numberOfPlayers;
	   this->players = gameEngine.players;
	   this->maploader = gameEngine.maploader;
	   this->map = gameEngine.map;
       this->deck =  gameEngine.deck;
	
	return *this;
}

//stream insertion operator for GameEngine
ostream& operator << (ostream &os, const GameEngine &gameEngine){ 
	return os << "\n GameEngine number of player:" << gameEngine.numberOfPlayers 
    << "\n GameEngine player size: " << gameEngine.players.size()  
    << "\n GameEngine maploader: " << gameEngine.maploader  
    << "\n GameEngine map: " << gameEngine.map;
}

// destructor
GameEngine::~GameEngine(){
    numberOfPlayers = 0;
    players.clear(); // empty array
    maploader = NULL;
    map = NULL;
}

// let user choose map
Map* GameEngine::chooseMap() {
    bool validMap = 0;
    Map* map = NULL;
    while(validMap != 1) {
        cout << "Which file do you want to use as the map?\n\n";
        string filePath;
        cin >> filePath;
        MapLoader* mapL = new MapLoader(filePath); // load the file
        validMap = mapL->parse(); // check if it is a valid map
        map = mapL->createMap(); // get the map

        // delete pointer and dangling pointer
        delete mapL;
        mapL = NULL;
    }
    return map;
}

// set the map name
void GameEngine::setMap(Map* map) {
    this->map = map;
}

// retrieve number of player
int GameEngine::getPlayerNum() {
    return numberOfPlayers;
}

// let users choose number of player
void GameEngine::setPlayerNum() {
    int tempnumberOfPlayers = 0;
    do {
        cout << "How many players do you want in the game (2-5 players)?\n\n";
		cin >> tempnumberOfPlayers;
	} while (tempnumberOfPlayers < 2 || tempnumberOfPlayers > 5);

    numberOfPlayers = tempnumberOfPlayers;
}

void GameEngine::createPlayers() {

    vector<Territory*> defaultTerritories; // players have no territories at first
    Hand* defaultHand = new Hand(); // to make default empty hand
    vector<Order*> defaultOrders; // default set of battle orders
    vector<Card*> defaultCards; // some cards
    Deck* defaultDeck = new Deck(); // default deck of cards

    this->deck = defaultDeck; // set the default deck to the new initialized one

    for (int i = 1; i <= this->numberOfPlayers; i++){
        // last parameter i is the playerID
        // create new players
        Player* tempPlayer = new Player(defaultTerritories, defaultHand, defaultOrders, i);
        this->players.push_back(tempPlayer); // add the players into the GameEngine vector

        cout << "Player " << i << " has been created " << endl;

        // free memory and dangling ptr
        delete tempPlayer;
        tempPlayer = NULL;
    }

    // free memory and dangling ptr
    defaultHand = NULL;
    defaultDeck = NULL;

    delete defaultHand;
    delete defaultDeck;

    cout << "End of player creation" << endl;
}

void GameEngine::reinforcementPhase() {}

void GameEngine::issueOrdersPhase() {}

void GameEngine::executeOrdersPhase() {}

Startup::Startup(vector<Player*> *players, Map *map){
    setPlayerNum(players->size());
    startupPhase(players, map);
}

Startup::Startup(const Startup& startup){
    playerNum = startup.playerNum;
}

Startup::~Startup(){

}

void Startup::setPlayerNum(int num){
    playerNum = num;
}

int Startup::getPlayerNum(){
    return playerNum;
}

int Startup::getInitialArmyNum(){
    return ((playerNum * 5) + 10 * (5 - playerNum));
}

void Startup::startupPhase(vector<Player*> *players, Map *map){
    // shuffle player order in vector
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(players->begin(), players->end(), default_random_engine(seed));
    int initialArmyNum = getInitialArmyNum(); // get initial army num

    // assign territories
    int size = map->getTerritories().size(); // get territory num
    vector<int> randomTerritoryId;
    // get random territory id and push to the vector
    for(int i = 0; i < playerNum; i++){
        srand(time(NULL));
        int temp = rand() % size;
        // find a match
        vector<int>::iterator it = find (randomTerritoryId.begin(), randomTerritoryId.end(), temp);
        // if num exists, repeat
        while(it != randomTerritoryId.end()){
            temp = rand() % size;
            it = find (randomTerritoryId.begin(), randomTerritoryId.end(), temp);
        }
        randomTerritoryId.push_back(temp); // push it to the vector
        players->at(i)->addTerritory(map->getTerritories()[temp]); // give player the territory
        map->getTerritories()[temp]->addArmyNum(initialArmyNum); // assign army to territory
    }
}
