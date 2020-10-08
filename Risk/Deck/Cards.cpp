#include "Cards.h"
using namespace std;

void Deck::draw()
{
}


CardType Card::getCardType() const {
	return cardType;
}


// SPY, BOMB, REINFORCEMENT, BLOCKADE, AIRLIFT, DIPLOMACY
std::string Card::getCardTypeToString() const {
	if (cardType == SPY)
		return "spy";
	else if (cardType == BOMB)
		return "bomb";
	else if (cardType == REINFORCEMENT)
		return "reinforcement";
	else if (cardType == BLOCKADE)
		return "blockade";
	else if (cardType == AIRLIFT)
		return "airlift"; 
	else 
		return "diplomacy";
}

void Card::setCardType(CardType cardType) {
	this->cardType = carType;
}
