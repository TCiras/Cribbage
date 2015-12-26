/*************
Thaddeus Ciras
tableFuns.cpp
*************/

#include "crib.h"

/*
	Constructor
	Input:
		play = vetcor of players
*/
Table::Table(Wood play){
	for (int i = 0; i < play.size(); ++i){
		players.push_back(play[i].getHand());
		scores.push_back(play[i].getPts());
		go.push_back(false);
	}
	
	total = 0;
	rmv = 0;
}

/*
	Getter for the total
*/
int Table::getTotal(){
	return total;
}

/*
	Getter for a player's score
	Input:
		num = which player (Index)
*/
int Table::getScore(int num){
	return scores[num];
}

/*
	Checks the card that was played to insure that the total is under 31
*/
bool Table::checkPlayed(Card& card){
	int value = (card.getValue() > 10 ? 10 : card.getValue());
	
	if (value + total > 31){
		cout << "You can't do that" << endl;
		return false;
	}
	return true;
}

/*
	Calculates the number of points earned by having played a card
	Input:
		card = card being played
	Output:
		The number of points earned by playing that card
*/
int Table::calculate(Card& card){
	int sum = 0;
	int value = (card.getValue() > 10 ? 10 : card.getValue());
	
	if (!checkPlayed(card)){
		return -1;
	}
	
	cards.push_back(card);
	
	sum += pairs();
	sum += run();
	sum += fifteen();
	
	cout << "The " << card.toString() << " was played for " << sum << "pts." << endl;
	
	total += value;
	
	cout << total << endl;
	
	return sum;
}

/*
	Resets the total and sets all GO to false
	NOTE: Should do this when 31 is reached or all players say GO
*/
void Table::resetTotal(){
	total = 0;
	for (int i = 0; i < go.size(); ++i){
		go[i] = false;
	}	
}


/*
	Checks the played cards for fifteen
	Output:
		The number of points earned by fifteen on the table
*/
int Table::fifteen(){
	if (total == 15){
		return 2;
	} else {
		return 0;
	}
}

/*
	Checks the played card for pairs
	Output:
		The number of points earned by playing pairs
*/
int Table::pairs(){
	int sum = 0, size = cards.size();
	
	if (size == 1){
		sum = 0;
	} else if (cards[size].getValue() == cards[size - 1].getValue()){
		if (size == 2){
			sum += 2;
		} else if (cards[size].getValue() == cards[size - 2].getValue()){
			if(size == 3){
				sum += 4;
			} else if (cards[size].getValue() == cards[size - 3].getValue()){
				sum += 6;
			}
		}
	}
	
	return sum;
}

/*
	Checks the played card for runs
	See log to understand skips (12/14/15)
	Output:
		The number of points earned by playing runs 
*/
int Table::run(){
	int count, start;
	
	for (int num = 7; num > 2; --num){ /* Test run sizes 7 - 3 */
		Deck hand;
		count = 1;
		
		for (int i = 0; i < num; ++i){
			hand.push_back(cards[cards.size() - i]);
		}
		
		sortCards(hand);
		if (num == 7 && hand[hand.size() - 1].getValue() > 7){ /* Skip */
		} else if (num == 6 && hand[hand.size() - 1].getValue() > 7){ /* Skip */
		} else if (num == 5 && hand[hand.size() - 1].getValue() > 8){ /* Skip */
		} else if (num == 4 && hand[hand.size() - 1].getValue() > 9){ /* Skip */
		} else {
			start = hand[0].getValue();
			
			for (int i = 0; i < num; ++i){
                        	if (++start == cards[i].getValue()){
                                	++count;
	                        } else {
        	                        break;
                	        }
	                }
			
			if (count == num){
				return num;
			}
		}
	}
	
	return 0;
		
}

/*
	Sorts the "hand" given. Used for calculating runs.
*/
void Table::sortCards(Deck& hand){
        sort(hand.begin(), hand.end());
}

/*
	Place where pegging should run for a single turn
	Output:
		A bool that is true if there is a winner
*/
bool Table::pegging(){
	/* Needs a loop that rotates through the players */
	/* 	Needs an option fo a player to GO 	 */
	/* Should show cards remaining and current total */
	
	int num;
	bool done = false;
	
	for (int i = 0; ; ++i){
		if (i == players.size()){
			i = 0;
		}
		
		if (players[i].size() == 0 || go[i] == true){
			/* Skip player */
		} else {
			num = playCard(players[i]);
			while (num == -1){
				cout << "Total must be less then 31" << endl;
				cout << "Coose another card: " << endl;
				num = playCard(players[i]);
			}
			
			if (num != -2){
				removeCard(rmv, i);
			} else {
				/* Set chain for last card */
				go[i] = true;
				done = testDone();
			}
		}
		
		scores[i] += num;
		
		if (scores[i] >= 120){
			return true;
		}
	}
	
	return false; 
}

/*
	Tests to see if all have said go
	Output:
		A bool that is true if all have said go.
*/
bool Table::testDone(){
	for (int i = 0; i < go.size(); ++i){
		if (go[i] == false){
			return false;
		}
	}
	
	return true;
}

/*
	Interface of playing cards.
	Input:
		hand = the hand from which a card is going to be played
	Output:
		Number of points earned by playing thh card;
*/
int Table::playCard(Deck& hand){
	int num, calc;
	
	printCards(hand);
        cout << "\t5) GO" << endl;

	do{
		cout << "Play What card [0-" << hand.size() << "]: ";
		cin >> num;
	} while (num < 0 && num > hand.size() + 1 && checkPlayed(hand[num]));
	
	if (num == 5){
		return -2;
	}
	
	calc = calculate(hand[num - 1]);
	if (calc == -1){
		return -1;
	} else {
		rmv = num - 1;
		return calc;
	}
}

/*
	Print function for the hand
	Input:
		hand = the hand to print
*/
void Table::printCards(Deck& hand){
	int i;
	
	cout << "Your Hand: " << endl;
	
	for (i = 0; i < hand.size(); ++i){
		cout << "\t" << i + 1 << ") " << hand[i].toString() << endl;
	}
	
	for (; i < 4; ++i){ /* No longer a card in hand. Keeps numbering correct */
		cout << "\t" << i + 1 << ")  * of ********" << endl;
	}
}

/*
	Talkes card from player and puts it on the table
	Input:
		num = which card to remove (Index)
		play = which player (Index)
*/
void Table::removeCard(int num, int play){
	cards.push_back(players[play][num]);
	players[play].erase(players[play].begin() + num);
}
