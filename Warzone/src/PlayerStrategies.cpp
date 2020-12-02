#include "../include/PlayerStrategies.h"
#include "../include/GameEngine.h"
#include "../include/GameObservers.h"

#include <iostream>
#include <ctime>
#include <algorithm>
#include <random>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <cmath>

using namespace std;

PlayerStrategy::PlayerStrategy() : player(nullptr) {}

PlayerStrategy::PlayerStrategy(Player* player) : player(player) {}

PlayerStrategy::PlayerStrategy(const PlayerStrategy &copy)
{
    this->player = copy.player;
}

PlayerStrategy::~PlayerStrategy() { }

// output stream
ostream& operator<<(ostream& out, const PlayerStrategy& output)
{
    out << "player strategy"<<endl;
    return out;
}

void PlayerStrategy::setPlayer(Player* player)
{
    this->player = player;
}

// assignment operator
PlayerStrategy& PlayerStrategy::operator=(const PlayerStrategy& strat)
{
    player = strat.player;
    return *this;
}

// TO DO: Repurpose issueOrder, toAttack and toDefend to conform to each strategy

// constructor
HumanPlayerStrategy::HumanPlayerStrategy(Player* player) : PlayerStrategy(player) { }

// copy constructor
HumanPlayerStrategy::HumanPlayerStrategy(const HumanPlayerStrategy &copy) : PlayerStrategy(copy) { }

// destructor
HumanPlayerStrategy::~HumanPlayerStrategy() {}

// assignment operator
HumanPlayerStrategy& HumanPlayerStrategy::operator=(const HumanPlayerStrategy& strat)
{
    PlayerStrategy::operator=(strat);
		return *this;
}

// stream output
ostream& operator<<(ostream& out, const HumanPlayerStrategy& output)
{
    out << "Human player strategy"<<endl;
    return out;
}

void HumanPlayerStrategy::issueOrder(GameEngine *gameEngine, PhaseObserver *phaseObserver) {

}

vector<Territory*> HumanPlayerStrategy::toDefend(PhaseObserver *phaseObserver) {

}

vector<Territory*> HumanPlayerStrategy::toAttack(PhaseObserver *phaseObserver) {

}

// NOTE: Only issueOrder is listed here since toAttack and toDefend are called within this
// function by default (with the way it is currently set up in Player.cpp)
void HumanPlayerStrategy::execute(GameEngine *gameEngine, PhaseObserver *phaseObserver) {
    if (phaseObserver != nullptr) {
      phaseObserver->setPlayer(player);
      phaseObserver->setInfo("execute Order NeutralPlayerStrategy");
    }
    player->issueOrder(gameEngine, phaseObserver);
  	gameEngine->Notify(phaseObserver);
}


// AggressivePlayerStrategy (reinforce strongest country, always attack with it until it can't anymore,
// fortifies in order to maximize aggregation of forces in one country)

// constructor
AggressivePlayerStrategy::AggressivePlayerStrategy(Player* player) : PlayerStrategy(player) { }

// copy constructor
AggressivePlayerStrategy::AggressivePlayerStrategy(const AggressivePlayerStrategy &copy) : PlayerStrategy(copy) { }

// stream output
ostream& operator<<(ostream& out, const AggressivePlayerStrategy& output)
{
    out << "Aggressive player strategy"<<endl;
    return out;
}

// destructor
AggressivePlayerStrategy::~AggressivePlayerStrategy() {}

// assignment operator
AggressivePlayerStrategy& AggressivePlayerStrategy::operator=(const AggressivePlayerStrategy& strat)
{
    PlayerStrategy::operator=(strat);
		return *this;
}


