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

// empty constructor
PlayerStrategy::PlayerStrategy() : player(nullptr) {}

// default constrcutor
PlayerStrategy::PlayerStrategy(Player *player) : player(player) {}

// copy constructor
PlayerStrategy::PlayerStrategy(const PlayerStrategy &copy)
{
	this->player = copy.player;
}

// destructor
PlayerStrategy::~PlayerStrategy() {}

// output stream
ostream &operator<<(ostream &out, const PlayerStrategy &output)
{
	out << "player strategy" << endl;
	return out;
}

// set player
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

// constructor
HumanPlayerStrategy::HumanPlayerStrategy(Player *player) : PlayerStrategy(player) {}

// copy constructor
HumanPlayerStrategy::HumanPlayerStrategy(const HumanPlayerStrategy &copy) : PlayerStrategy(copy) {}

// destructor
HumanPlayerStrategy::~HumanPlayerStrategy() {}

// assignment operator
HumanPlayerStrategy &HumanPlayerStrategy::operator=(const HumanPlayerStrategy &strat)
{
	PlayerStrategy::operator=(strat);
	return *this;
}

// stream output
ostream &operator<<(ostream &out, const HumanPlayerStrategy &output)
{
	out << "Human player strategy" << endl;
	return out;
}

void HumanPlayerStrategy::issueOrder(GameEngine *gameEngine, PhaseObserver *phaseObserver)
{
	vector<Territory *> controlled = player->getTerritories(); // territories controlled by player

	if (phaseObserver != nullptr)
	{
		phaseObserver->setPlayer(player);
		phaseObserver->setInfo("Issue Order HumanPlayerStrategy");
	}

	// gets territories to defend and attack of player
	vector<Territory *> toDefendTerritory = player->toDefend(phaseObserver);
	vector<Territory *> toAttackTerritory = player->toAttack(phaseObserver);

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
					int toDeploy = 0;
					do
					{
						cout << "Input number toDeploy between 0 and " << canDeploy << endl;
						cin >> toDeploy;
						if (toDeploy < 0 || toDeploy > canDeploy)
						{
							cout << "Input number between 0 and " << canDeploy << endl;
						}
					} while (toDeploy < 0 || toDeploy > canDeploy);
					canDeploy -= toDeploy; // subtract deploying armies from total pool
					cout << "Deploying " << toDeploy << " armies to " << toDefendTerritory[i]->getName() + "." << endl;
					if (phaseObserver != nullptr)
					{
						phaseObserver->setInfo(phaseObserver->getInfo() + "Deploying " + to_string(toDeploy) + " armies to " + toDefendTerritory[i]->getName() + ".\n");
					}
					Deploy *deploy = new Deploy(player, toDeploy, toDefendTerritory[i]);
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
	vector<Territory *> allied_neighbours; // neighbouring territories controlled by player
	vector<Territory *> enemy_neighbours;  // neighbouring territories hostile to player

	// let user pick a decision number 0 to 100
	int decision = 0;
	do
	{
		cout << "Input number decision between 0 and 99 inclusively" << endl;
		cin >> decision;
		if (decision < 0 || decision >= 100)
		{
			cout << "Input number between 0 and 99 inclusively"  << endl;
		}
	} while (decision < 0 || decision >= 100);
	if (decision % 2 == 0 || toDefendTerritory.size() < 2) // if even, attack
	{
		cout << "Player " << player->getPlayerID() + 1 << " chooses to attack" << endl;

		int index = 0;
		do
		{
			cout << "Input number index between 0 and " << toAttackTerritory.size() - 1 << endl;
			cin >> index;
			if (index < 0 || index >= toAttackTerritory.size())
			{
				cout << "Input number between 0 and " << toAttackTerritory.size() - 1 << endl;
			}
		} while (index < 0 || index >= toAttackTerritory.size());

		auto all_neighbours = toAttackTerritory[index]->getNeighbours(); // get neighbours of enemy territory
		cout << "Chosen enemy to attack: " << toAttackTerritory[index]->getName() << endl;
		if (phaseObserver != nullptr)
		{
			phaseObserver->setInfo(phaseObserver->getInfo() + "Attempting to attack " + toAttackTerritory[index]->getName() + ".\n");
		}
		cout << "\nEnemies's neighbours: ";
		for (auto n : all_neighbours)
		{
			cout << n->getName() << "   ";
		}
		cout << "\nYour Enemies: ";
		auto all_hostile = player->get_neighbour_territories(player); // get unfriendly
		for (auto n : all_hostile)
		{
			cout << n->getName() << "   ";
		}
		cout << "\n";
		cout << "\n";
		for (Territory *neighbour : all_neighbours)
		{
			auto result = find(toDefendTerritory.begin(), toDefendTerritory.end(), neighbour);
			if (result != toDefendTerritory.end()) // vector contains the element (get own territory close to hostile territory)
			{
				cout << "Player: " << player->getPlayerID() << " chooses to deploy armies from: " << result[0]->getName() << " to attack " << toAttackTerritory[index]->getName() << endl;
				if (result[0]->getArmyNum() > 0) // if own territory has army  (TODO remove the equal later on for check)
				{								 // move random amount of army up to max number in that territory to toAttack Territory
					// pop toAttack territory
					cout << "Allied territory has armies to attack: " << result[0]->getArmyNum() << endl;

					int attackNum = 0;
					do
					{
						cout << "Input number attackNum between 0 and " << result[0]->getArmyNum() << endl;
						cin >> attackNum;
						if (attackNum < 0 || attackNum > result[0]->getArmyNum())
						{
							cout << "Input number between 0 and " << result[0]->getArmyNum() << endl;
						}
					} while (attackNum < 0 || attackNum > result[0]->getArmyNum());

					cout << "To deploy " << attackNum << " armies from: " << result[0]->getName() << " to attack: " << toAttackTerritory[index]->getName() << endl;
					Advance *advanceAtk = new Advance(player, result[0], toAttackTerritory[index], attackNum);
					player->getPlayerOrders().push_back(advanceAtk);
					cout << "Attack order added" << endl;
					if (phaseObserver != nullptr)
					{
						phaseObserver->setInfo(phaseObserver->getInfo() + "Issuing attack from " + result[0]->getName() + " to " + toAttackTerritory[index]->getName() + ".\n");
					}
					break;
				}
				else // if you don't have armies, redundant for now but will be implemented later
				{	 // test to see if it will break
					if (phaseObserver != nullptr)
					{
						phaseObserver->setInfo(phaseObserver->getInfo() + "No armies available to attack " + toAttackTerritory[index]->getName() + ".\n");
					}
					cout << "Don't have armies in " << result[0]->getName() << " to deploy to " << toAttackTerritory[index]->getName() << endl;
					toDefendTerritory.erase(find(toDefendTerritory.begin(), toDefendTerritory.end(), result[0])); // pop from the defend list
					continue;
				}
			}
			else // vector does not contain element
			{
				cout << "You don't own: " << neighbour->getName() << endl;
				if (phaseObserver != nullptr)
				{
					phaseObserver->setInfo(phaseObserver->getInfo() + "Unable to attack from " + neighbour->getName() + ".\n");
				}
				continue;
			}
		}
	}
	else // if odd, defend

	{
		cout << "Player: " << player->getPlayerID() << " chooses to defend" << endl;

		int index = 0;
		do
		{
			cout << "Input number index between 0 and " << toDefendTerritory.size() - 1 << endl;
			cin >> index;
			if (index < 0 || index >= toDefendTerritory.size())
			{
				cout << "Input number between 0 and " << toDefendTerritory.size() - 1 << endl;
			}
		} while (index < 0 || index >= toDefendTerritory.size());

		auto all_neighbours = toDefendTerritory[index]->getNeighbours(); // get neighbours of this territory
		cout << "Chosen territory to defend: " << toDefendTerritory[index]->getName() << endl;

		auto all_friendly = player->get_friendly_neighbour(player); // get all allied neighbours of player
		cout << "Your Allied territories:" << endl;
		for (auto n : all_friendly)
		{
			cout << n->getName() << "   ";
		}
		cout << "\n";

		for (Territory *neighbour : all_neighbours)
		{
			auto result = find(controlled.begin(), controlled.end(), neighbour);
			if (result != controlled.end()) // vector contains the element
			{
				cout << "Player: " << player->getPlayerID() << " chooses to deploy armies from: " << result[0]->getName() << " to defend " << toDefendTerritory[index]->getName() << endl;
				if (result[0]->getArmyNum() > 0) // TODO remove equal later when execution
				{								 // move random amount of army up to max number in that territory to toDefend Territory
					// pop toDefend territory
					cout << "Allied territory has armies to move: " << result[0]->getArmyNum() << endl;

					int moveNum = 0;
					do
					{
						cout << "Input number moveNum between 0 and " << result[0]->getArmyNum() << endl;
						cin >> moveNum;
						if (index < 0 || moveNum > result[0]->getArmyNum())
						{
							cout << "Input number between 0 and " << result[0]->getArmyNum() << endl;
						}
					} while (moveNum < 0 || moveNum > result[0]->getArmyNum());

					cout << "To deploy " << moveNum << " armies from: " << result[0]->getName() << " to defend: " << toDefendTerritory[index]->getName() << endl;
					Advance *advanceDef = new Advance(player, result[0], toDefendTerritory[index], moveNum);
					player->getPlayerOrders().push_back(advanceDef);
					cout << "Defend order added" << endl;
					break;
				}
				else // if don't have armies in that area (redundant for now but will be useful later)
				{	 // test to see if it'll break
					cout << "Don't have armies in " << result[0]->getName() << " to deploy to " << toDefendTerritory[index]->getName() << endl;
					toDefendTerritory.erase(find(toDefendTerritory.begin(), toDefendTerritory.end(), result[0])); // pop from the defend list
					continue;
				}
			}
			else // vector does not contain element
			{
				cout << "You don't control " << neighbour->getName() << endl;
				continue;
			}
			cout << "\nDefending Ended" << endl;
		}
	}

	// 3. use card
	cout << "Choose a card from your hand to use (if you have one): " << endl;
	Deck *deck = new Deck();

	// if player has cards, they'll play one card at random
	if (player->getHand()->getNumberHandCards() > 0)
	{
		cout << "Player " << player->getPlayerID() << " has cards:" << endl;
		for (int i = 0; i < player->getHand()->getNumberHandCards(); i++)
		{
			cout << player->getHand()->getCards()[i]->getCardType() << "   ";
		}
		cout << "\n";

		int cardNumPicked = 0;
		do
		{
			cout << "Input number cardNumPicked between 0 and " << player->getHand()->getNumberHandCards() - 1 << endl;
			cin >> cardNumPicked;
			if (cardNumPicked < 0 || cardNumPicked >= player->getHand()->getNumberHandCards())
			{
				cout << "Input number between 0 and " << player->getHand()->getNumberHandCards() - 1 << endl;
			}
		} while (cardNumPicked < 0 || cardNumPicked >= player->getHand()->getNumberHandCards());

		auto player_orders = player->getPlayerOrders();
		player->getHand()->getCards()[cardNumPicked]->play(player_orders, *deck);
		cout << " ";
	}
	else
	{
		cout << "You don't have cards to play!" << endl;
	}
	gameEngine->Notify(phaseObserver);
}

