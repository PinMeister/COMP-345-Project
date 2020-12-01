#include "../include/PlayerStrategies.h"
#include "../include/GameEngine.h"
#include "../include/GameObservers.h"

using namespace std;

PlayerStrategy::PlayerStrategy(Player* player) {}

PlayerStrategy::~PlayerStrategy() { }

vector<Territory*> PlayerStrategy::toDefend(PhaseObserver *phaseObserver) { return toDefendTerritory; }
	
vector<Territory*> PlayerStrategy::toAttack(PhaseObserver *phaseObserver) { return toAttackTerritory; }

int PlayerStrategy::getReinforcementPool()
{
	return reinforcementPool;
}

Player* PlayerStrategy::getPlayer()
{
    return player;
}

vector<Order*> Player :: getPlayerOrders(){
	return orders;
}

Hand* Player::getHand()
{
    return hand;
}

// assignment operator
PlayerStrategy& PlayerStrategy::operator=(const PlayerStrategy& strat)
{
    player = strat.player;
    reinforcementPool = player->getReinforcementPool();
    toDefendTerritory.clear(); // clears the territory

    // gets all player owned territories pushes to todefend list
    for (Territory* t : player->getTerritories())
    {
        toDefendTerritory.push_back(t);
    }

    toAttackTerritory.clear(); // clears territories
    // gets enemy territories and pushes to toattack list
    for (Territory* t : player->get_neighbour_territories(player))
    {
        toAttackTerritory.push_back(t);
    }

    return *this;
}

// TO DO: Repurpose issueOrder, toAttack and toDefend to conform to each strategy
void HumanPlayerStrategy::issueOrder(GameEngine *gameEngine, PhaseObserver *phaseObserver) {

}

vector<Territory*> HumanPlayerStrategy::toDefend(PhaseObserver *phaseObserver) {
    
}

vector<Territory*> HumanPlayerStrategy::toAttack(PhaseObserver *phaseObserver) {
    
}

// NOTE: Only issueOrder is listed here since toAttack and toDefend are called within this
// function by default (with the way it is currently set up in Player.cpp)
// void HumanPlayerStrategy::execute(GameEngine *gameEngine, PhaseObserver *phaseObserver) {
//     issueOrder(gameEngine, phaseObserver);
// }


// AggressivePlayerStrategy (reinforce strongest country, always attack with it until it can't anymore,
// fortifies in order to maximize aggregation of forces in one country)

// constructor
AggressivePlayerStrategy::AggressivePlayerStrategy(Player* player) : PlayerStrategy(player) { }

