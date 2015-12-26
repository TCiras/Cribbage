/*************
Thaddeus Ciras
boardFuns.cpp
*************/

#include "crib.h"

/*
	Constructor
	Inputs:
		num = Number of players
*/
Board::Board(int num){
	for (int i = 0; i < num; ++i){
		addPlayer();
	}
	who = 1;
}

/*
	Adds a player to the player vector
*/
void Board::addPlayer(){
	Player player(numPlayers());
	players.push_back(player);
}

/*
	Return's player at index p - 1
	Inputs:
		p = What player # (Not Index)
	Output:
		Number of points belonging to the player
*/
int Board::getPlayer(int p){
	return players[p - 1].getPts();
}


/*
	Moves the player's peg by giving the player points
	Inputs:
		pla = Which player
		num = How many points to add
*/
void Board::peg(int pla, int num){
	players[pla - 1].peg(num);
}


/*
	Getter for the player who has the crib
*/
int Board::getWho(){
	return who;
}


/*
	Setter for the player who has the crib.
	The player is just inceremented
*/
void Board::setWho(){
	if ((who + 1) != numPlayers()){
		++who;
	} else {
		who = 0;
	}
}

/*
	Play a turn
	Inputs:
		deck = The deck of cards to preserve shuffle
	Output:
		A bool that is true if there is a winner
*/
bool Board::playTurn(DeckOfCards& deck){
	cout << "The crib belongs to Player " << who + 1 << endl << endl;
	
	for (int i = 0; i < 6; ++i){
		for (int j = 0; j < numPlayers(); ++j){
			players[j].addCard(deck.dealCard()); 
		}
	}
	
	Card top = deck.dealCard();
	
	for (int i = 0; i < numPlayers(); ++i){
		players[i].sortHand();
		players[i].printHand();
		toCrib(i, players[i].getHand());
		players[i].calculate(top, 0);
	}
	
	crib.sortHand();
	crib.calculate(top, 1);
		
	cout << "The top card is:" << endl;
	cout << "\t\t" << faces[top.getValue()] << " of " << suits[top.getSuit()] << endl;
	
	if (top.getValue() == 10){
		players[who].peg(2);
	}
		
	printAll();
	
	if (pegging()){
		return true;
	}

	return count();
}

/*
	Calculates the amount of points earned by each player in the propper order
	Output:
		A bool that is true if there is a winner
*/
bool Board::count(){
	for (int i = who + 1; i < numPlayers(); ++i){
		players[i].peg(players[i].getScore());
		if (players[i].getPts() >= 120){
			players[i].peg(120 - players[i].getPts());
			return true;
		}
	}
	for (int i = 0; i <= who; ++i){
		players[i].peg(players[i].getScore());
		if (players[i].getPts() >= 120){
			players[i].peg(120 - players[i].getPts());
			return true;
		}
	}
	
	players[who].peg(crib.getScore());
	if (players[who].getPts() >= 120){
		players[who].peg(120 - players[who].getPts());
		return true;
	}
	
	setWho();
	
	return false;
}

/*
	A getter for the number of players
*/
int Board::numPlayers(){
	if (players.size() == 0){
		return 0;
	}
	return players.size();
}

/*
	Players discard cards to the crib
	Inputs:
		num = Which player (Index)
		hand = The player's hand
*/
void Board::toCrib(int num, Deck& hand){
        int a, b;
	
	cout << "Choose two cards to discard: " << endl;
	
	do{
        	cout << "One [1-6]: ";
        	cin >> a;
	} while (a < 0 && a > 7);
	
	do{
	        cout << "Two [1-6]: ";
        	cin >> b;
	} while (b < 0 && b > 7 && b != a);
	
        addCrib(hand[a - 1]);
        addCrib(hand[b - 1]);
        if (a < b){
                players[num].removeCard(b);
                players[num].removeCard(a);
        } else {
                players[num].removeCard(a);
                players[num].removeCard(b);
        }
	cout << endl << endl;
}

/*
	Takes a card and puts it in the crib
	Input:
		card = The card
*/
void Board::addCrib(Card& card){
	crib.addCard(card);
}

/*
	Empty everyone's hand to start the next turn
*/
void Board::clearHands(){
	for (int i = 0; i < numPlayers(); ++i){
		players[i].clearHand();
	}
	
	crib.clearHand();
}

/*
	A print function that display's each player's hands and the crib
*/
void Board::printAll(){
	cout << endl << endl;
	for (int i = 0; i < numPlayers(); ++i){ /* Print titles */
		cout << "Player " << i + 1 << "'s hand:\t\t\t";
	}
	
	cout << "The crib contains: " << endl;
	
	for (int i = 0; i < 4; ++i){ /* Print each card on it's own line */
		cout << "\t";
		for (int j = 0; j < numPlayers(); ++j){
			Card& card = players[j].getCard(i);
			cout << i + 1 << ") " << card.toString();
			
			if (card.getSuit() != 3){
				cout << "\t\t\t\t";
			} else {
				cout << "\t\t\t";
			}
		}
		
		Card& crbCard = crib.getCard(i);
		cout << i + 1 << ") " << crbCard.toString() << endl;
	}
	
	cout << "\t";
	
	for (int i = 0; i < numPlayers(); ++i){ /* Print hand's worth */
		cout  << "Pts: " << players[i].getScore() << "\t\t\t\t\t";
	}
	
	cout << "Pts: " << crib.getScore() << endl << endl << endl;
}

/*
	Pegging wrapper.  Actual pegging done in the Table Class
*/
bool Board::pegging(){
	Table peg(players);
	bool var = peg.pegging();
	
	for(int i = 0; i < numPlayers(); ++i){
		players[i].peg(peg.getScore(i) - players[i].getPts());
	}
	
	return var;
}

/*
	Getter for the players vector
*/
Wood& Board::getPlayers(){
	return players;
}