void AggressivePlayerStrategy::issueOrder(GameEngine *gameEngine, PhaseObserver *phaseObserver)
{
    vector<Territory*> controlled = player->getTerritories(); // territories controlled by player

	if (phaseObserver != nullptr) {
		phaseObserver->setPlayer(this->player);
		phaseObserver->setInfo("");
	}

    // gets territories to defend and attack of player
    this->toDefendTerritory = this->toDefend(phaseObserver);
    toAttackTerritory = this->toAttack(phaseObserver);

    int canDeploy = player->getReinforcementPool(); // get player's army pool

	cout << "Player " + to_string(player->getPlayerID() + 1) + " currently has " + to_string(canDeploy) + " armies." << endl;

    // 1. while have armies, deploy them until none or stop
    while (canDeploy > 0)
    {
        if (toDefendTerritory.size() > 0)
        {
            for (int i = 0; i < toDefendTerritory.size(); i++)
            {
                if (canDeploy > 0)
                {
                    srand(time(NULL));                       // different random outputs everytime it's run
                    int toDeploy = rand() % canDeploy + 1; // randomly choose a number from 0 to how many you can deploy max
                    canDeploy -= toDeploy;                   // subtract deploying armies from total pool
                    cout << "Deploying " << toDeploy << " armies to " << toDefendTerritory[i]->getName() + "."<< endl;
					if (phaseObserver != nullptr) {
						phaseObserver->setInfo(phaseObserver->getInfo() + "Deploying " + to_string(toDeploy) + " armies to " + toDefendTerritory[i]->getName() + ".\n");
					}
                    // TODO create deploy order issue
					Deploy* deploy = new Deploy(player, toDeploy,toDefendTerritory[i]);
					player->getPlayerOrders().push_back(deploy);
					deploy->execute();
                    continue;
                }
                else
                {
                    cout << " No more armies to deploy" << endl;
                    break;
                }
            }
        }
        else
        {
            cout << " You don't have territories to defend." << endl;
            break;
        }
    }
	// 2. advanced orders
		vector<Territory*> allied_neighbours; // neighbouring territories controlled by player
		vector<Territory*> enemy_neighbours; // neighbouring territories hostile to player


		int decision = rand() % 100;  // take a random number from 0 to 100
			if (decision % 2 == 0  || toDefendTerritory.size() < 2) // if even, attack
			{
				cout << "Player " << player->getPlayerID() + 1 <<  " chooses to attack" << endl;
				int index = rand() % toAttackTerritory.size();
				auto all_neighbours = toAttackTerritory[index]->getNeighbours(); // get neighbours of enemy territory
				cout << "Chosen enemy to attack: " << toAttackTerritory[index]->getName() << endl;
				if (phaseObserver != nullptr) {
						phaseObserver->setInfo(phaseObserver->getInfo() + "Attempting to attack " + toAttackTerritory[index]->getName() + ".\n"); }
				cout << "\nEnemies's neighbours: ";
				for (auto n : all_neighbours) {cout << n->getName() << "   ";}
				cout << "\nYour Enemies: " ;
				auto all_hostile = this->player->get_neighbour_territories(this->player); // get unfriendly
				for (auto n : all_hostile) {cout << n->getName() << "   ";}
				cout << "\n" ;
				cout << "\n" ;
				for (Territory* neighbour : all_neighbours) {
					auto result = find(toDefendTerritory.begin(), toDefendTerritory.end(), neighbour);
            		if (result != toDefendTerritory.end()) // vector contains the element (get own territory close to hostile territory)
           			{
						cout << "Player: "<< player->getPlayerID()<< " chooses to deploy armies from: " << result[0]->getName() <<" to attack " << toAttackTerritory[index]->getName()<<endl;
						if (result[0]->getArmyNum() > 0) // if own territory has army  (TODO remove the equal later on for check)
						{// move random amount of army up to max number in that territory to toAttack Territory
						// pop toAttack territory
						cout << "Allied territory has armies to attack: " << result[0]->getArmyNum() << endl;
						int attackNum = rand() % result[0]->getArmyNum() +1;
						cout << "To deploy " << attackNum << " armies from: " << result[0]->getName() << " to attack: " <<toAttackTerritory[index]->getName() << endl;
						Advance* advanceAtk = new Advance(this->player, result[0], toAttackTerritory[index], attackNum);
						player->getPlayerOrders().push_back(advanceAtk);
						cout << "Attack order added" << endl;
						if (phaseObserver != nullptr) {
							phaseObserver->setInfo(phaseObserver->getInfo() + "Issuing attack from " + result[0]->getName() + " to " + toAttackTerritory[index]->getName() + ".\n"); }
						break;
						}
						else  // if you don't have armies, redundant for now but will be implemented later
						{ // test to see if it will break
							if (phaseObserver != nullptr) {
								phaseObserver->setInfo(phaseObserver->getInfo() + "No armies available to attack " + toAttackTerritory[index]->getName() + ".\n"); }
							cout << "Don't have armies in " << result[0]->getName() << " to deploy to " << toAttackTerritory[index]->getName() << endl;
							toDefendTerritory.erase(find(toDefendTerritory.begin(), toDefendTerritory.end(), result[0])); // pop from the defend list
							continue;
						}
            		}
            		else  // vector does not contain element
            		{
						cout <<"You don't own: " << neighbour->getName()<< endl;
						if (phaseObserver != nullptr) {
							phaseObserver->setInfo(phaseObserver->getInfo() + "Unable to attack from " + neighbour->getName() + ".\n"); }
               			continue;
            		}
				}
			}
			else // if odd, defend

			{
				cout << "Player: "<< player->getPlayerID()<<  " chooses to defend" << endl;
				int index = rand() % toDefendTerritory.size();
				auto all_neighbours = toDefendTerritory[index]->getNeighbours(); // get neighbours of this territory
				cout << "Chosen territory to defend: " << toDefendTerritory[index]->getName() << endl;

				auto all_friendly = this->player->get_friendly_neighbour(this->player); // get all allied neighbours of player
				cout << "Your Allied territories:" << endl;
				for (auto n : all_friendly) {cout << n->getName() << "   ";}
				cout << "\n" ;

				for (Territory* neighbour : all_neighbours) {
					auto result = find(controlled.begin(), controlled.end(), neighbour);
            		if (result != controlled.end()) // vector contains the element
           			{
						cout << "Player: "<< player->getPlayerID()<< " chooses to deploy armies from: " << result[0]->getName()<< " to defend " << toDefendTerritory[index]->getName() << endl;
						if (result[0]->getArmyNum() > 0) // TODO remove equal later when execution
						{// move random amount of army up to max number in that territory to toDefend Territory
						// pop toDefend territory
						cout << "Allied territory has armies to move: " << result[0]->getArmyNum() << endl;
						int moveNum = rand() % result[0]->getArmyNum() +1;
						cout << "To deploy " << moveNum << " armies from: " << result[0]->getName() << " to defend: " <<toDefendTerritory[index]->getName() << endl;
						Advance* advanceDef = new Advance(this->player, result[0], toDefendTerritory[index], moveNum);
						player->getPlayerOrders().push_back(advanceDef);
						cout << "Defend order added" << endl;
						break;
						}
						else // if don't have armies in that area (redundant for now but will be useful later)
						{ // test to see if it'll break
							cout << "Don't have armies in " << result[0]->getName() << " to deploy to " << toDefendTerritory[index]->getName() << endl;
							toDefendTerritory.erase(find(toDefendTerritory.begin(), toDefendTerritory.end(), result[0])); // pop from the defend list
							continue;
						}
            		}
            		else  // vector does not contain element
            		{
						cout <<"You don't control " << neighbour->getName() <<endl;
               			continue;
            		}
					cout << "\nDefending Ended" << endl;
				}
			}


	// 3. use card
	cout << "Choose a card from your hand to use (if you have one): " << endl;
	Deck* deck = new Deck();

	// if player has cards, they'll play one card at random
	if (this->player->getHand()->getNumberHandCards() > 0)
	{
	cout << "Player " << player->getPlayerID() << " has cards:"<< endl;
	for (int i = 0; i < player->getHand()->getNumberHandCards(); i++)
	{
		cout << player->getHand()->getCards()[i]->getCardType() << "   ";
	}
	cout << "\n";
    auto player_orders = player->getPlayerOrders();
	this->player->getHand()->getCards()[rand() % player->getHand()->getNumberHandCards()]->play(player_orders, *deck);
	cout << " ";
	}
	else {
		cout << "You don't have cards to play!"<< endl;
	}

	gameEngine->Notify(phaseObserver);

}

