#include "../include/GameEngine.h"
#include <iostream>
#include <ctime>
#include <algorithm>
#include <random>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <cmath>
#include <typeinfo> 

using namespace std;


// main driver
int main(){
    int numberOfPlayers = 0;
    vector<Player*> tempPlayers;
    MapLoader* maploader;
    Map* map;
    GameEngine* gameEngine = new GameEngine(numberOfPlayers, tempPlayers, maploader, map);

    StatsObserver* statsObserver = new StatsObserver(gameEngine);
    PhaseObserver* phaseObserver = new PhaseObserver(gameEngine);

    string phaseToggle; // Set phase observer on/off
    do {
        cout << "Turn off phase observer? (Y/N)" << endl;
		cin >> phaseToggle;
	} while (phaseToggle != "Y" && phaseToggle != "N");
    if (phaseToggle == "Y") {
        delete phaseObserver;
        phaseObserver = nullptr;
    }

    string statsToggle; // Set stats observer on/off
    do {
        cout << "Turn off game stats observer? (Y/N)" << endl;
		cin >> statsToggle;
	} while (statsToggle != "Y" && statsToggle != "N");
    if (statsToggle == "Y") {
        delete statsObserver;
        statsObserver = nullptr;
    }

    cout << "Map BEFORE user chooses: " << gameEngine->map << endl;
    map = gameEngine->chooseMap(); // choose map to start the game
    cout << "Setting map..." << endl;
    gameEngine->setMap(map); // set the new map from the maploader
    cout << "Map AFTER user chooses: " << gameEngine->map << endl;

    cout << "Number of player before user chooses: " << gameEngine->numberOfPlayers << endl;
    gameEngine->setPlayerNum(); // let user choose number of players
    cout << "Number of player after user chooses: " << gameEngine->numberOfPlayers << endl;

    // above code is the driver for game start - Part 1

    // below code is for gameplay and maingameloop - Part 3
    int playerNum = gameEngine->numberOfPlayers;

    cout << "Creating the players and required items for the game: " << endl;

    // objects for players
    vector<Territory*> defaultTerritories; // players have no territories at first
    Hand* defaultHand = new Hand(); // to make default empty hand
    vector<Order*> defaultOrders; // default set of battle orders
    vector<Card*> defaultCards; // some cards
    Deck* defaultDeck = new Deck(); // default deck of cards

    gameEngine->deck = defaultDeck; // set the default deck to the new initialized one

    // create players
    vector<Player*> players;
    for(int i = 0; i < playerNum; i++){
        Player *player = new Player(defaultTerritories, defaultHand, defaultOrders, i);
        players.push_back(player);
        cout << "Player " << i + 1 << " id: " << player->getPlayerID() << "\n";
    }

    gameEngine->players = players;

    cout << "Players have been created" << endl;
    cout << "GameEngine player size " << gameEngine->players.size() << endl;

    // create GameEngine
    cout << "\nCreating game" << "\n";
    Startup *startUp = new Startup(&players, map);
    cout << "startup phase completed" << "\n\n";

    for(int i = 0; i < playerNum; i++){
        cout << "Player " << i + 1 << " has " << players[i]->getReinforcementPool() <<  " armies" << endl;
    }

    if (statsObserver != nullptr) {
        gameEngine->Notify(statsObserver);
    }

    if (phaseObserver != nullptr) {
        gameEngine->mainGameLoop(phaseObserver);
    }
    else {
        gameEngine->mainGameLoop(nullptr);
    }

    // free memory and dangling ptr
    delete startUp;
    delete gameEngine;
    delete defaultHand;
    delete defaultDeck;

    startUp = NULL;
    gameEngine = NULL;
    defaultHand = NULL;
    defaultDeck = NULL;

    if (phaseObserver != nullptr) {
        delete phaseObserver;
        phaseObserver = nullptr;
    }
    if (statsObserver != nullptr) {
        delete statsObserver;
        statsObserver = nullptr;
    }

    return 0;
}

// default constructor auto generated
GameEngine::GameEngine() {}

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
        cout << "Which file do you want to use as the map?\n";
        string filePath;
        cin >> filePath;
        // if file name contains Conquest_
        if (filePath.find("Conquest_") != string::npos) {
            // use the adapter to read conquest maps
            ConquestFileReader *conquestLoader = new ConquestFileReader(filePath);
            ConquestFileReaderAdapter *adapter = new ConquestFileReaderAdapter(conquestLoader);
            validMap = adapter->parse();
            cout << "Creating map..." << endl;
            map = adapter->createMap();
            cout << "Confirming Conquest map..." << endl;
            delete adapter;
            adapter = nullptr;
        }
        else {
            MapLoader* mapL = new MapLoader(filePath); // load the file
            validMap = mapL->parse(); // check if it is a valid map
            map = mapL->createMap(); // get the map
            // delete pointer and dangling pointer
            delete mapL;
            mapL = NULL;
        }
    }
    cout << map << endl;
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
        cout << "How many players do you want in the game (2-5 players)?\n";
		cin >> tempnumberOfPlayers;
	} while (tempnumberOfPlayers < 2 || tempnumberOfPlayers > 5);

    this->numberOfPlayers = tempnumberOfPlayers;
}

