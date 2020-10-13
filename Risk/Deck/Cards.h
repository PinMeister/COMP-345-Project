using namespace std;


#include <iostream>
#include <string>
#include <vector>

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

	void play();
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
	void printDeck();
	
	Card draw();
	// player draws card at random from cards remaining and puts into their hand
	int getNumberOfCards(); 

	int get_DeckSize();
};

// hand has finite collection of cards, taken from deck. When played, cards leave hand and return to deck
class Hand {
private:
	vector<Card*> *cards;
	int numHandCards;
	int maxCards;
public:

	// constructor
	Hand();
	// copy constructor
	Hand( const Hand &hand);
	// destructor
	~Hand();
	// assignment operator
	Hand& operator = ( const Hand &hand);
	// stream operator
	friend ostream& operator << (std::ostream& out, const Deck &deck);
	vector<Card*> * get_cards();
	// void getHand();
	// void printHand();
	int getNumberHandCards();
	// Card play();

};