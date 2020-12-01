#pragma once

#include "../include/Orders.h"
#include "../include/Cards.h"

class Territory;
class Player;

class PlayerStrategy {

    friend class GameEngine;
	friend class Player;
	friend class Card;

	public:
        PlayerStrategy(Player* player); // base constructor, player owns strategy
        PlayerStrategy(const PlayerStrategy &strat); // copy constructor
        PlayerStrategy& operator=(const PlayerStrategy& other); // assignment operator
        // virtual orders

        virtual ~PlayerStrategy(); // desctructor
		virtual vector<Territory*> toDefend(PhaseObserver *phaseObserver);
        virtual vector<Territory*> toAttack(PhaseObserver *phaseObserver);
        virtual void issueOrder(GameEngine *gameEngine, PhaseObserver *phaseObserver) =0;
        //virtual void execute(GameEngine *gameEngine, PhaseObserver *phaseObserver) = 0;  // actually I don't think we need this 
    private:
    vector<Territory*> toDefendTerritory;
	vector<Territory*> toAttackTerritory;
    int reinforcementPool;

};

class HumanPlayerStrategy : public PlayerStrategy {
	public:
		//void execute(GameEngine *gameEngine, PhaseObserver *phaseObserver);
        void virtual issueOrder(GameEngine *gameEngine, PhaseObserver *phaseObserver);
        vector<Territory*> toDefend(PhaseObserver *phaseObserver);
        vector<Territory*> toAttack(PhaseObserver *phaseObserver);
};


// AggressivePlayerStrategy (reinforce strongest country,
// always attack with it until it can't anymore, fortifies in order to maximize aggregation of forces in one country)
class AggressivePlayerStrategy : public PlayerStrategy {
	public:
        AggressivePlayerStrategy(Player* player); // base constructor
        AggressivePlayerStrategy(const AggressivePlayerStrategy &strat); // copy constructor
        ~AggressivePlayerStrategy(); // destructor


		//void execute(GameEngine *gameEngine, PhaseObserver *phaseObserver);
        void virtual issueOrder(GameEngine *gameEngine, PhaseObserver *phaseObserver);
        vector<Territory*> virtual toDefend(PhaseObserver *phaseObserver);
        vector<Territory*> virtual toAttack(PhaseObserver *phaseObserver);
};


// BenevolentPlayerStrategy (reinforce weakest countries, never attacks, fortifies to move armies to weaker countries)
class BenevolentPlayerStrategy : public PlayerStrategy {
	public:
        BenevolentPlayerStrategy(Player* player); // base constructor
        BenevolentPlayerStrategy(const BenevolentPlayerStrategy &strat); // copy constructor
        ~BenevolentPlayerStrategy(); // destructor

		//void execute(GameEngine *gameEngine, PhaseObserver *phaseObserver);
        void virtual issueOrder(GameEngine *gameEngine, PhaseObserver *phaseObserver);
        vector<Territory*> virtual toDefend(PhaseObserver *phaseObserver);
        vector<Territory*> virtual toAttack(PhaseObserver *phaseObserver);
};

class NeutralPlayerStrategy : public PlayerStrategy {
	public:
		//void execute(GameEngine *gameEngine, PhaseObserver *phaseObserver);
        void virtual issueOrder(GameEngine *gameEngine, PhaseObserver *phaseObserver);
        vector<Territory*> toDefend(PhaseObserver *phaseObserver);
        vector<Territory*> toAttack(PhaseObserver *phaseObserver);
};
