#include "../include/Player.h"
#include <vector>
#include <iostream>
#include <algorithm> 
#include <stdlib.h> 
#include <time.h>

using namespace std;

// default constructor
Player::Player(int playerID){
	this->playerID = playerID;
	this->reinforcementPool = 0;
}

// construtor with parameters
Player::Player(vector<Territory*> territories, Hand* hand, vector<Order*> orders, int playerID) {
	this->territories = territories;
	this->hand = hand;
	this->orders = orders;
	this->playerID = playerID;
	this->reinforcementPool = 0;
}

// copy constructor
Player::Player(const Player &player){
	this->territories = player.territories;
	this->hand = player.hand;
	this->orders = player.orders;
	this->playerID = player.playerID;
	this->reinforcementPool = player.reinforcementPool;
}

//assignment operator
Player& Player::operator=(const Player &player){ 
	this->territories = player.territories;
	this->hand = player.hand;
	this->orders = player.orders;
	this->playerID = player.playerID;
	this->reinforcementPool = player.reinforcementPool;
	return *this;
}

//stream insertion operator for Player
ostream& operator << (ostream &os, const Player &player){ 
	return os << "Player:" << player.playerID << " Player territories: " << player.territories.size()  << " Player hand: " << player.hand  << "Player orders: " << player.orders.size();
}

vector<Territory*> Player::toDefend() {

	vector<Territory*> controlled = this->getTerritories(); // territories controlled by player

	// show territories controlled by player 
	if (controlled.size() > 0)
	{	
		cout << "Currently controlled Territories and armies: ";
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

	cout << "Choose a territory to defend (number corresponding to territory):" << endl;

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
			}

			// 1. if toDefendTerritory size is 0, pick another index and check
			// 2. if toDefendTerritory size is 1*, make a decision (odd/even) to decide whether to continue picking or not
			if (this->toDefendTerritory.size() < 1) {
				index = rand() % controlled.size();
				continue;
			}
			else 
			{
				int decision = rand() % 100;  // take a random number from 0 to 100
				if (decision % 2 == 0) // if even, finish picking
				{
					cout << "Finished Picking." << endl;
					break;
				}
				else // if odd, continue picking
				{
					cout << "Pick another territory." << endl;
					index = rand() % controlled.size();
				}
			}	
		}
		return this->toDefendTerritory;
}

// creates vector of countries to attack
// 1. get all territories controlled by player 
// 2. neigbours not in controlled are non_allied_neighbours
// 3. pick from non_allied_neighbours randomly and add to toAttackTerritory
vector<Territory*> Player::toAttack() {
	vector<Territory*> controlled = this->getTerritories(); // territories controlled by player
	vector<Territory*> non_allied_neighbours = this->get_neighbour_territories(this); // neighbouring territories not controlled by player
	
	// 1. check if you have enough army to deploy to areas to add
	// 2. if toAttackTerritory size is 0, pick index and check
	// 3. if toAttackTerritory size is 1+, make decision (odd/even) to decide whether to continue picking or not
	int deploy_limit = this->getReinforcementPool(); // get reinforcement pool to deploy

	if (non_allied_neighbours.size() > 0) 
	{
		//	Show possible territories to attack
		cout << " Territories to attack:";
		for (int i = 0; i < non_allied_neighbours.size(); i++)
			cout << "  (" << i << ") " + non_allied_neighbours[i]->getName() + "   " << non_allied_neighbours[i]->getArmyNum();
		cout << endl;

		cout << "Choose the territory to attack: ";
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
		if (this->toAttackTerritory.size() <1 && deploy_limit>0) // if toAttackTerritory size is 0 and have armies to deploy
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
				deploy_limit--;
			}	
		}
		else if (deploy_limit == 0) // if none to deploy, break the loop
		{
			cout << "No more reinforcements to deploy, finished picking." << endl;
			break;
		}

		else
		{
			int decision = rand() % 100;  // take a random number from 0 to 100
			if (decision % 2 == 0) // if even, finish picking
			{
				cout << "Finished Picking." << endl;
				break;
			}
			else // if odd, continue picking
			{
				cout << "Pick another territory." << endl;
				index = rand() % non_allied_neighbours.size();
			}
		}	
	}
	
	return this->toAttackTerritory;
}

