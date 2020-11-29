#include "../include/PlayerStrategies.h"
#include "../include/GameEngine.h"
#include "../include/GameObservers.h"

using namespace std;

// TO DO: Repurpose issueOrder, toAttack and toDefend to conform to each strategy
void HumanPlayerStrategy::issueOrder(GameEngine *gameEngine, PhaseObserver *phaseObserver) {

}

void HumanPlayerStrategy::toDefend(PhaseObserver *phaseObserver) {
    
}

void HumanPlayerStrategy::toAttack(PhaseObserver *phaseObserver) {
    
}

// NOTE: Only issueOrder is listed here since toAttack and toDefend are called within this
// function by default (with the way it is currently set up in Player.cpp)
void HumanPlayerStrategy::execute(GameEngine *gameEngine, PhaseObserver *phaseObserver) {
    issueOrder(gameEngine, phaseObserver);
}

void AggressivePlayerStrategy::issueOrder(GameEngine *gameEngine, PhaseObserver *phaseObserver) {

}

void AggressivePlayerStrategy::toDefend(PhaseObserver *phaseObserver) {
    
}

void AggressivePlayerStrategy::toAttack(PhaseObserver *phaseObserver) {
    
}

void AggressivePlayerStrategy::execute(GameEngine *gameEngine, PhaseObserver *phaseObserver) {
    issueOrder(gameEngine, phaseObserver);
    
}

void BenevolentPlayerStrategy::issueOrder(GameEngine *gameEngine, PhaseObserver *phaseObserver) {

}

void BenevolentPlayerStrategy::toDefend(PhaseObserver *phaseObserver) {
    
}

void BenevolentPlayerStrategy::toAttack(PhaseObserver *phaseObserver) {
    
}

void BenevolentPlayerStrategy::execute(GameEngine *gameEngine, PhaseObserver *phaseObserver) {
    issueOrder(gameEngine, phaseObserver);
}

void NeutralPlayerStrategy::issueOrder(GameEngine *gameEngine, PhaseObserver *phaseObserver) {

}

void NeutralPlayerStrategy::toDefend(PhaseObserver *phaseObserver) {
    
}

void NeutralPlayerStrategy::toAttack(PhaseObserver *phaseObserver) {
    
}

void NeutralPlayerStrategy::execute(GameEngine *gameEngine, PhaseObserver *phaseObserver) {
    issueOrder(gameEngine, phaseObserver);
}
