#ifndef CARDS_H
#define CARDS_H

#include <iostream>
#include <string>
#include <vector>
#include "../include/Orders.h"

using namespace std;

class Deck;
class Card;
class Hand;

class Card {

public:
	// enum for card type
	enum CardType {
		BOMB, REINFORCEMENT, BLOCKADE, AIRLIFT, DIPLOMACY
	};

	// constructor
	Card(CardType val);	
	// copy constructor
	Card(const Card &card);	
	// deconstructor
	~Card();
	// assignment operator
	Card& operator = (const Card &card);
	// stream operator
	friend ostream& operator << (std::ostream& out, const Card &card); 

	// getter function for card type
	CardType getCardType();
	// play the card, remove from hand and return to deck
	void play(vector<Order*> &ol, Deck &deck);

private:
	CardType val;
};

class Deck {
private:
	// int deckSize;
	// int numBomb;
	// int numbReinforcement;
	// int numBlockade;
	// int numbAirlift;
	// int numDiplomacy;
	
public: 
	// constructor
	Deck();
	// copy constructor
	Deck( const Deck &deck);
	// destructor
	~Deck();
	// assignment operator
	Deck& operator = ( const Deck &deck);

	explicit Deck(vector<Card *> &cards);
	// stream operator
	friend ostream& operator << (std::ostream& out, const Deck &deck);

	vector<Card*> cards;
	Card draw();
	void addCardBack(Card &card);
	// player draws card at random from cards remaining and puts into their hand
	int getNumberOfCards(); 
	int getDeckSize();
};

// hand has finite collection of cards, taken from deck. When played, cards leave hand and return to deck
class Hand {
private:
	vector<Card*> cards;
	int numHandCards;

public:
	// constructor
	Hand();
	// copy constructor
	Hand(const Hand &hand);
	// destructor
	~Hand();
	// assignment operator
	Hand& operator = ( const Hand &hand);
	// stream operator
	friend ostream& operator << (std::ostream& out, const Hand &hand);
	vector<Card*> getCards();
	void addCard(Card &card);
	// void printHand();
	int getNumberHandCards();
	// Card play();
};

#endif