vector<Territory *> HumanPlayerStrategy::toDefend(PhaseObserver *phaseObserver)
{
	vector<Territory *> toDefendTerritory;
	vector<Territory *> controlled = player->getTerritories(); // territories controlled by player

	// show territories controlled by player
	if (controlled.size() > 0)
	{
		cout << "Player " << player->getPlayerID() + 1 << "'s currently controlled Territories and armies:" << endl;
		for (int i = 0; i < controlled.size(); i++)
		{
			cout << " (" << i << ") " + controlled[i]->getName() + "   " << controlled[i]->getArmyNum() << endl;
		}
	}
	else
	{
		cout << " You currently don't control any territories. " << endl;
		return toDefendTerritory;
	}

	cout << "\nChoose a territory to defend (number corresponding to territory):" << endl;

	// let user choose which territory to defed
	int index = 0;
	do
	{
		cout << "Input number index between 0 and " << controlled.size() - 1 << endl;
		cin >> index;
		if (index < 0 || index >= controlled.size())
		{
			cout << "Input number between 0 and " << controlled.size() - 1 << endl;
		}
	} while (index < 0 || index >= controlled.size());

	while (true)
	{
		// 1. check if picked already
		// 2. if not picked, push to toDefendTerritory vector
		vector<Territory *>::iterator it;
		it = find(toDefendTerritory.begin(), toDefendTerritory.end(), controlled[index]);

		if (it != toDefendTerritory.end())
		{
			cout << controlled[index]->getName() << " already picked." << endl;
		}
		else
		{
			cout << controlled[index]->getName() + " picked." << endl;
			toDefendTerritory.push_back(controlled[index]);
			controlled.erase(find(controlled.begin(), controlled.end(), controlled[index])); // pop from the controlled list
		}

		// 1. if toDefendTerritory size is 0, pick another index and check
		// 2. if toDefendTerritory size is 1*, make a decision (odd/even) to decide whether to continue picking or not
		if (toDefendTerritory.size() < 1)
		{
			index = 0;
			do
			{
				cout << "Input number index between 0 and " << controlled.size() - 1 << endl;
				cin >> index;
				if (index < 0 || index >= controlled.size())
				{
					cout << "Input number between 0 and " << controlled.size() - 1 << endl;
				}
			} while (index < 0 || index >= controlled.size());
			continue;
		}
		else
		{

			// let user pick a decision number 0 to 100
			int decision = 0;
			do
			{
				cout << "Input number decision between 0 and 99 inclusively" << endl;
				cin >> decision;
				if (decision < 0 || decision >= 100)
				{
					cout << "Input number between 0 and 99 inclusively" << endl;
				}
			} while (decision < 0 || decision >= 100);

			if (decision % 2 == 1)
			{ // if odd, finish picking
				cout << "Finished picking.\n"
					 << endl;
				break;
			}
			else if (decision % 2 == 0 && controlled.size() > 0)
			{
				cout << "Pick another territory:" << endl;
				index = 0;
				do
				{
					cout << "Input number index between 0 and " << controlled.size() - 1 << endl;
					if (index < 0 || index >= controlled.size())
					{
						cout << "Input number between 0 and " << controlled.size() - 1 << endl;
					}
				} while (index < 0 || index >= controlled.size());
			}
			else
			{ // if odd, continue picking
				cout << "No more Territories to pick" << endl;
				break;
			}
		}
	}
	return toDefendTerritory;
}

