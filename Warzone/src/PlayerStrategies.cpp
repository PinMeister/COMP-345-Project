#include "../include/PlayerStrategies.h"
#include "../include/GameEngine.h"
#include "../include/GameObservers.h"

using namespace std;

PlayerStrategy::PlayerStrategy(Player* player) {}

PlayerStrategy::~PlayerStrategy() { }

vector<Territory*> PlayerStrategy::toDefend(PhaseObserver *phaseObserver) { return toDefendTerritory; }
	
vector<Territory*> PlayerStrategy::toAttack(PhaseObserver *phaseObserver) { return toAttackTerritory; }

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

void AggressivePlayerStrategy::issueOrder(GameEngine *gameEngine, PhaseObserver *phaseObserver) {

}

vector<Territory*> AggressivePlayerStrategy::toDefend(PhaseObserver *phaseObserver) {
    
}

vector<Territory*> AggressivePlayerStrategy::toAttack(PhaseObserver *phaseObserver) {
    
}

// void AggressivePlayerStrategy::execute(GameEngine *gameEngine, PhaseObserver *phaseObserver) {
//     issueOrder(gameEngine, phaseObserver);
    
// }


//  ---BenevolentPlayerStrategy (reinforce weakest countries, never attacks, fortifies to move armies to weaker countries) ---

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