// copy constructor
AggressivePlayerStrategy::AggressivePlayerStrategy(const AggressivePlayerStrategy &strat) : PlayerStrategy(strat) { }

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
    vector<Territory*> controlled = getPlayer()->getTerritories(); // territories controlled by player

	if (phaseObserver != nullptr) {
		phaseObserver->setPlayer(this->getPlayer());
		phaseObserver->setInfo("");
	}

    // gets territories to defend and attack of player
    this->toDefendTerritory = this->toDefend(phaseObserver);
    toAttackTerritory = this->toAttack(phaseObserver);

    int canDeploy = this->getReinforcementPool(); // get player's army pool

	cout << "Player " + to_string(this->getPlayerID() + 1) + " currently has " + to_string(canDeploy) + " armies." << endl; 

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
					Deploy* deploy = new Deploy(this->getPlayer(), toDeploy,toDefendTerritory[i]);
					this->getPlayerOrders().push_back(deploy);
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
				cout << "Player " << this->getPlayerID() + 1 <<  " chooses to attack" << endl;
				int index = rand() % toAttackTerritory.size();
				auto all_neighbours = toAttackTerritory[index]->getNeighbours(); // get neighbours of enemy territory
				cout << "Chosen enemy to attack: " << toAttackTerritory[index]->getName() << endl;
				if (phaseObserver != nullptr) {
						phaseObserver->setInfo(phaseObserver->getInfo() + "Attempting to attack " + toAttackTerritory[index]->getName() + ".\n"); }
				cout << "\nEnemies's neighbours: ";
				for (auto n : all_neighbours) {cout << n->getName() << "   ";}
				cout << "\nYour Enemies: " ;
				auto all_hostile = this->getPlayer()->get_neighbour_territories(this->getPlayer()); // get unfriendly
				for (auto n : all_hostile) {cout << n->getName() << "   ";}
				cout << "\n" ;
				cout << "\n" ;
				for (Territory* neighbour : all_neighbours) {
					auto result = find(toDefendTerritory.begin(), toDefendTerritory.end(), neighbour); 
            		if (result != toDefendTerritory.end()) // vector contains the element (get own territory close to hostile territory)
           			{
						cout << "Player: "<< this->getPlayerID()<< " chooses to deploy armies from: " << result[0]->getName() <<" to attack " << toAttackTerritory[index]->getName()<<endl; 
						if (result[0]->getArmyNum() > 0) // if own territory has army  (TODO remove the equal later on for check)
						{// move random amount of army up to max number in that territory to toAttack Territory
						// pop toAttack territory
						cout << "Allied territory has armies to attack: " << result[0]->getArmyNum() << endl;
						int attackNum = rand() % result[0]->getArmyNum() +1; 
						cout << "To deploy " << attackNum << " armies from: " << result[0]->getName() << " to attack: " <<toAttackTerritory[index]->getName() << endl;
						Advance* advanceAtk = new Advance(this->getPlayer(), result[0], toAttackTerritory[index], attackNum);
						this->getPlayerOrders().push_back(advanceAtk);
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
				cout << "Player: "<< this->getPlayerID()<<  " chooses to defend" << endl;
				int index = rand() % toDefendTerritory.size();
				auto all_neighbours = toDefendTerritory[index]->getNeighbours(); // get neighbours of this territory
				cout << "Chosen territory to defend: " << toDefendTerritory[index]->getName() << endl;

				auto all_friendly = this->getPlayer()->get_friendly_neighbour(this->getPlayer()); // get all allied neighbours of player
				cout << "Your Allied territories:" << endl;
				for (auto n : all_friendly) {cout << n->getName() << "   ";}
				cout << "\n" ;

				for (Territory* neighbour : all_neighbours) {
					auto result = find(controlled.begin(), controlled.end(), neighbour);
            		if (result != controlled.end()) // vector contains the element
           			{
						cout << "Player: "<< this->getPlayerID()<< " chooses to deploy armies from: " << result[0]->getName()<< " to defend " << toDefendTerritory[index]->getName() << endl; 
						if (result[0]->getArmyNum() > 0) // TODO remove equal later when execution
						{// move random amount of army up to max number in that territory to toDefend Territory
						// pop toDefend territory
						cout << "Allied territory has armies to move: " << result[0]->getArmyNum() << endl;
						int moveNum = rand() % result[0]->getArmyNum() +1;
						cout << "To deploy " << moveNum << " armies from: " << result[0]->getName() << " to defend: " <<toDefendTerritory[index]->getName() << endl;
						Advance* advanceDef = new Advance(this->getPlayer(), result[0], toDefendTerritory[index], moveNum);
						this->getPlayerOrders().push_back(advanceDef);
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
	if (this->getPlayer()->getHand()->getNumberHandCards() > 0) 
	{
	cout << "Player " << this->getPlayerID() << " has cards:"<< endl;
	for (int i = 0; i < hand->getNumberHandCards(); i++)
	{    
		cout << this->hand->getCards()[i]->getCardType() << "   ";
	}
	cout << "\n";

	this->getPlayer()->getHand()->getCards()[rand() % this->getPlayer()->getHand()->getNumberHandCards()]->play(this->getPlayerOrders(), *deck);
	cout << " ";
	}
	else {
		cout << "You don't have cards to play!"<< endl;
	}

	gameEngine->Notify(phaseObserver);
	
}

vector<Territory*> AggressivePlayerStrategy::toDefend(PhaseObserver *phaseObserver) {
    time_t t;

	vector<Territory*> controlled = this->getPlayer()->getTerritories(); // territories controlled by player

	// show territories controlled by player 
	if (controlled.size() > 0)
	{	
		cout << "Player " << this->getPlayerID() + 1 << "'s currently controlled Territories and armies:"<< endl;
		for (int i=0; i< controlled.size(); i++)
		{
			cout << " (" << i << ") "  + controlled[i]->getName()  + "   " << controlled[i]->getArmyNum() << endl;
		}
	}
	else 
	{
		cout << " You currently don't control any territories. " << endl;
		return this->toDefendTerritory;	
	}

	cout << "\nChoose a territory to defend (number corresponding to territory):" << endl;

	//choose territory(ies) to defend
	srand(time(NULL)); // different random outputs everytime it's run
	int index = rand() % controlled.size();
		while (true)
		{
			// 1. check if picked already 
			// 2. if not picked, push to toDefendTerritory vector
			vector<Territory*>::iterator it;
			it = find(this->toDefendTerritory.begin(), this->toDefendTerritory.end(), controlled[index]);

			if (it != this->toDefendTerritory.end())
			{
				cout << controlled[index]->getName() << " already picked." << endl;
			}
			else 
			{
				cout << controlled[index]->getName() + " picked."<< endl;
				this->toDefendTerritory.push_back(controlled[index]);
				controlled.erase(find(controlled.begin(), controlled.end(), controlled[index])); // pop from the controlled list

			}

			// 1. if toDefendTerritory size is 0, pick another index and check
			// 2. if toDefendTerritory size is 1*, make a decision (odd/even) to decide whether to continue picking or not
			if (this->toDefendTerritory.size() < 1) {
				srand((unsigned) time(&t));// different random outputs everytime it's run
				index = rand() % controlled.size();
				continue;
			}
			else 
			{
				int decision = rand() % 100;  // take a random number from 0 to 100
				if (decision % 2 == 1 ) // if odd, finish picking
				{
					cout << "Finished picking.\n" << endl;
					break;
				}
				else if (decision % 2 == 0 && controlled.size() > 0)
				{
					cout << "Pick another territory:" << endl;
					index = rand() % controlled.size();
				}				
				else // if odd, continue picking
				{
					cout << "No more Territories to pick" << endl;
					break;
				}
			}
				
		}
		return this->toDefendTerritory;
    
}

vector<Territory*> AggressivePlayerStrategy::toAttack(PhaseObserver *phaseObserver) 
{
	vector<Territory*> controlled = player->getTerritories(); // territories controlled by player
	vector<Territory*> non_allied_neighbours = player->get_neighbour_territories(player); // neighbouring territories not controlled by player
	time_t t;
	// 1. check if you have enough army to deploy to areas to add
	// 2. if toAttackTerritory size is 0, pick index and check
	// 3. if toAttackTerritory size is 1+, make decision (odd/even) to decide whether to continue picking or not
	int deploy_limit = this->getReinforcementPool(); // get reinforcement pool to deploy

	if (non_allied_neighbours.size() > 0) 
	{
		//	Show possible territories to attack
		cout << " Territories to attack:"<< endl;
		for (int i = 0; i < non_allied_neighbours.size(); i++)
			cout << "  (" << i << ") " + non_allied_neighbours[i]->getName() + "   " << non_allied_neighbours[i]->getArmyNum() << endl;
		cout << endl;

		cout << "Choose the territory to attack: " <<endl;
	}
	else 
	{
		cout << "You don't have any neighbours."<< endl;
		return this->toAttackTerritory;	
	}

	srand(time(NULL)); // different random outputs everytime it's run
	int index = rand() % non_allied_neighbours.size(); // generate random number
	while (true)
	{
	
			vector<Territory*>::iterator it;
			it = find(this->toAttackTerritory.begin(), this->toAttackTerritory.end(), non_allied_neighbours[index]);

			if (it != this->toAttackTerritory.end()) // if the territory pick is already in toAttackTerritory
			{
				cout << non_allied_neighbours[index]->getName() << " already picked." << endl;
				index = rand() % controlled.size();
				continue;
			}
			else 
			{
				this->toAttackTerritory.push_back(non_allied_neighbours[index]);
				cout << non_allied_neighbours[index]->getName() << " added to attacking territories." <<  endl;
				non_allied_neighbours.erase(find(non_allied_neighbours.begin(), non_allied_neighbours.end(), non_allied_neighbours[index])); // pop from the non allied list
				deploy_limit--;
			}	
		
		if (this->toAttackTerritory.size() > 1 && deploy_limit>0)
		{
			int decision = rand() % 100;  // take a random number from 0 to 100
			if (decision % 2 == 1) // if odd, finish picking
			{
				cout << "Finished picking.\n" << endl;
				break;
			}
			else if (decision % 2 == 0 && non_allied_neighbours.size()>0) // if odd, continue picking
			{
				cout << "Pick another territory." << endl;
				index = rand() % non_allied_neighbours.size();
			}
			else  // if odd, continue picking
			{
				cout << "No more Territories to pick" << endl;
				break;
			}
		}

		else if (deploy_limit==0)  // if none to deploy, break the loop
		{
			cout << "No more reinforcements to deploy, finished picking." << endl;
			break;
		}
	
	}
	
	return this->toAttackTerritory;   
}

// void AggressivePlayerStrategy::execute(GameEngine *gameEngine, PhaseObserver *phaseObserver) {
//     issueOrder(gameEngine, phaseObserver);
    
// }


//  ---BenevolentPlayerStrategy (reinforce weakest countries, never attacks, fortifies to move armies to weaker countries) ---


BenevolentPlayerStrategy& BenevolentPlayerStrategy::operator=(const BenevolentPlayerStrategy& strat) 
{
    PlayerStrategy::operator=(strat);
		return *this;
}

void BenevolentPlayerStrategy::issueOrder(GameEngine *gameEngine, PhaseObserver *phaseObserver) {

}

vector<Territory*> BenevolentPlayerStrategy::toDefend(PhaseObserver *phaseObserver) {
    
}

vector<Territory*> BenevolentPlayerStrategy::toAttack(PhaseObserver *phaseObserver) {
    
}

// void BenevolentPlayerStrategy::execute(GameEngine *gameEngine, PhaseObserver *phaseObserver) {
//     issueOrder(gameEngine, phaseObserver);
// }

void NeutralPlayerStrategy::issueOrder(GameEngine *gameEngine, PhaseObserver *phaseObserver) {

}

vector<Territory*> NeutralPlayerStrategy::toDefend(PhaseObserver *phaseObserver) {
    
}

vector<Territory*> NeutralPlayerStrategy::toAttack(PhaseObserver *phaseObserver) {
    
}

// void NeutralPlayerStrategy::execute(GameEngine *gameEngine, PhaseObserver *phaseObserver) {
//     issueOrder(gameEngine, phaseObserver);
// }
