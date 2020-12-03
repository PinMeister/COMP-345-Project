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

PlayerStrategy::PlayerStrategy(Player *player) : player(player) {}

PlayerStrategy::PlayerStrategy(const PlayerStrategy &copy)
{
	this->player = copy.player;
}

PlayerStrategy::~PlayerStrategy() {}

// output stream
ostream &operator<<(ostream &out, const PlayerStrategy &output)
{
	out << "player strategy" << endl;
	return out;
}

void PlayerStrategy::setPlayer(Player *player)
{
	this->player = player;
}

// assignment operator
PlayerStrategy &PlayerStrategy::operator=(const PlayerStrategy &strat)
{
	player = strat.player;
	return *this;
}

// TO DO: Repurpose issueOrder, toAttack and toDefend to conform to each strategy

HumanPlayerStrategy::HumanPlayerStrategy(Player *player) : PlayerStrategy(player) {}

void HumanPlayerStrategy::issueOrder(GameEngine *gameEngine, PhaseObserver *phaseObserver)
{
}

vector<Territory *> HumanPlayerStrategy::toDefend(PhaseObserver *phaseObserver)
{
}

vector<Territory *> HumanPlayerStrategy::toAttack(PhaseObserver *phaseObserver)
{
}

// NOTE: Only issueOrder is listed here since toAttack and toDefend are called within this
// function by default (with the way it is currently set up in Player.cpp)
// void HumanPlayerStrategy::execute(GameEngine *gameEngine, PhaseObserver *phaseObserver) {
//     issueOrder(gameEngine, phaseObserver);
// }

// AggressivePlayerStrategy (reinforce strongest country, always attack with it until it can't anymore,
// fortifies in order to maximize aggregation of forces in one country)

// constructor
AggressivePlayerStrategy::AggressivePlayerStrategy(Player *player) : PlayerStrategy(player) {}

// copy constructor
AggressivePlayerStrategy::AggressivePlayerStrategy(const AggressivePlayerStrategy &copy) : PlayerStrategy(copy) {}

// stream output
ostream &operator<<(ostream &out, const AggressivePlayerStrategy &output)
{
	out << "Aggressive player strategy" << endl;
	return out;
}

// destructor
AggressivePlayerStrategy::~AggressivePlayerStrategy() {}

// assignment operator
AggressivePlayerStrategy &AggressivePlayerStrategy::operator=(const AggressivePlayerStrategy &strat)
{
	PlayerStrategy::operator=(strat);
	return *this;
}

