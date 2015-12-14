/*************
Thaddeus Ciras
main.cpp
*************/

#include "crib.h"

int main(int argc, char* argv[]){
	Board board(2);
	DeckOfCards deck;
	bool winner = false;
	int turn = 0;
	
	do {
		deck.reset();
		deck.shuffle();
		
		winner = board.playTurn(deck);
		
		board.clearHands();
		
		++turn;
	
		cout << "Player 1: " << board.getPlayer(1) << endl;
		cout << "Player 2: " << board.getPlayer(2) << endl;
		cout << endl << endl << endl << endl;
	} while (!winner);

	return 0;
}
