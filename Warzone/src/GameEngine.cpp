#include "../include/GameEngine.h"
#include <iostream>
#include <ctime>
#include <algorithm>
#include <random>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <cmath>

using namespace std;

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

    this->numberOfPlayers = tempnumberOfPlayers;
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
        // Player* tempPlayer = new Player(i);
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

// TO DO

void GameEngine::mainGameLoop() {
// This loop shall continue until only one of the players owns all the territories in the map, at which point a winner is
// announced and the game ends. The main game loop also checks for any player that does not control at least one
// territory; if so, the player is removed from the game.    
}

void GameEngine::reinforcementPhase() {
    int numOfArmies = 0;
    vector<Player*>::iterator it;

    cout << "Gameengine player vector size" << this->players.size() <<  endl;

    for (int a = 0; a<3; a++){

        cout << "Test Round " << a << endl;

    for(it = this->players.begin(); it != this->players.end(); it++){   //iterating through list of players
        // (# of territories owned divided by 3, rounded down
        cout << "Starting to loop through each player" << endl;
        cout << (*it)->getTerritories().size() << endl; 

        numOfArmies = (*it)->getTerritories().size();
        numOfArmies = floor(numOfArmies/3);

        vector<Continent*> mapContinents = this->map->getContinents(); // get all continents for current map
        vector<Territory*> playerTerritories = (*it)->getTerritories(); // get the user's territories
        vector<string> playerTerritoriesName; // get the user's territories name

        // iterate through player's territories and add their name
        for (auto territory : playerTerritories) {
            playerTerritoriesName.push_back(territory->getName());
        }

        // sort the vector for later processing
        sort(playerTerritoriesName.begin(), playerTerritoriesName.end());

        // check for each continent if user owns all territories
        for (auto continent : mapContinents){
            vector<Territory*> mapTerritories = continent->getMembers();
            int n = mapTerritories.size();
            vector<string> continentTerritoriesName;

            // iterate through continent's territories and add their name
            for (auto territory : mapTerritories) {
                continentTerritoriesName.push_back(territory->getName());
            }

            // temp vector for set_difference
            vector<string> v(n); 
            vector<string>::iterator iter, st; 

            // Sort vector to use set_difference
            sort(continentTerritoriesName.begin(), continentTerritoriesName.end()); 

            // compare both vector
            iter = set_difference(continentTerritoriesName.begin(),
                                continentTerritoriesName.end(), 
                                playerTerritoriesName.begin(), 
                                playerTerritoriesName.end(), v.begin());

            for (st = v.begin(); st != iter; ++st) {} // add into st until it's not equal to iter            

            // if the set difference has no element
            // means the player owns the continent
            if ((st - v.begin()) == 0) {
                numOfArmies += continent->getControlBonus();
            }
        }

        // minimal number of reinforcement armies per turn for any player is 3. 
        if (numOfArmies < 3) {
            numOfArmies = 3;
        }

        cout << "Player " << (*it)->getPlayerID() << " will receive " << numOfArmies << " armies" << endl;

        // add new armie number to the user's pool
        int totalArmySize = (*it)->getReinforcementPool() + numOfArmies;
        (*it)->setReinforcementPool(totalArmySize);

        cout << "Player " << (*it)->getPlayerID() << "has " << (*it)->getReinforcementPool() << " armies" << endl;
        }
    }
}

void GameEngine::issueOrdersPhase() {}

void GameEngine::executeOrdersPhase() {}

// constructor with no parameter
Startup::Startup(){
    // nothing
}

// constructor takes in a vector pointer of player pointers and a pointer to map
Startup::Startup(vector<Player*> *players, Map *map){
    setPlayerNum(players->size());
    startupPhase(players, map);
}

// copy constructor
Startup::Startup(const Startup& startup){
    Startup* copy = new Startup();
    copy->playerNum = startup.playerNum;
    copy->setPlayerNum(copy->playerNum);
}

// destructor
Startup::~Startup(){
    //nothing
}

// assignment operator
Startup& Startup::operator=(const Startup &startUp){
    playerNum = startUp.playerNum;
    return *this;
}

// stream insertion operator
ostream& operator<<(ostream& out, const Startup &startUp){
    out << "Player Number: " << startUp.playerNum << "\nGame started: " << startUp.started << "\n";
    return out;
}

// set player num to an int
void Startup::setPlayerNum(int num){
    playerNum = num;
}

// return player num
int Startup::getPlayerNum(){
    return playerNum;
}

// use player num to get initial army num
int Startup::getInitialArmyNum(){
    return ((playerNum * 5) + 10 * (5 - playerNum));
}

// start up the game
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
<<<<<<< HEAD
        srand(time(NULL)); srand(time(NULL)); // set seed a runtime value
=======
        srand(time(NULL)); // set seed a runtime value
>>>>>>> 3f83eef6cb085ae0460eae408b5ced1ca2df9776
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
<<<<<<< HEAD
}
=======
    started = true;
}
>>>>>>> 3f83eef6cb085ae0460eae408b5ced1ca2df9776
