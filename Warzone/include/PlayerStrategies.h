#ifndef PLAYERSTRATEGY_H
#define PLAYERSTRATEGY_H

#include "../include/Orders.h"
#include "../include/Cards.h"
#include "../include/GameObservers.h"
#include "../include/Map.h"
#include "../include/Player.h"
#include "../include/GameEngine.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Order;
class Hand;
class OrdersList;
class Territory;
class Player;
class GameEngine;
class PhaseObserver;

class PlayerStrategy {

    friend class GameEngine;
	friend class Player;
	friend class Card;
    friend class Order;

	public:
        PlayerStrategy();
        PlayerStrategy(Player* player); // base constructor, player owns strategy
        PlayerStrategy(const PlayerStrategy &copy); // copy constructor
        PlayerStrategy& operator=(const PlayerStrategy &strat); // assignment operator

        friend ostream& operator<<(ostream& out, const PlayerStrategy& output); // output stream
        // virtual orders
        virtual ~PlayerStrategy(); // desctructor
		virtual vector<Territory*> toDefend(PhaseObserver *phaseObserver) =0;
        virtual vector<Territory*> toAttack(PhaseObserver *phaseObserver) =0;
        virtual void issueOrder(GameEngine *gameEngine, PhaseObserver *phaseObserver) =0;
        //virtual void execute(GameEngine *gameEngine, PhaseObserver *phaseObserver) = 0;  // actually I don't think we need this 

        void setPlayer(Player* player);
    private:

    protected: // fields used in all child classes of this class
        vector<Territory*> toDefendTerritory;
        vector<Territory*> toAttackTerritory;
        Player* player;
};

class HumanPlayerStrategy : public PlayerStrategy {
	public:
        HumanPlayerStrategy();
        HumanPlayerStrategy(Player* player);
		//void execute(GameEngine *gameEngine, PhaseObserver *phaseObserver);
        void virtual issueOrder(GameEngine *gameEngine, PhaseObserver *phaseObserver);
        vector<Territory*> toDefend(PhaseObserver *phaseObserver);
        vector<Territory*> toAttack(PhaseObserver *phaseObserver);
};


// AggressivePlayerStrategy (reinforce strongest country,
// always attack with it until it can't anymore, fortifies in order to maximize aggregation of forces in one country)
class AggressivePlayerStrategy : public PlayerStrategy {
	public:
        AggressivePlayerStrategy();
        AggressivePlayerStrategy(Player* player); // base constructor
        AggressivePlayerStrategy(const AggressivePlayerStrategy &copy); // copy constructor
        AggressivePlayerStrategy& operator=(const AggressivePlayerStrategy& strat); // assignment operator

        friend ostream& operator<<(ostream& out, const AggressivePlayerStrategy& output); // output stream
        ~AggressivePlayerStrategy(); // destructor


		//void execute(GameEngine *gameEngine, PhaseObserver *phaseObserver);
        void virtual issueOrder(GameEngine *gameEngine, PhaseObserver *phaseObserver);
        vector<Territory*> virtual toDefend(PhaseObserver *phaseObserver);
        vector<Territory*> virtual toAttack(PhaseObserver *phaseObserver);
};


// BenevolentPlayerStrategy (reinforce weakest countries, never attacks, fortifies to move armies to weaker countries)
class BenevolentPlayerStrategy : public PlayerStrategy {
	public:
        BenevolentPlayerStrategy();
        BenevolentPlayerStrategy(Player* player); // base constructor
        BenevolentPlayerStrategy(const BenevolentPlayerStrategy &strat); // copy constructor
        BenevolentPlayerStrategy& operator=(const BenevolentPlayerStrategy& strat); // assignment operator

        friend ostream& operator<<(ostream& out, const BenevolentPlayerStrategy& output); // output stream
        ~BenevolentPlayerStrategy(); // destructor

		//void execute(GameEngine *gameEngine, PhaseObserver *phaseObserver);
        void virtual issueOrder(GameEngine *gameEngine, PhaseObserver *phaseObserver);
        vector<Territory*> virtual toDefend(PhaseObserver *phaseObserver);
        vector<Territory*> virtual toAttack(PhaseObserver *phaseObserver);
};

class NeutralPlayerStrategy : public PlayerStrategy {
	public:
        NeutralPlayerStrategy();
        NeutralPlayerStrategy(Player* player); // base constructor
        NeutralPlayerStrategy(const NeutralPlayerStrategy &copy); // copy constructor

		//void execute(GameEngine *gameEngine, PhaseObserver *phaseObserver);
        void virtual issueOrder(GameEngine *gameEngine, PhaseObserver *phaseObserver);
        vector<Territory*> virtual toDefend(PhaseObserver *phaseObserver);
        vector<Territory*> virtual toAttack(PhaseObserver *phaseObserver);
};
#endif