void AggressivePlayerStrategy::issueOrder(GameEngine *gameEngine, PhaseObserver *phaseObserver)
{
	if (phaseObserver != nullptr)
	{
		phaseObserver->setPlayer(this->player);
		phaseObserver->setInfo("");
	}
	// gets territories to defend and attack of player
	vector<Territory *> toDefendTerritory = toDefend(phaseObserver); // ordered from most armed territories
	vector<Territory *> toAttackTerritory = toAttack(phaseObserver);

	int canDeploy = player->getReinforcementPool(); // get player's army pool

	cout << "Player " + to_string(player->getPlayerID() + 1) + " currently has " + to_string(canDeploy) + " armies." << endl;

	// 1. while have armies, deploy them all to the strongest country	
		if (toDefendTerritory.size() > 0)
		{
			if (canDeploy > 0) // if you have reinforcements
			{
				cout << "Deploying " << canDeploy << " armies to " << toDefendTerritory[0]->getName() + "." << endl;
				if (phaseObserver != nullptr)
				{
					phaseObserver->setInfo(phaseObserver->getInfo() + "Deploying " + to_string(canDeploy) + " armies to " + toDefendTerritory[0]->getName() + ".\n");
				}
				// create deploy order issue and execute to deploy
				Deploy *deploy = new Deploy(player, canDeploy, toDefendTerritory[0]);
				player->getPlayerOrders().push_back(deploy);
				deploy->execute(); // placing to the country so the army numbers are updated
				player->setReinforcementPool(0); // set pool to zero since all are deployed
			}
			else
			{
				cout << "No more armies to deploy" << endl;
			}
		}
		else
		{
			cout << "You don't have territories to defend." << endl;
		}
	
	// 2. advanced orders --> fortify strongest country and keep attacking
	cout << "Player " << player->getPlayerID() + 1 << " to issue attacks." << endl;
	auto all_neighbours_enemy = toAttackTerritory[0]->getNeighbours();		   // get neighbours of top territory
	vector<Territory *> allied_neighbours = toDefendTerritory[0]->getAllies(); // neighbouring territories controlled by player

	while (true)
	{
		for (Territory *self : toDefendTerritory)
		{	
			int moveNum = self->getArmyNum(); // get army number in top country
			vector<Territory *> enemy_neighbours = self->getEnemies(); // get enemy neighbours of your top territory
			if (enemy_neighbours.size() > 0)
			{
				for (Territory *enemy : enemy_neighbours)
				{
					if ((moveNum > 0) && (enemy->getOwner() != player) && (Territory::moreArmiesDeployed(self, enemy)))
					{
						srand(time(NULL)); // seed random
						int attackNum = rand() % moveNum + enemy->getArmyNum();
						cout << "Chosen enemy to attack: " << enemy->getName() << endl;
						cout << "Allied territory has armies to attack: " << moveNum << endl;
						if (phaseObserver != nullptr)
						{
							phaseObserver->setInfo(phaseObserver->getInfo() + "Attempting to attack " + enemy->getName() + ".\n");
						}
						auto source = self;
						auto target = enemy;
						cout << "To deploy " << attackNum << " armies from: " << self->getName() << " to attack: " << enemy->getName() << endl;
						player->getPlayerOrders().push_back(new Advance(player, source, target, attackNum));
						moveNum -= attackNum; // subtract from the number of armies available
						if (phaseObserver != nullptr)
						{
							phaseObserver->setInfo(phaseObserver->getInfo() + "Issuing attack from " + self->getName() + " to " + enemy->getName() + ".\n");
						}
					}
					else if (moveNum == 0) // no more to advance
					{
						cout << "No more armies to deploy." << endl;
						break;
					}
				}		
			}
		}
		cout << " No enemies to attack. Attacking orders issue done."<<endl;
	}
	while (true){
	cout << "Player " << player->getPlayerID() + 1 << " issues fortify orders" << endl;
			for (Territory *neighbour : allied_neighbours) // get all neighbours
			{
				int moveNum = neighbour->getArmyNum();
				if ((neighbour->getOwner() == player) && (moveNum > 0))
				{
					int defendNum = rand() % moveNum + 1;
					cout << "To deploy " << defendNum << " armies from: " << neighbour->getName() << " to fortify: " << toDefendTerritory[0]->getName() << endl;
					Advance *advancedfd = new Advance(player, neighbour, toDefendTerritory[0], defendNum);
					player->getPlayerOrders().push_back(advancedfd);
					moveNum -= defendNum;
					if (phaseObserver != nullptr)
						{
							phaseObserver->setInfo(phaseObserver->getInfo() + "Issuing defend from " + neighbour->getName() + " to " + toDefendTerritory[0]->getName() + ".\n");
						}
				}
			}
			cout << "Fortication orders issue done."<<endl;
	}
	int index = rand() % 2 + 1; // choose number between 1 to 2
	if (index == 0) // if even set player strategy to benevolent
	{
		player->setStrategy(new BenevolentPlayerStrategy(player));
	}
	gameEngine->Notify(phaseObserver);
}

