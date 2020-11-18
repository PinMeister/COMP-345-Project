#include "../include/Cards.h"
#include "../include/Orders.h"

using namespace std;

class Deck;

// constructor and copy constructor
Card::Card(CardType type) {
	this->val = type;
}

Card::Card(const Card &card) {
	this->val = card.val;
}

Card& Card::operator=(const Card &card){
	this->val = card.val;
	return *this;
}

Card::~Card() {
	delete this;
}

Card::CardType Card::getCardType() {
	return this->val;
}

ostream& operator<<(ostream& out, const Card &card){
    return out << "Card Type: " << card.val;
}

void Card::play(vector<Order*> &ol, Deck &deck) {
	Order* o;
	if(this->val == CardType::BOMB) {
		// TODO: supposely player that issues the command, temporarily use OrdersList.
    	//o = new Bomb(1, "mexico");
	}
	if(this->val == CardType::REINFORCEMENT) {
		// TODO: supposely player that issues the command, temporarily use OrdersList.
		//o = new Deploy(1, 2, "canada");
    	//o = new Advance(1, "canada", "usa", 2);
	}
	if(this->val == CardType::BLOCKADE) {
		// TODO: supposely player that issues the command, temporarily use OrdersList.
    	//o = new Blockade(1, "canada");
	}
	if(this->val == CardType::AIRLIFT) {
		// TODO: supposely player that issues the command, temporarily use OrdersList.
	    //o = new Airlift(1, "canada", "usa", 2); 
	}
	if(this->val == CardType::DIPLOMACY) {
		// TODO: supposely player that issues the command, temporarily use OrdersList.
	    //o = new Negotiate(1, 6); 
	}
	ol.push_back(o);

	cout<< "Play CardType:" << this->val << endl;

	deck.addCardBack(*this);
	return;
}

Deck::Deck() {
	for (auto i = 0; i < 56;  ++i)
	{
		int random = rand() % 5; // not really random... 
		if(random % 5 == 0) {
			cards.push_back(new Card(Card::BOMB)); 
		}
		else if(random % 4 == 1) {
			cards.push_back(new Card(Card::REINFORCEMENT)); 
		}
		else if(random % 4 == 2) {
			cards.push_back(new Card(Card::BLOCKADE)); 
		}
		else if(random % 4 == 3) {
			cards.push_back(new Card(Card::AIRLIFT)); 
		}
		else{
			cards.push_back(new Card(Card::DIPLOMACY)); 
		}
	}
	cout<< this << endl;
}

Deck::Deck(vector<Card*> &cpy_cards) {
    for (std::vector<Card*>::iterator it = cpy_cards.begin(); it != cpy_cards.end(); ++it) {
		cards.push_back(new Card(**it));
    }
	cout<< this << endl;
}

Deck& Deck::operator=(const Deck &deck){
	this->cards = deck.cards;
	return *this;
}

Deck::~Deck() {
	delete this;
}

int Deck::getDeckSize() {
	return this->cards.size();
}

void Deck::addCardBack(Card &card){
	this->cards.push_back(&card);
}

Card Deck::draw(){
	Card* draw = nullptr;
	if(!cards.empty()){
		draw = cards.back();
		cards.pop_back();
	}
	else {
		cout << "SOMETHING BAD HAPPENED EMPTY DECK" << endl;
	}
	cout<< "Draw CardType:" << draw->getCardType() << endl;

	return *draw;
}

ostream& operator << (std::ostream& out, const Deck &deck) {
	return out << "Deck has " << deck.cards.size() << " cards" ;
}

Hand::Hand() {
	// for (auto i = 0; i < 5; ++i){
	// 	int random = rand() % 5;
	// 	if(random % 4 == 0) {
	// 		this->cards.push_back(new Card(Card::BOMB)); 
	// 	}
	// 	else if(random % 4 == 1) {
	// 		this->cards.push_back(new Card(Card::REINFORCEMENT)); 
	// 	}
	// 	else if(random % 4 == 2) {
	// 		this->cards.push_back(new Card(Card::BLOCKADE)); 
	// 	}
	// 	else if(random % 4 == 3) {
	// 		this->cards.push_back(new Card(Card::AIRLIFT)); 
	// 	}
	// 	else{
	// 		this->cards.push_back(new Card(Card::DIPLOMACY)); 
	// 	}
	// }
	cout<< this << endl;
}

Hand::Hand( const Hand &hand) {
	// copy each invidual cards
	for ( size_t i = 0; i < hand.cards.size(); ++i ){
		this->cards.push_back(new Card(*hand.cards[i]));
	}

	cout<< this << endl;
}

Hand::~Hand() {
	delete this;
}

Hand& Hand::operator=(const Hand &hand){
	this->cards = hand.cards;
	this->numHandCards = hand.numHandCards;
	return *this;
}

ostream& operator<<(ostream& out, const Hand &hand){
    return out << "Hand has " << hand.cards.size() << " cards";
}

void Hand::addCard(Card &card){
	this->cards.push_back(&card);
}

int Hand::getNumberHandCards(){
	return this->cards.size();
}

vector<Card*> Hand::getCards(){
	return this->cards;
}