vector<Territory *> HumanPlayerStrategy::toAttack(PhaseObserver *phaseObserver)
{
	vector<Territory *> toAttackTerritory;
	vector<Territory *> controlled = player->getTerritories();							   // territories controlled by player
	vector<Territory *> non_allied_neighbours = player->get_neighbour_territories(player); // neighbouring territories not controlled by player

	// 1. check if you have enough army to deploy to areas to add
	// 2. if toAttackTerritory size is 0, pick index and check
	// 3. if toAttackTerritory size is 1+, make decision (odd/even) to decide whether to continue picking or not
	int deploy_limit = player->getReinforcementPool(); // get reinforcement pool to deploy

	if (non_allied_neighbours.size() > 0)
	{
		//	Show possible territories to attack
		cout << " Territories to attack:" << endl;
		for (int i = 0; i < non_allied_neighbours.size(); i++)
			cout << "  (" << i << ") " + non_allied_neighbours[i]->getName() + "   " << non_allied_neighbours[i]->getArmyNum() << endl;
		cout << endl;
		cout << "Choose the territory to attack: " << endl;
	}
	else
	{
		cout << "You don't have any neighbours." << endl;
		return toAttackTerritory;
	}

	// let user choose which territory to attack
	int index = 0;
	do
	{
		cout << "Input number index between 0 and " << non_allied_neighbours.size() - 1 << endl;
		cin >> index;
		if (index < 0 || index >= non_allied_neighbours.size())
		{
			cout << "Input number between 0 and " << non_allied_neighbours.size() - 1 << endl;
		}
	} while (index < 0 || index >= non_allied_neighbours.size());

	while (true)
	{
		vector<Territory *>::iterator it;
		it = find(toAttackTerritory.begin(), toAttackTerritory.end(), non_allied_neighbours[index]);

		if (it != toAttackTerritory.end())
		{ // if the territory pick is already in toAttackTerritory
			cout << non_allied_neighbours[index]->getName() << " already picked." << endl;

			// let user pick a decision number 0 to 100
			index = 0;
			do
			{
				cout << "Input number index between 0 and " << controlled.size() - 1 << endl;
				cin >> index;
				if (index < 0 || index >= controlled.size())
				{
					cout << "Input number between 0 and " << controlled.size() - 1 << endl;
				}
			} while (index < 0 || index >= controlled.size());

			continue;
		}
		else
		{
			toAttackTerritory.push_back(non_allied_neighbours[index]);
			cout << non_allied_neighbours[index]->getName() << " added to attacking territories." << endl;
			non_allied_neighbours.erase(find(non_allied_neighbours.begin(), non_allied_neighbours.end(), non_allied_neighbours[index])); // pop from the non allied list
			deploy_limit--;
		}

		if (toAttackTerritory.size() > 1 && deploy_limit > 0)
		{
			// let user pick a decision number 0 to 100
			int decision = 0;
			do
			{
				cout << "Input number decision between 0 and 99 inclusively" << endl;
				cin >> decision;
				if (decision < 0 || decision >= 100)
				{
					cout << "Input number between 0 and 99 inclusively" << endl;
				}
			} while (decision < 0 || decision >= 100);
			if (decision % 2 == 1)
			{ // if odd, finish picking
				cout << "Finished picking.\n"
					 << endl;
				break;
			}
			else if (decision % 2 == 0 && non_allied_neighbours.size() > 0)
			{ // if odd, continue picking
				// let user choose which territory to attack
				cout << "Pick another territory." << endl;
				do
				{
					cout << "Input number index between 0 and " << non_allied_neighbours.size() - 1 << endl;
					cin >> index;
					if (index < 0 || index >= non_allied_neighbours.size())
					{
						cout << "Input number between 0 and " << non_allied_neighbours.size() - 1 << endl;
					}
				} while (index < 0 || index >= non_allied_neighbours.size());
			}
			else // if odd, continue picking
			{
				cout << "No more Territories to pick" << endl;
				break;
			}
		}
		else if (deploy_limit == 0)
		{ // if none to deploy, break the loop
			cout << "No more reinforcements to deploy, finished picking." << endl;
			break;
		}
	}
	return toAttackTerritory;
}