// to fortify the territories with the most army (to deploy to)
vector<Territory*> AggressivePlayerStrategy::toDefend(PhaseObserver *phaseObserver) {
	vector<Territory*> controlled = player->getTerritories(); // territories controlled by player

	// show territories controlled by player
	if (controlled.size() > 0)
	{
        // sort all controlled territories starting with the territories with the most armies in front
        stable_sort(controlled.begin(), controlled.end(), Territory::moreArmiesDeployed);
		cout << "Player " << player->getPlayerID() + 1 << "'s currently controlled Territories and armies:"<< endl;
		for (int i=0; i< controlled.size(); i++)
		{
			cout << " (" << i << ") "  + controlled[i]->getName()  + "   " << controlled[i]->getArmyNum() << endl;
            toDefendTerritory.push_back(controlled[i]);
		}
        return toDefendTerritory;
	}
	else
	{
		cout << " You currently don't control any territories. " << endl;
		return toDefendTerritory;
	}
}

// attacks neighbours
vector<Territory*> AggressivePlayerStrategy::toAttack(PhaseObserver *phaseObserver)
{
	vector<Territory*> controlled = player->getTerritories(); // territories controlled by player
	vector<Territory*> non_allied_neighbours = player->get_neighbour_territories(player); // neighbouring territories not controlled by player

	int deploy_limit = player->getReinforcementPool(); // get reinforcement pool to deploy

    // if no neighbours return empty list, else return sorted enemy neighbour list
	if (non_allied_neighbours.size() > 0)
	{
		//	Show possible territories to attack
		cout << " Territories to attack:"<< endl;
        // sort all enemy territories starting with the territories with the most armies in front
        stable_sort(non_allied_neighbours.begin(), non_allied_neighbours.end(), Territory::moreArmiesDeployed);
		for (int i = 0; i < non_allied_neighbours.size(); i++)
			{
                cout << "  (" << i << ") " + non_allied_neighbours[i]->getName() + "   " << non_allied_neighbours[i]->getArmyNum() << endl;
                toAttackTerritory.push_back(non_allied_neighbours[i]);
            }
		cout << endl;
        return toAttackTerritory;
	}
	else
	{
		cout << "You don't have any neighbours."<< endl;
		return toAttackTerritory;
	}
}