// TODO issueOrder
void Player::issueOrder() {
	vector<Territory*> controlled = this->getTerritories(); // territories controlled by player


    // tell whose player's orders
    cout << "\n\nPlayer: " << this->getPlayerID() << "'s  Orders" << endl;

    // gets territories to defend and attack of player
    toDefendTerritory = this->toDefend();
    toAttackTerritory = this->toAttack();

    int canDeploy = this->getReinforcementPool(); // get player's army pool
    cout << "Player " << this->getPlayerID() << " currently has: " << canDeploy << " armies" << endl;
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
                    cout << "Deploying " << toDeploy << " armies to " << toDefendTerritory[i]->getName() << endl;
                    // TODO create deploy order issue
					Deploy* deploy = new Deploy(toDeploy,toDefendTerritory[i]->getName());
					this->orders.push_back(deploy);
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
	cout << "\n Advanced Orders " << endl;
	// 2. advanced orders
		vector<Territory*> allied_neighbours; // neighbouring territories controlled by player
		vector<Territory*> enemy_neighbours; // neighbouring territories hostile to player
		
		int decision = rand() % 100;  // take a random number from 0 to 100
			if (decision % 2 == 0  || toDefendTerritory.size() < 2) // if even, attack
			{
				cout << "Player: "<< this->getPlayerID()<<  " chooses to attack" << endl;
				int index = rand() % toAttackTerritory.size();
				auto all_neighbours = toAttackTerritory[index]->getNeighbours(); // get neighbours of this territory
				cout << "Chosen enemy to attack: " << toAttackTerritory[index]->getName() << endl;
				cout << "\nEnemies's neighbours: ";
				for (auto n : all_neighbours) {cout << n->getName() << "   ";}
				cout << "\nEnemies: " ;
				auto all_hostile = this->get_neighbour_territories(this); // get unfriendly
				for (auto n : all_hostile) {cout << n->getName() << "   ";}
				cout << "\n" ;
				cout << "\n" ;
				for (Territory* neighbour : all_neighbours) {
					auto result = find(controlled.begin(), controlled.end(), neighbour);
            		if (result != controlled.end()) // vector contains the element (get own territory close to hostile territory)
           			{
						cout << "Player: "<< this->getPlayerID()<< " chooses to deploy armies from: " << result[0]->getName() <<" to attack " << toAttackTerritory[index]->getName()<<endl; 
						if (result[0]->getArmyNum() > 0) // if own territory has army
						{// move random amount of army up to max number in that territory to toAttack Territory
						// pop toAttack territory
						cout << "Allied territory has armies to attack: " << result[0]->getArmyNum() << endl;
						int attackNum = rand() % result[0]->getArmyNum() +1;
						cout << "To deploy " << attackNum << " armies from: " << result[0]->getName() << " to : " <<toAttackTerritory[index]->getName() << endl;
						Advance* advanceAtk = new Advance(result[0]->getName(), toAttackTerritory[index]->getName(), attackNum);
						this->orders.push_back(advanceAtk);
						break;
						}
            		}
            		else  // vector does not contain element
            		{
						cout << "Finding match (attack) " << endl;
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

				auto all_friendly = this->get_friendly_neighbour(this); // get all allied neighbours of player
				for (auto n : all_friendly) {cout << "allies: " << n->getName() << "   ";}
				cout << "\n" ;

				for (Territory* neighbour : all_neighbours) {
					auto result = find(controlled.begin(), controlled.end(), neighbour);
            		if (result != controlled.end()) // vector contains the element
           			{
						cout << "Player: "<< this->getPlayerID()<< " chooses to deploy armies from: " << result[0]->getName()<< " to defend" << toDefendTerritory[index]->getName() << endl; 
						if (result[0]->getArmyNum() > 0)
						{// move random amount of army up to max number in that territory to toDefend Territory
						// pop toDefend territory
						cout << "Allied territory has armies to move: " << result[0]->getArmyNum() << endl;
						int moveNum = rand() % result[0]->getArmyNum() +1;
						cout << "To deploy " << moveNum << " armies from: " << result[0]->getName() << " to : " <<toDefendTerritory[index]->getName() << endl;
						Advance* advanceDef = new Advance(result[0]->getName(), toDefendTerritory[index]->getName(), moveNum);
						this->orders.push_back(advanceDef);
						break;
						}
            		}
            		else  // vector does not contain element
            		{
						cout << "Finding match (defend)" << endl;
               			continue;
            		}
				}
			}


	// 3. use card
	cout << "Choose a card from your hand to use (if you have one): " << endl;
	Deck* deck = new Deck(); 
	
	// if player has cards, they'll play one card at random 
	if (this->hand->getNumberHandCards() > 0) 
	{
	cout << "Player " << this->getPlayerID() << " has cards:"<< endl;
	for (int i = 0; i < hand->getNumberHandCards(); i++)
	{    
		cout << this->hand->getCards()[i]->getCardType() << "   ";
	}
	cout << "\n";

	this->hand->getCards()[rand() % hand->getNumberHandCards()]->play(orders, *deck);
	cout << " ";
	}
	else {
		cout << "You don't have cards to play!"<< endl;
	}
}

// add territory to player
void Player::addTerritory(Territory* territory){
	territories.push_back(territory);
}

// return player's territories
vector<Territory*> Player::getTerritories(){
	return territories;
}

// returns neighbours not controlled by player
vector<Territory*> Player::get_neighbour_territories(Player* p) {
	vector<Territory*> controlled = p->getTerritories(); 
	vector<Territory*> neighbouring_terrritories; 

	// Get neighbour territories ( territories to attack )
	for (Territory* c : controlled) {
		vector<Territory*> attacking = c->getNeighbours();
        
        // for territories to attack find if it's controlled by you
		for (Territory* neighbour : attacking) {
			auto result = find(controlled.begin(), controlled.end(), neighbour);
            if (result == controlled.end()) // vector doesn't contain element
            {
				neighbouring_terrritories.push_back(neighbour); // push to neighbouring territories vector
            }
            else 
            {
                continue;
            }
		}
	}
	return neighbouring_terrritories;
}


// returns neighbours controlled by player
vector<Territory*> Player::get_friendly_neighbour(Player* p) {
	vector<Territory*> controlled = p->getTerritories(); 
	vector<Territory*> friendly_neighbours; 

	// Get neighbour territories ( territories to attack )
	for (Territory* c : controlled) {
		vector<Territory*> all_neighbours = c->getNeighbours();
        
        // for territories to attack find if it's controlled by you
		for (Territory* neighbour : all_neighbours) {
			auto result = find(controlled.begin(), controlled.end(), neighbour);
            if (result != controlled.end()) // vector contains the element
            {
				friendly_neighbours.push_back(neighbour); // push to neighbouring territories vector
            }
            else 
            {
                continue;
            }
		}
	}
	return friendly_neighbours;
}

int Player::getPlayerID(){
	return playerID;
}

int Player::getReinforcementPool(){
	return reinforcementPool;
}

void Player::setReinforcementPool(int i){
	this->reinforcementPool = i;
}

void Player::setOrdersRef(vector<Order*> ordersRef){
	orders = ordersRef;
}