// NOTE: Only issueOrder is listed here since toAttack and toDefend are called within this
// function by default (with the way it is currently set up in Player.cpp)
void HumanPlayerStrategy::execute(GameEngine *gameEngine, PhaseObserver *phaseObserver)
{
	if (phaseObserver != nullptr)
	{
		phaseObserver->setPlayer(player);
		phaseObserver->setInfo("execute Order HumanPlayerStrategy");
	}
	player->issueOrder(gameEngine, phaseObserver);
	gameEngine->Notify(phaseObserver);
}

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

// issue orders: fortify strongest country and keep attacking
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
			deploy->execute();				 // placing to the country so the army numbers are updated
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

	while (true) // attack enemy neighbours from strongest countries first if any
	{
		for (Territory *self : toDefendTerritory)
		{
			int moveNum = self->getArmyNum();						   // get army number in top country
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
				cout << " No enemies to attack. Attacking orders issue done." << endl;
				break;
			}
		}
		cout << " No enemies to attack. Attacking orders issue done." << endl;
		break;
	}
	while (true) // fortifying to aggregate to strongest country
	{
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
			else if (moveNum == 0) // no more to advance
			{
				cout << "No more armies to deploy." << endl;
				break;
			}
		}
		cout << "Fortication orders issue done." << endl;
		break;
	}
	int index = rand() % 2 + 1; // choose number between 1 to 2
	if (index == 0)				// if even set player strategy to benevolent
	{
		cout << "Setting " << player->getPlayerID() + 1 << " to benevolent strategy." << endl;
		player->setStrategy(new BenevolentPlayerStrategy(player));
	}
	gameEngine->Notify(phaseObserver);
}

