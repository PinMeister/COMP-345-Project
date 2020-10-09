using namespace std;


#include <iostream>
#include <string>

// each card has a type 
enum CardType {
	BOMB, REINFORCEMENT, BLOCKADE, AIRLIFT, DIPLOMACY
};

class Card {
private:
public:
	Card() = default;
	// getter function for card type
	void getCardType() const;

	// converting enum to string
	std::string getCardTypeToString() const; 

	// setter function for card type
	void setCardType(cardType cardType);

	// play method that plays the card (creates order and adds to player's list of orders, then returns card to deck)
	void play();

};

class Deck {

private:
public: 
	Deck() = default;
	// player draws card at random from cards remaining and puts into their hand
	void draw();

};

// hand has finite collection of cards, taken from deck. When played, cards leave hand and return to deck
class Hand {
private:
public:
	Hand() = default;

};