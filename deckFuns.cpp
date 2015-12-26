/*************
Thaddeus Ciras
deckFuns.cpp
*************/

#include "crib.h"

/*
	Constructor
	Created one of each card to start
*/
DeckOfCards::DeckOfCards(){
        currentCard = 0;

        for (int i = 0; i < 4; ++i){
                for (int j = 1; j < 14; ++j){
			Card newCard(j,i);
                        deck.push_back(newCard);
                }
        }
}

/*
	Shuffles the deck using the time as the random number
*/
void DeckOfCards::shuffle(){
        for(int i = 0; i < 7; ++i){
		for(int j = 0; j < 52; ++j){
			int random;
			if(i % 2 == 0){
				srand(time(NULL));
			}
			random = rand() % 52;
			swap(deck[j], deck[random]);
		}
	}
}

/*
	"Deals" a card by moving the head pointer
	Output:
		The card at the previous head
*/
Card DeckOfCards::dealCard(){
	return deck[currentCard++];
}

/*
	Checks to make certain there are still cards in the deck
	Output:
		A bool that is true when there are cards in the deck
*/
bool DeckOfCards::moreCards(){
	if (currentCard == 52){
		return false;
	} else {
		return true;
	}
}

/*
	Print function for the deck
*/
void DeckOfCards::printDeck(){
	cout << "Printing Deck" << endl;
	
	for (int i = 0; i < 52; ++i){
		cout << "\t" << i + 1 << ": " << deck[i].toString() << endl;
	}
}

/*
	Deck Reseter. Moves the head pointer back to position zero.
	This allows all cards to be used in the next turn
*/
void DeckOfCards::reset(){
	currentCard = 0;
}