//  ---BenevolentPlayerStrategy (reinforce weakest countries, never attacks, fortifies to move armies to weaker countries) ---
// base constructor
BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* player): PlayerStrategy(player) { }

// copy constructor
BenevolentPlayerStrategy::BenevolentPlayerStrategy(const BenevolentPlayerStrategy &copy) : PlayerStrategy(copy) { }

// assignment operator
BenevolentPlayerStrategy& BenevolentPlayerStrategy::operator=(const BenevolentPlayerStrategy& strat)
{
    PlayerStrategy::operator=(strat);
		return *this;
}

// stream output
ostream& operator<<(ostream& out, const BenevolentPlayerStrategy& output)
{
    out << "Benevolent player strategy"<<endl;
    return out;
}

// destructor
BenevolentPlayerStrategy::~BenevolentPlayerStrategy() {}

// reinforce weakest countries, never attacks, fortifies to move armies to weaker countries
void BenevolentPlayerStrategy::issueOrder(GameEngine *gameEngine, PhaseObserver *phaseObserver)
{
    vector<Territory*> controlled = player->getTerritories(); // territories controlled by player

	if (phaseObserver != nullptr) {
		phaseObserver->setPlayer(this->player);
		phaseObserver->setInfo("");
	}

    // gets territories to defend and attack of player
    this->toDefendTerritory = this->toDefend(phaseObserver);
    toAttackTerritory = this->toAttack(phaseObserver);

    int canDeploy = player->getReinforcementPool(); // get player's army pool

	cout << "Player " + to_string(player->getPlayerID() + 1) + " currently has " + to_string(canDeploy) + " armies." << endl;

    // 1. while have armies, deploy them until none or stop
    while (canDeploy > 0)
    {
        if (toDefendTerritory.size() > 0)
        {
            for (int i = 0; i < toDefendTerritory.size(); i++)
            {
                if (canDeploy > 0)
                {
                    srand(time(NULL));                       // different random outputs everytime it's run
                    int toDeploy = rand() % canDeploy + 1; // randomly choose a number from 0 to how many you can deploy max
                    canDeploy -= toDeploy;                   // subtract deploying armies from total pool
                    cout << "Deploying " << toDeploy << " armies to " << toDefendTerritory[i]->getName() + "."<< endl;
					if (phaseObserver != nullptr) {
						phaseObserver->setInfo(phaseObserver->getInfo() + "Deploying " + to_string(toDeploy) + " armies to " + toDefendTerritory[i]->getName() + ".\n");
					}
                    // TODO create deploy order issue
					Deploy* deploy = new Deploy(player, toDeploy,toDefendTerritory[i]);
					player->getPlayerOrders().push_back(deploy);
					deploy->execute();
                    continue;
                }
                else
                {
                    cout << " No more armies to deploy" << endl;
                    break;
                }
            }
        }
        else
        {
            cout << " You don't have territories to defend." << endl;
            break;
        }
    }
	// 2. advanced orders
		vector<Territory*> allied_neighbours; // neighbouring territories controlled by player
		vector<Territory*> enemy_neighbours; // neighbouring territories hostile to player


		int decision = rand() % 100;  // take a random number from 0 to 100
			if (decision % 2 == 0  || toDefendTerritory.size() < 2) // if even, attack
			{
				cout << "Player " << player->getPlayerID() + 1 <<  " chooses to attack" << endl;
				int index = rand() % toAttackTerritory.size();
				auto all_neighbours = toAttackTerritory[index]->getNeighbours(); // get neighbours of enemy territory
				cout << "Chosen enemy to attack: " << toAttackTerritory[index]->getName() << endl;
				if (phaseObserver != nullptr) {
						phaseObserver->setInfo(phaseObserver->getInfo() + "Attempting to attack " + toAttackTerritory[index]->getName() + ".\n"); }
				cout << "\nEnemies's neighbours: ";
				for (auto n : all_neighbours) {cout << n->getName() << "   ";}
				cout << "\nYour Enemies: " ;
				auto all_hostile = this->player->get_neighbour_territories(this->player); // get unfriendly
				for (auto n : all_hostile) {cout << n->getName() << "   ";}
				cout << "\n" ;
				cout << "\n" ;
				for (Territory* neighbour : all_neighbours) {
					auto result = find(toDefendTerritory.begin(), toDefendTerritory.end(), neighbour);
            		if (result != toDefendTerritory.end()) // vector contains the element (get own territory close to hostile territory)
           			{
						cout << "Player: "<< player->getPlayerID()<< " chooses to deploy armies from: " << result[0]->getName() <<" to attack " << toAttackTerritory[index]->getName()<<endl;
						if (result[0]->getArmyNum() > 0) // if own territory has army  (TODO remove the equal later on for check)
						{// move random amount of army up to max number in that territory to toAttack Territory
						// pop toAttack territory
						cout << "Allied territory has armies to attack: " << result[0]->getArmyNum() << endl;
						int attackNum = rand() % result[0]->getArmyNum() +1;
						cout << "To deploy " << attackNum << " armies from: " << result[0]->getName() << " to attack: " <<toAttackTerritory[index]->getName() << endl;
						Advance* advanceAtk = new Advance(this->player, result[0], toAttackTerritory[index], attackNum);
						player->getPlayerOrders().push_back(advanceAtk);
						cout << "Attack order added" << endl;
						if (phaseObserver != nullptr) {
							phaseObserver->setInfo(phaseObserver->getInfo() + "Issuing attack from " + result[0]->getName() + " to " + toAttackTerritory[index]->getName() + ".\n"); }
						break;
						}
						else  // if you don't have armies, redundant for now but will be implemented later
						{ // test to see if it will break
							if (phaseObserver != nullptr) {
								phaseObserver->setInfo(phaseObserver->getInfo() + "No armies available to attack " + toAttackTerritory[index]->getName() + ".\n"); }
							cout << "Don't have armies in " << result[0]->getName() << " to deploy to " << toAttackTerritory[index]->getName() << endl;
							toDefendTerritory.erase(find(toDefendTerritory.begin(), toDefendTerritory.end(), result[0])); // pop from the defend list
							continue;
						}
            		}
            		else  // vector does not contain element
            		{
						cout <<"You don't own: " << neighbour->getName()<< endl;
						if (phaseObserver != nullptr) {
							phaseObserver->setInfo(phaseObserver->getInfo() + "Unable to attack from " + neighbour->getName() + ".\n"); }
               			continue;
            		}
				}
			}
			else // if odd, defend

			{
				cout << "Player: "<< player->getPlayerID()<<  " chooses to defend" << endl;
				int index = rand() % toDefendTerritory.size();
				auto all_neighbours = toDefendTerritory[index]->getNeighbours(); // get neighbours of this territory
				cout << "Chosen territory to defend: " << toDefendTerritory[index]->getName() << endl;

				auto all_friendly = this->player->get_friendly_neighbour(this->player); // get all allied neighbours of player
				cout << "Your Allied territories:" << endl;
				for (auto n : all_friendly) {cout << n->getName() << "   ";}
				cout << "\n" ;

				for (Territory* neighbour : all_neighbours) {
					auto result = find(controlled.begin(), controlled.end(), neighbour);
            		if (result != controlled.end()) // vector contains the element
           			{
						cout << "Player: "<< player->getPlayerID()<< " chooses to deploy armies from: " << result[0]->getName()<< " to defend " << toDefendTerritory[index]->getName() << endl;
						if (result[0]->getArmyNum() > 0) // TODO remove equal later when execution
						{// move random amount of army up to max number in that territory to toDefend Territory
						// pop toDefend territory
						cout << "Allied territory has armies to move: " << result[0]->getArmyNum() << endl;
						int moveNum = rand() % result[0]->getArmyNum() +1;
						cout << "To deploy " << moveNum << " armies from: " << result[0]->getName() << " to defend: " <<toDefendTerritory[index]->getName() << endl;
						Advance* advanceDef = new Advance(this->player, result[0], toDefendTerritory[index], moveNum);
						player->getPlayerOrders().push_back(advanceDef);
						cout << "Defend order added" << endl;
						break;
						}
						else // if don't have armies in that area (redundant for now but will be useful later)
						{ // test to see if it'll break
							cout << "Don't have armies in " << result[0]->getName() << " to deploy to " << toDefendTerritory[index]->getName() << endl;
							toDefendTerritory.erase(find(toDefendTerritory.begin(), toDefendTerritory.end(), result[0])); // pop from the defend list
							continue;
						}
            		}
            		else  // vector does not contain element
            		{
						cout <<"You don't control " << neighbour->getName() <<endl;
               			continue;
            		}
					cout << "\nDefending Ended" << endl;
				}
			}


	// 3. use card
	cout << "Choose a card from your hand to use (if you have one): " << endl;
	Deck* deck = new Deck();

	// if player has cards, they'll play one card at random
	if (this->player->getHand()->getNumberHandCards() > 0)
	{
	cout << "Player " << player->getPlayerID() << " has cards:"<< endl;
	for (int i = 0; i < player->getHand()->getNumberHandCards(); i++)
	{
		cout << player->getHand()->getCards()[i]->getCardType() << "   ";
	}
	cout << "\n";
    auto player_orders = player->getPlayerOrders();
	this->player->getHand()->getCards()[rand() % player->getHand()->getNumberHandCards()]->play(player_orders, *deck);
	cout << " ";
	}
	else {
		cout << "You don't have cards to play!"<< endl;
	}

	gameEngine->Notify(phaseObserver);
}

