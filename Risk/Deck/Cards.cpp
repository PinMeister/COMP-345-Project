#include "Cards.h"
#include "../Orders/Orders.h"
//#include "../Player/Player.h"
using namespace std;

// constructor and copy constructor
Card::Card(CardType type) {
	this->val = type;
}

Card::Card(const Card &card) {
	this->val = card.val;
}

Card::~Card() {
	delete this;
}

Card::CardType Card::getCardType() {
	return this->val;
}

ostream& operator<<(ostream& out, const Card &card){
    return out << "Card Type: " << card.val << endl;
}

void Card::play() {
// 	this.card
	return;
}

Deck::Deck() {
	for (auto i = 0; i < 56;  ++i)
	{
		if(i % 5 == 0) {
			cards.push_back(new Card(Card::BOMB)); 
		}
		else if(i % 4 == 1) {
			cards.push_back(new Card(Card::REINFORCEMENT)); 
		}
		else if(i % 4 == 2) {
			cards.push_back(new Card(Card::BLOCKADE)); 
		}
		else if(i % 4 == 3) {
			cards.push_back(new Card(Card::AIRLIFT)); 
		}
		else{
			cards.push_back(new Card(Card::DIPLOMACY)); 
		}
	}
}

Deck::Deck(vector<Card*> &cpy_cards) {
    // vector<Card*> temp  = new vector<Card*>(cards.size());
    auto cardsIterator = cpy_cards.begin();
    for (std::vector<Card*>::iterator it = cardsIterator; it != cards.end(); ++it) {
		cards.push_back(new Card(**it));
    }
}

Deck::~Deck() {
	delete this;
}

int Deck::get_DeckSize() {
	return cards.size();
}

Card Deck::draw(){
	Card card(*(cards.back()));
	cards.pop_back();
	return card;
}

Hand::Hand() {
	cards = new vector<Card*>;
}

Hand::Hand( const Hand &hand) {
	cards = hand.cards;
}

Hand::~Hand() {
	delete cards;
	cards = nullptr;
}

Hand& Hand::operator=(const Hand &hand){
          cards = hand.cards;
          return *this;
     }

ostream& operator<<(ostream& out, const Hand &hand){
    return out << "Hand has: " << hand << endl;
}

int Hand::getNumberHandCards(){
	return cards->size();
}

vector<Card*> * Hand::get_cards() {
	return cards;
}