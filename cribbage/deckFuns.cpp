/*************
Thaddeus Ciras
deckFuns.cpp
*************/

#include "crib.h"

DeckOfCards::DeckOfCards(){
        currentCard = 0;

        for (int i = 0; i < 4; ++i){
                for (int j = 1; j < 14; ++j){
			Card newCard(j,i);
                        deck.push_back(newCard);
                }
        }
}

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

Card DeckOfCards::dealCard(){
	return deck[currentCard++];
}

bool DeckOfCards::moreCards(){
	if (currentCard == 52){
		return false;
	} else {
		return true;
	}
}

void DeckOfCards::printDeck(){
	cout << "Printing Deck" << endl;
	
	for (int i = 0; i < 52; ++i){
		cout << "\t" << i + 1 << ": " << deck[i].toString() << endl;
	}
}

void DeckOfCards::reset(){
	currentCard = 0;
}
