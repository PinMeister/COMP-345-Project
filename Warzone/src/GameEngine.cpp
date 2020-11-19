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

// TO DO

void GameEngine::mainGameLoop() {
// This loop shall continue until only one of the players owns all the territories in the map, at which point a winner is
// announced and the game ends. The main game loop also checks for any player that does not control at least one
// territory; if so, the player is removed from the game.    
}

void GameEngine::reinforcementPhase(PhaseObserver* phaseObserver) {
    int numOfArmies = 0;
    vector<Player*>::iterator it;

    // this is to test and simulate rounds of only reinforcement
    for (int a = 0; a<3; a++){

        cout << endl << "Round: " << to_string(a + 1) << endl;

    for(it = this->players.begin(); it != this->players.end(); it++){   //iterating through list of players
        // (# of territories owned divided by 3, rounded down
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

        if (phaseObserver != nullptr) {
            phaseObserver->setPlayer(*it);
            phaseObserver->setInfo("Player " + to_string((*it)->getPlayerID() + 1) + " will receive " + to_string(numOfArmies) + " armies.");
            Notify(phaseObserver);
        }

        // add new army number to the user's pool
        int totalArmySize = (*it)->getReinforcementPool() + numOfArmies;
        (*it)->setReinforcementPool(totalArmySize);

            if (phaseObserver != nullptr) {
                phaseObserver->setInfo("Player " + to_string((*it)->getPlayerID() + 1)+ " has " + to_string((*it)->getReinforcementPool()) + " armies.");
                Notify(phaseObserver);
            }
        }
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
    // while (!active.empty())
    // {
        for (size_t i=0; i<active.size(); i++)
        {
            active[i]-> issueOrder();
            // if no new order, go to next player
            // if (newOrder == nullptr)
            // {
            //     active.erase(active.begin()+i);
            // }
            // // execute order
            // else 
            // {
            //     currentPlayer = active[i];
            //     lastOrder = newOrder;
            //     active[i]->issueOrder();
            // }
        }
    // }

}

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

    cout << "Initial army size for each player " << initialArmyNum << endl;

    // assign territories
    int size = map->getTerritories().size(); // get territory num
    vector<int> randomTerritoryId;
    // get random territory id and push to the vector
    for(int i = 0; i < playerNum; i++){
        srand(time(NULL)); // set seed a runtime value
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
        players->at(i)->setReinforcementPool(initialArmyNum); // set palyer total army
      
        // give player all the orders
        Deploy *depl;
        Advance *adv;
        Bomb *bmb;
        Blockade *blckd;
        Airlift *alt; 
        Negotiate *ngt; 
        vector<Order*> orders;
        orders.push_back(depl);
        orders.push_back(adv);
        orders.push_back(bmb);
        orders.push_back(blckd);
        orders.push_back(alt);
        orders.push_back(ngt); 

        players->at(i)->setOrdersRef(orders);
    }
    started = true;
}
