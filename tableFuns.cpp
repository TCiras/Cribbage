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
	
	total += value;
	
	cout << "Total: " << total << endl;
	
	cards.push_back(card);
	
	sum += pairs();
	sum += run();
	sum += fifteen();
	
	if (total == 31){
		sum += 2;
	}
	
	cout << "The " << card.toString() << " was played for " << sum << "pts." << endl;
	cout << "Pts. played is now " << total  << "." << endl;
	
	return sum;
}

/*
	Resets the total, empties the played cards, and sets all GO to false
	NOTE: Should do this when 31 is reached or all players say GO
*/
void Table::reset(){
	total = 0;
	for (int i = 0; i < go.size(); ++i){
		go[i] = false;
	}
	cards.clear();
	printStack();
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
	int sum = 0, size = cards.size() - 1;
	
	if (size + 1 == 1){
		sum = 0;
	} else if (cards[size].getValue() == cards[size - 1].getValue()){
		if (size + 1 == 2){
			sum += 2;
		} else if (cards[size].getValue() == cards[size - 2].getValue()){
			if(size + 1 == 3){
				sum += 6;
			} else if (cards[size].getValue() == cards[size - 3].getValue()){
				sum += 12;
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
	
	for (int num = 7; num > 2; --num){
		Deck hand;
		count = 1;
		
		if (cards.size() < num){ /* Skip */
		} else {
			for (int i = 0; i < num; ++i){
				hand.push_back(cards[cards.size() - (i + 1)]);
			}
			
			sortCards(hand);
			
			int max = hand[hand.size() - 1].getValue();
			
			/* Mike the Commuter's Algorithm */
			if (num == 7 && max > 7){ /* Skip */
			} else if (num == 6 && max > 7){ /* Skip */
			} else if (num == 5 && max > 8){ /* Skip */
			} else if (num == 4 && max > 9){ /* Skip */
			} else {
				start = hand[0].getValue();
				
				for (int i = 1; i < num; ++i){
                	        	if (++start == hand[i].getValue()){
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
	int num;
	
	for (int i = 0; ; ++i){ /* Issue is here */
		if (i == players.size()){ /* Rotate properly through the players */
			i = 0;
		}
		
		if (players[i].size() == 0){ /* If the player has no cards left */
			bool done = true;
			for (int j = 0; j < players.size(); ++j){ /* See if anyone else has cards */
				if (players[j].size() == 0){
					done = true;
				} else {
					done = false;
					break;
				}
			}
			
			if (done){
				break;
			} else {
				go[i] = true;
			}
		} else if (go[i] == true){ /* Looks to see if all have said go */
			if(testDone()){
				reset();
			}
		} else { /* Player plays a card */
			num = playCard(players[i], i);
			while (num == -1){ /* Invalid card */
				cout << "Total must be less then 31" << endl;
				cout << "Coose another card: " << endl;
				num = playCard(players[i], i);
			}
			
			cout << "Total: " << total << endl;
			
			if (num != -2){ /* If valid card and not GO */
				removeCard(rmv, i);
			} else if (total == 31){ /* If 31 */
				cout << "Total is 31" << endl;
				reset();
			} else { /* If GO */
				go[i] = true;
				if (testDone()){
					reset();
					cout << "Last Card for 1" << endl;
					scores[i] += 1;
				}
			}
		}
		
		scores[i] += num;
		
		if(scores[i] >= 120){
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
		play = which player
	Output:
		Number of points earned by playing the card;
*/
int Table::playCard(Deck& hand, int play){
	int num, calc;
	
	cout << endl << endl << "Player " << play + 1 << ":" << endl;
	printCards(hand);
	bool go = showGo(play);
	
	do {
		do {
			cout << "Play What card [0-" << hand.size() << "]: ";
			cin >> num;
			
			if (num == 5 && go == true){
				break;
			}
			
		} while (num < 0 || num > hand.size());
		
		if (num == 5 && go == true){
			break;
		}
		
	} while (!checkPlayed(hand[num - 1]));
	
	if (num == 5){
		return -2;
	}
	
	calc = calculate(hand[num - 1]);
	if (calc == -1){
		cards.pop_back();
		return -1;
	} else {
		rmv = num - 1;
		return calc;
	}
}

/*
	Decides if player can say go and displays the option only if necessary
	Input:
		play = the humber of the player
	Output:
		A bool that is true if the player can say go
*/
bool Table::showGo(int play){
	for (int i = 0; i < players[play].size(); ++i){
		int value = (players[play][i].getValue() > 10 ? 10 : players[play][i].getValue());
		if (value + total < 31){
			return false;
		}
	}
	
	cout << "\t5) GO" << endl;
	return true;
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
		cout << "\t" << i + 1 << ") * of ********" << endl;
	}
}

/*
	Talkes card from player and puts it on the table
	Input:
		num = which card to remove (Index)
		play = which player (Index)
*/
void Table::removeCard(int num, int play){
	cout << "Playing " << players[play][num].toString() << endl;
	players[play].erase(players[play].begin() + num);
}

/*
	Prints all cards that have been played
*/
void Table::printStack(){
	for (int i = 0; i < cards.size(); ++i){
		cout << "\t" << i + 1 << ") " << cards[i].toString() << endl;
	}
}