// defends least fortified controlled territories
vector<Territory*> BenevolentPlayerStrategy::toDefend(PhaseObserver *phaseObserver) {
    vector<Territory*> controlled = player->getTerritories(); // territories controlled by player

	// show territories controlled by player
	if (controlled.size() > 0)
	{
        // sort all controlled territories starting with the territories with the least armies in front
        stable_sort(controlled.begin(), controlled.end(), Territory::lessArmiesDeployed);
		cout << "Player " << player->getPlayerID() + 1 << "'s currently controlled Territories and armies:"<< endl;
		for (int i=0; i< controlled.size(); i++)
		{
			cout << " (" << i << ") "  + controlled[i]->getName()  + "   " << controlled[i]->getArmyNum() << endl;
            toDefendTerritory.push_back(controlled[i]);
		}
        return toDefendTerritory;
	}
	else
	{
		cout << " You currently don't control any territories. " << endl;
		return toDefendTerritory;
	}
}

// does not attack returns empty territory vector
vector<Territory*> BenevolentPlayerStrategy::toAttack(PhaseObserver *phaseObserver) {
    return toAttackTerritory;
}


NeutralPlayerStrategy::NeutralPlayerStrategy(Player* player): PlayerStrategy(player) { }

// copy constructor
NeutralPlayerStrategy::NeutralPlayerStrategy(const NeutralPlayerStrategy &copy) : PlayerStrategy(copy) { }