void GameEngine::mainGameLoop(PhaseObserver* phaseObserver) {
// This loop shall continue until only one of the players owns all the territories in the map, at which point a winner is
// announced and the game ends. The main game loop also checks for any player that does not control at least one
// territory; if so, the player is removed from the game.
int round = 0;
string gameEnd;
    // this is to test and simulate rounds of only reinforcement
    
    do {
        cout << endl << "Round: " << to_string(round + 1) << endl;
        cout << "End game? (Y/N)" << endl;
		cin >> gameEnd;
        if (gameEnd == "Y") {
            break;
        }
        round++;
        if (phaseObserver != nullptr) {
            phaseObserver->setPhase("Reinforcement Phase");
            this->reinforcementPhase(phaseObserver);
            phaseObserver->setPhase("Orders Issuing Phase");
            this->issueOrdersPhase(phaseObserver);
            phaseObserver->setPhase("Order Execution Phase");
            this->executeOrdersPhase(phaseObserver);
        }
        else {
            this->reinforcementPhase(nullptr);
            this->issueOrdersPhase(nullptr);
            this->executeOrdersPhase(nullptr);
        }
	} while (gameEnd != "Y");
}

void GameEngine::reinforcementPhase(PhaseObserver* phaseObserver) {
    int numOfArmies = 0;
    vector<Player*>::iterator it;
        
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

        // add new army number to the user's pool
        int totalArmySize = (*it)->getReinforcementPool() + numOfArmies;
        (*it)->setReinforcementPool(totalArmySize);

        if (phaseObserver != nullptr) {
            phaseObserver->setPlayer(*it);
            phaseObserver->setInfo("Player " + to_string((*it)->getPlayerID() + 1) + " will receive " + to_string(numOfArmies) + " armies.\n"
            + "Player " + to_string((*it)->getPlayerID() + 1)+ " has " + to_string((*it)->getReinforcementPool()) + " armies.");
            Notify(phaseObserver);
        }
    }
}

/* player determines territories to attack (listed in toAttack) and deploys orders to own territories (listed in toDefend)
player can deploy if it still has armies to deploy before continuing to other orders, can issue advance orders and play a
card from their hand
*/
void GameEngine::issueOrdersPhase(PhaseObserver* phaseObserver) {
    // create list to defned and attack
    for (Player* p: players)
    {
        p->getTerritories();
    }
    vector<Player*> active = players;


        for (size_t i=0; i<active.size(); i++)
        {
            active[i]-> issueOrder(this, phaseObserver);       
        }
}

void GameEngine::executeOrdersPhase(PhaseObserver* phaseObserver) {
    vector<Player*>::iterator it;
    vector<Order*>::iterator iter;
    vector<Order*> playerOrders;
    Deploy* deploy;
    for(it = players.begin(); it != players.end(); it++){   //iterating through list of players
        playerOrders = (*it)->getPlayerOrders();  //accessing each player's orders
        cout << "Executing Player " << (*it)->getPlayerID() + 1 << "'s orders..." << endl;
        for(iter = playerOrders.begin(); iter != playerOrders.end(); iter++){   //iterating through each player's list of orders
            cout << "Found " << (*iter)->getName() << " Deploy order." << endl;            
            cout << "Is it equal to " << typeid(Deploy).name() << " order?" << endl;
            if ((*iter)->getName() != typeid(Deploy).name()){   //skips iteration if not deploy
                continue;
            }
            else {
            cout << "Executing " << typeid(*iter).name() << " Deploy order..." << endl;
            (*iter)->execute();
            iter = playerOrders.erase(iter);
            }
        }
        for(iter = playerOrders.begin(); iter != playerOrders.end(); iter++){   //iterating through each player's list of orders
            cout << "Found " << typeid(*iter).name() << " Airlift order." << endl;     
            cout << "Is it equal to " << typeid(Airlift).name() << " order?" << endl;
            if ((*iter)->getName() != typeid(Airlift).name()){   //skips iteration if not airlift
                continue;
            }
            cout << "Executing " << typeid(*iter).name() << " Airlift order..." << endl;
            (*iter)->execute();
            iter = playerOrders.erase(iter);
        } 
        for(iter = playerOrders.begin(); iter != playerOrders.end(); iter++){   //iterating through each player's list of orders
            cout << "Found " << typeid(*iter).name() << " Blockade order." << endl;
            cout << "Is it equal to " << typeid(Blockade).name() << " order?" << endl;
            if ((*iter)->getName() != typeid(Blockade).name()){   //skips iteration if not blockade
                continue;
            }
            cout << "Executing " << typeid(*iter).name() << " Blockade order..." << endl;
            (*iter)->execute();
            iter = playerOrders.erase(iter);
        }
        for(iter = playerOrders.begin(); iter != playerOrders.end(); iter++){   //iterating through each player's list of orders
            cout << "Found " << typeid(*iter).name() << " Other order." << endl;
            cout << "Executing " << typeid(*iter).name() << " Other order..." << endl;
            (*iter)->execute();     //executes the rest of the order types
            iter = playerOrders.erase(iter);
        }
    }
}
  
// constructor with no parameter
Startup::Startup() {}

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
    vector<int> randTerritoryId;

    /*
    for(int i = 0; i < randTerritoryId.size(); i++) {
        cout << to_string(randTerritoryId[i]) << endl;
    }*/

    // assign all territories to each player randomly
    while(randTerritoryId.size() < size){
        for(int i = 0; i < playerNum; i ++){
            srand(time(NULL)); // set seed a runtime value
            int temp = rand() % size;
            // if num exists, repeat
            while(find(randTerritoryId.begin(), randTerritoryId.end(), temp) != randTerritoryId.end()){
                temp = rand() % size;
            }
            randTerritoryId.push_back(temp); // push it to the vector
            players->at(i)->addTerritory(map->getTerritories()[temp]); // give player the territory
            cout << "Player " + to_string(i + 1) + " gets territory " + to_string(temp) << "\n";
            // break the loop if these's no more territory
            if (randTerritoryId.size() >= size){
                break;
            }
        }
    }

    // give player all the orders and armies
    for(int i = 0; i < playerNum; i++){
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
        players->at(i)->setReinforcementPool(initialArmyNum); // set player total army
    }
    started = true; // the game starts
}

