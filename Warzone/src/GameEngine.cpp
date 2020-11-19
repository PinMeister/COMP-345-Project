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

// main driver
// int main() {
//     int numberOfPlayers = 0;
//     vector<Player*> players;
//     MapLoader* maploader;
//     Map* map;
//     GameEngine* gameEngine = new GameEngine(numberOfPlayers, players, maploader, map);

//     cout << "Map BEFORE user chooses: " << gameEngine->map << endl;
//     map = gameEngine->chooseMap(); // choose map to start the game
//     gameEngine->setMap(map); // set the new map from the maploader
//     cout << "Map AFTER user chooses: " << gameEngine->map << endl;

//     cout << "Number of player before user chooses: " << gameEngine->numberOfPlayers << endl;
//     gameEngine->setPlayerNum(); // let user choose number of players
//     cout << "Number of player after user chooses: " << gameEngine->numberOfPlayers << endl;

//     cout << "Creating the players and required items for the game: " << endl;
//     gameEngine->createPlayers();
//     cout << "Players have been created" << endl;

//     // free memory and dangling ptr
//     for (auto p : players) { delete p; } 
//     delete maploader;
//     delete map;
//     delete gameEngine;

//     players.clear();
//     maploader = NULL;   
//     map = NULL;
//     gameEngine = NULL;

// 	return 0;
// }

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
    Hand* defaultHand = new  Hand(); // to make default empty hand
    vector<Order*> defaultOrders; // default set of battle orders
    vector<Card*> defaultCards; // some cards
    Deck* defaultDeck = new Deck(); // default deck of cards

    this->deck = defaultDeck; // set the default deck to the new initialized one

    for (int i = 1; i <= numberOfPlayers; i++){
        // last parameter i is the playerID
        // create new players
        Player* tempPlayer = new Player(defaultTerritories, defaultHand, defaultOrders, i);
        this->players.push_back(tempPlayer); // add the players into the GameEngine vector

        // free memory and dangling ptr
        delete tempPlayer;
        tempPlayer = NULL;
    }

    // free memory and dangling ptr
    for (auto p : defaultTerritories) { delete p; } 
    for (auto p : defaultOrders) { delete p; } 
    for (auto p : defaultCards) { delete p; } 
    delete defaultHand;
    delete defaultDeck;

    defaultTerritories.clear();
    defaultHand = NULL;
    defaultOrders.clear();
    defaultCards.clear();
    defaultDeck = NULL;
}

// TO DO

void GameEngine::mainGameLoop() {
// This loop shall continue until only one of the players owns all the territories in the map, at which point a winner is
// announced and the game ends. The main game loop also checks for any player that does not control at least one
// territory; if so, the player is removed from the game.    
}

// const Player* GameEngine::getCurrentPlayer() {
//     return GetEngine().currentPlayer;
// }

// const Order* GameEngine::getLastOrder(){
//     return GetEngine().lastOrder;
// }

void GameEngine::reinforcementPhase() {
    int numOfArmies = 0;
    vector<Player*>::iterator it;

    for(it = players.begin(); it != players.end(); it++){   //iterating through list of players
        // (# of territories owned divided by 3, rounded down
        numOfArmies = (*it)->getTerritories().size();
        numOfArmies = floor(numOfArmies/3);

        vector<Continent*> mapContinents = map->getContinents(); // get all continents for current map
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

            for (auto p : mapTerritories) { delete p; }
            mapTerritories.clear();
        }

        // minimal number of reinforcement armies per turn for any player is 3. 
        if (numOfArmies < 3) {
            numOfArmies = 3;
        }

        // add new armie number to the user's pool
        int totalArmySize = (*it)->getReinforcementPool() + numOfArmies;
        (*it)->setReinforcementPool(totalArmySize);

        // free memory and dangling ptr
        for (auto p : mapContinents) { delete p; }
        mapContinents.clear();

        for (auto p : playerTerritories) { delete p; }
        playerTerritories.clear();
        
        playerTerritoriesName.clear();
        }
}

/* player determines territories to attack (listed in toAttack) and deploys orders to own territories (listed in toDefend)
player can deploy if it still has armies to deploy before continuing to other orders, can issue advance orders and play a
card from their hand
*/
void GameEngine::issueOrdersPhase() {
    // create list to defned and attack
    for (Player* p: players)
    {
        p->getTerritories();
    }
    //TODO armies available on all territories 

    vector<Player*> active = players;

    // if have active players
    while (!active.empty())
    {
        for (size_t i=0; i<active.size(); i++)
        {
            Order* newOrder;
            active[i]-> issueOrder(newOrder);

            // if no new order, go to next player
            if (newOrder == nullptr)
            {
                active.erase(active.begin()+i);
            }
            // execute order
            else 
            {
                currentPlayer = active[i];
                lastOrder = newOrder;
                active[i]->issueOrder(lastOrder);
            }
        }
    }

}

void GameEngine::executeOrdersPhase() {
    vector<Player*>::iterator it;
    vector<Order*>::iterator iter;
    vector<Order*> playerOrders;
    for(it = players.begin(); it != players.end(); it++){   //iterating through list of players
        playerOrders = (*it)->getPlayerOrders();  //accessing each player's orders
        for(iter = playerOrders.begin(); iter != playerOrders.end(); iter++){   //iterating through each player's list of orders
            if (typeid(*iter) != typeid(Deploy)){   //skips iteration if not deploy
                continue;
            }
            (*iter)->execute();
        }
        for(iter = playerOrders.begin(); iter != playerOrders.end(); iter++){   //iterating through each player's list of orders
            if (typeid(*iter) != typeid(Airlift)){   //skips iteration if not airlift
                continue;
            }
            (*iter)->execute();
        } 
        for(iter = playerOrders.begin(); iter != playerOrders.end(); iter++){   //iterating through each player's list of orders
            if (typeid(*iter) != typeid(Blockade)){   //skips iteration if not blockade
                continue;
            }
            (*iter)->execute();
        }
        for(iter = playerOrders.begin(); iter != playerOrders.end(); iter++){   //iterating through each player's list of orders
            (*iter)->execute();     //executes the rest of the order types
        }
    }
    reinforcementPhase();   //goes back to the reinforcement phase
}

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