// destructor
NeutralPlayerStrategy::~NeutralPlayerStrategy() {}

// assignment operator
NeutralPlayerStrategy& NeutralPlayerStrategy::operator=(const NeutralPlayerStrategy& strat)
{
    PlayerStrategy::operator=(strat);
		return *this;
}

// stream output
ostream& operator<<(ostream& out, const NeutralPlayerStrategy& output)
{
    out << "Neutral player strategy"<<endl;
    return out;
}




// we don't issue anything for this strategy
void NeutralPlayerStrategy::issueOrder(GameEngine *gameEngine, PhaseObserver *phaseObserver) {
  cout << "NeutralPlayerStrategy not allowed to issueOrder" << endl;
}

// return their initial toDefendTerritory no modification
vector<Territory*> NeutralPlayerStrategy::toDefend(PhaseObserver *phaseObserver) {
  cout << "NeutralPlayerStrategy not allowed to toDefend" << endl;
  return toDefendTerritory;
}

// return their initial toAttackTerritory no modification
vector<Territory*> NeutralPlayerStrategy::toAttack(PhaseObserver *phaseObserver) {
  cout << "NeutralPlayerStrategy not allowed to toAttack" << endl;
  return toAttackTerritory;
}

// don't execute anything, update phaseObserver
void NeutralPlayerStrategy::execute(GameEngine *gameEngine, PhaseObserver *phaseObserver) {
  cout << "NeutralPlayerStrategy not allowed to execute" << endl;
  if (phaseObserver != nullptr) {
    phaseObserver->setPlayer(player);
    phaseObserver->setInfo("execute Order NeutralPlayerStrategy");
  }
  // We don't call issueOrder here since the user cannot use any order
  gameEngine->Notify(phaseObserver);
}
