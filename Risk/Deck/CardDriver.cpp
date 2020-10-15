#include "../Deck/Cards.h"
#include "../Orders/Orders.h"
#include <iostream>
#include <cstdlib>


using namespace std;

/*Driver that creates  a  deck  of  cards  of  all  different  kinds, 
then  creates  a  hand object  that  is  filled by drawing cards from the deck,
then calls the play method of allcards in the hand.*/
int main() {

    cout << "Deck content" << endl;
	cout << "++++++++++++" << endl;
	vector<Card*> deckCards;
	for (auto i = 0; i < 46;  ++i)
	{
		if(i % 5 == 0) {
			deckCards.push_back(new Card(Card::BOMB)); 
		}
		else if(i % 4 == 1) {
			deckCards.push_back(new Card(Card::REINFORCEMENT)); 
		}
		else if(i % 4 == 2) {
			deckCards.push_back(new Card(Card::BLOCKADE)); 
		}
		else if(i % 4 == 3) {
			deckCards.push_back(new Card(Card::AIRLIFT)); 
		}
		else{
			deckCards.push_back(new Card(Card::DIPLOMACY)); 
		}
	}

    Deck* deck = new Deck(); 
    Hand* hand = new Hand();
    cout << *deck << endl;

    cout << *hand << endl;
	cout << "drawing 1" << endl;
	Card c = deck->draw();
    hand->addCard(c);
	cout << "drawing 1" << endl;
	Card d = deck->draw();
    hand->addCard(d);
	cout << "drawing 1" << endl;
	Card e = deck->draw();
    hand->addCard(e);

    cout << *hand << endl;
    cout << *deck << endl;

	// Temporary order vector
	vector<Order*> ol; 
	
	for ( size_t i = 0; i < hand->getCards().size(); ++i ){
		hand->getCards()[i]->play(ol, *deck);
		
	}

    cout << *deck << endl;
    
    delete hand;
    delete deck;

    return 0;
}