// to fortify the territories with the most army (to deploy to)
vector<Territory *> AggressivePlayerStrategy::toDefend(PhaseObserver *phaseObserver)
{
	vector<Territory *> toDefendTerritory;
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
	vector<Territory *> toAttackTerritory;
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
			deploy->execute();				 // placing to the country so the army numbers are updated
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
	cout << "Fortication orders issue done." << endl;

	int index = rand() % 2 + 1; // choose number between 1 to 2
	if (index == 0)				// if even set player strategy to agressive strategy
	{
		cout << "Setting " << player->getPlayerID() + 1 << " to aggressive strategy." << endl;
		player->setStrategy(new AggressivePlayerStrategy(player));
	}
	gameEngine->Notify(phaseObserver);
}

// defends least fortified controlled territories
vector<Territory *> BenevolentPlayerStrategy::toDefend(PhaseObserver *phaseObserver)
{	
	vector<Territory *> toDefendTerritory;
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
	vector<Territory *> toAttackTerritory;
	return toAttackTerritory;
}

NeutralPlayerStrategy::NeutralPlayerStrategy(Player *player) : PlayerStrategy(player) {}

// copy constructor
NeutralPlayerStrategy::NeutralPlayerStrategy(const NeutralPlayerStrategy &copy) : PlayerStrategy(copy) {}

