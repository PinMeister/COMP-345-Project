#include "Cards.h"
#include "../Orders/Orders.h"
//#include "../Player/Player.h"
using namespace std;

// constructor and copy constructor
Card::Card(CardType type) {
	this->val = new CardType;
}

Card::Card(const Card &card) {
	this->val = card.val;
}

Card::~Card() {
	delete val;
	val = nullptr;
}

Card::CardType Card::getCardType() {
	return *val;
}

ostream& operator<<(ostream& out, const Card &card){
    return out << "Card Type: " << card.val << endl;
}

// void Card::play() {
// 	this.card
// }

Deck::Deck() {
	cards = new vector<Card*>;
}

Deck::Deck(vector<Card *> &cards) {
    this->cards = new vector<Card *>(cards.size());
    auto deckCardsIterator = this->cards->begin();
    auto previousCardsIterator = cards.begin();
    for (size_t i = 0; i < cards.size(); i++) {
        *deckCardsIterator = new Card(**previousCardsIterator);
        deckCardsIterator++;
        previousCardsIterator++;
    }
}

Deck::~Deck() {
	delete cards;
	cards = nullptr;
}

int Deck::get_DeckSize() {
	return this->cards->size();
}

Card Deck::draw(){
	Card card(*(cards->back()));
	cards->pop_back();
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