// to fortify the territories with the most army (to deploy to)
vector<Territory *> AggressivePlayerStrategy::toDefend(PhaseObserver *phaseObserver)
{
	vector<Territory *> controlled = player->getTerritories(); // territories controlled by player

	// show territories controlled by player
	if (controlled.size() > 0)
	{
		// sort all controlled territories starting with the territories with the most armies in front
		stable_sort(controlled.begin(), controlled.end(), Territory::moreArmiesDeployed);
		cout << "Player " << player->getPlayerID() + 1 << "'s currently controlled Territories and armies:" << endl;
		for (int i = 0; i < controlled.size(); i++)
		{
			cout << " (" << i << ") " + controlled[i]->getName() + "   " << controlled[i]->getArmyNum() << endl;
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
vector<Territory *> AggressivePlayerStrategy::toAttack(PhaseObserver *phaseObserver)
{
	vector<Territory *> controlled = player->getTerritories();							   // territories controlled by player
	vector<Territory *> non_allied_neighbours = player->get_neighbour_territories(player); // neighbouring territories not controlled by player

	int deploy_limit = player->getReinforcementPool(); // get reinforcement pool to deploy

	// if no neighbours return empty list, else return sorted enemy neighbour list
	if (non_allied_neighbours.size() > 0)
	{
		//	Show possible territories to attack
		cout << " Territories to attack:" << endl;
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
		cout << "You don't have any neighbours." << endl;
		return toAttackTerritory;
	}
}

//  ---BenevolentPlayerStrategy (reinforce weakest countries, never attacks, fortifies to move armies to weaker countries) ---
// base constructor
BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player *player) : PlayerStrategy(player) {}

// copy constructor
BenevolentPlayerStrategy::BenevolentPlayerStrategy(const BenevolentPlayerStrategy &copy) : PlayerStrategy(copy) {}

// assignment operator
BenevolentPlayerStrategy &BenevolentPlayerStrategy::operator=(const BenevolentPlayerStrategy &strat)
{
	PlayerStrategy::operator=(strat);
	return *this;
}

// stream output
ostream &operator<<(ostream &out, const BenevolentPlayerStrategy &output)
{
	out << "Benevolent player strategy" << endl;
	return out;
}

// destructor
BenevolentPlayerStrategy::~BenevolentPlayerStrategy() {}

// reinforce weakest countries, never attacks, fortifies to move armies to weaker countries
void BenevolentPlayerStrategy::issueOrder(GameEngine *gameEngine, PhaseObserver *phaseObserver)
{
	if (phaseObserver != nullptr)
	{
		phaseObserver->setPlayer(this->player);
		phaseObserver->setInfo("");
	}
	// gets territories to defend and attack of player
	vector<Territory *> toDefendTerritory = toDefend(phaseObserver); // ordered from least armed territories first
	vector<Territory *> toAttackTerritory = toAttack(phaseObserver); // empty

	int canDeploy = player->getReinforcementPool(); // get player's army pool

	cout << "Player " + to_string(player->getPlayerID() + 1) + " currently has " + to_string(canDeploy) + " armies." << endl;

	// 1. while have armies, deploy them all to the weakest country	
		if (toDefendTerritory.size() > 0)
		{
			if (canDeploy > 0) // if you have reinforcements
			{
				cout << "Deploying " << canDeploy << " armies to " << toDefendTerritory[0]->getName() + "." << endl;
				if (phaseObserver != nullptr)
				{
					phaseObserver->setInfo(phaseObserver->getInfo() + "Deploying " + to_string(canDeploy) + " armies to " + toDefendTerritory[0]->getName() + ".\n");
				}
				// create deploy order issue and execute to deploy
				Deploy *deploy = new Deploy(player, canDeploy, toDefendTerritory[0]);
				player->getPlayerOrders().push_back(deploy);
				deploy->execute(); // placing to the country so the army numbers are updated
				player->setReinforcementPool(0); // set pool to zero since all are deployed
			}
			else
			{
				cout << "No more armies to deploy" << endl;
			}
		}
		else
		{
			cout << "You don't have territories to defend." << endl;
		}
	
	// 2. advanced orders --> fortify weakest countries
	vector<Territory *> allied_neighbours = toDefendTerritory[0]->getAllies(); // neighbouring territories controlled by player
	while (true){
	cout << "Player " << player->getPlayerID() + 1 << " issues fortify orders" << endl;
			for (Territory *neighbour : allied_neighbours) // get all neighbours
			{
				int moveNum = neighbour->getArmyNum();
				if ((neighbour->getOwner() == player) && (moveNum > 0))
				{
					int defendNum = rand() % moveNum + 1;
					cout << "To deploy " << defendNum << " armies from: " << neighbour->getName() << " to fortify: " << toDefendTerritory[0]->getName() << endl;
					Advance *advancedfd = new Advance(player, neighbour, toDefendTerritory[0], defendNum);
					player->getPlayerOrders().push_back(advancedfd);
					moveNum -= defendNum;
					if (phaseObserver != nullptr)
						{
							phaseObserver->setInfo(phaseObserver->getInfo() + "Issuing defend from " + neighbour->getName() + " to " + toDefendTerritory[0]->getName() + ".\n");
						}
				}
			}
			cout << "Fortication orders issue done."<<endl;
	}
	int index = rand() % 2 + 1; // choose number between 1 to 2
	if (index == 0) // if even set player strategy to agressive strategy
	{
		player->setStrategy(new AggressivePlayerStrategy(player));
	}
	gameEngine->Notify(phaseObserver);
}

// defends least fortified controlled territories
vector<Territory *> BenevolentPlayerStrategy::toDefend(PhaseObserver *phaseObserver)
{
	vector<Territory *> controlled = player->getTerritories(); // territories controlled by player

	// show territories controlled by player
	if (controlled.size() > 0)
	{
		// sort all controlled territories starting with the territories with the least armies in front
		stable_sort(controlled.begin(), controlled.end(), Territory::lessArmiesDeployed);
		cout << "Player " << player->getPlayerID() + 1 << "'s currently controlled Territories and armies:" << endl;
		for (int i = 0; i < controlled.size(); i++)
		{
			cout << " (" << i << ") " + controlled[i]->getName() + "   " << controlled[i]->getArmyNum() << endl;
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
vector<Territory *> BenevolentPlayerStrategy::toAttack(PhaseObserver *phaseObserver)
{
	return toAttackTerritory;
}

NeutralPlayerStrategy::NeutralPlayerStrategy(Player *player) : PlayerStrategy(player) {}

// copy constructor
NeutralPlayerStrategy::NeutralPlayerStrategy(const NeutralPlayerStrategy &copy) : PlayerStrategy(copy) {}

void NeutralPlayerStrategy::issueOrder(GameEngine *gameEngine, PhaseObserver *phaseObserver)
{
}

vector<Territory *> NeutralPlayerStrategy::toDefend(PhaseObserver *phaseObserver)
{
}

vector<Territory *> NeutralPlayerStrategy::toAttack(PhaseObserver *phaseObserver)
{
}

// void NeutralPlayerStrategy::execute(GameEngine *gameEngine, PhaseObserver *phaseObserver) {
//     issueOrder(gameEngine, phaseObserver);
// }