// destructor
NeutralPlayerStrategy::~NeutralPlayerStrategy() {}

// assignment operator
NeutralPlayerStrategy &NeutralPlayerStrategy::operator=(const NeutralPlayerStrategy &strat)
{
	PlayerStrategy::operator=(strat);
	return *this;
}

// stream output
ostream &operator<<(ostream &out, const NeutralPlayerStrategy &output)
{
	out << "Neutral player strategy" << endl;
	return out;
}

// we don't issue anything for this strategy
void NeutralPlayerStrategy::issueOrder(GameEngine *gameEngine, PhaseObserver *phaseObserver)
{
	cout << "NeutralPlayerStrategy not allowed to issueOrder" << endl;
	// gameEngine->Notify(phaseObserver);
}

// return their initial toDefendTerritory no modification
vector<Territory *> NeutralPlayerStrategy::toDefend(PhaseObserver *phaseObserver)
{
	cout << "NeutralPlayerStrategy not allowed to toDefend" << endl;
	vector<Territory *> toDefendTerritory;
	vector<Territory *> controlled = player->getTerritories(); // territories controlled by player

	// show territories controlled by player
	if (controlled.size() > 0)
	{
		cout << "Player " << player->getPlayerID() + 1 << "'s currently controlled Territories and armies:" << endl;
		for (int i = 0; i < controlled.size(); i++)
		{
			cout << " (" << i << ") " + controlled[i]->getName() + "   " << controlled[i]->getArmyNum() << endl;
		}
	}
	else
	{
		cout << " You currently don't control any territories. " << endl;
		return toDefendTerritory;
	}

	return toDefendTerritory;
}

// return their initial toAttackTerritory no modification
vector<Territory *> NeutralPlayerStrategy::toAttack(PhaseObserver *phaseObserver)
{
	cout << "NeutralPlayerStrategy not allowed to toAttack" << endl;

	vector<Territory *> toAttackTerritory;
	vector<Territory *> controlled = player->getTerritories();							   // territories controlled by player
	vector<Territory *> non_allied_neighbours = player->get_neighbour_territories(player); // neighbouring territories not controlled by player

	if (non_allied_neighbours.size() > 0)
	{
		//	Show possible territories to attack
		cout << " Territories to attack:" << endl;
		for (int i = 0; i < non_allied_neighbours.size(); i++)
			cout << "  (" << i << ") " + non_allied_neighbours[i]->getName() + "   " << non_allied_neighbours[i]->getArmyNum() << endl;
		cout << endl;
		cout << "Choose the territory to attack: " << endl;
	}
	else
	{
		cout << "You don't have any neighbours." << endl;
		return toAttackTerritory;
	}

	return toAttackTerritory;
}

// don't execute anything, update phaseObserver
void NeutralPlayerStrategy::execute(GameEngine *gameEngine, PhaseObserver *phaseObserver)
{
	cout << "NeutralPlayerStrategy not allowed to execute" << endl;
	if (phaseObserver != nullptr)
	{
		phaseObserver->setPlayer(player);
		phaseObserver->setInfo("execute Order NeutralPlayerStrategy");
	}
	player->issueOrder(gameEngine, phaseObserver);
	gameEngine->Notify(phaseObserver);
}
