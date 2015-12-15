/*************
Thaddeus Ciras
tableFuns.cpp
*************/

#include "crib.h"

Table::Table(Wood play){
	for (int i = 0; i < play.size(); ++i){
		players.push_back(play[i].getHand());
		scores.push_back(play[i].getPts());
	}
	
	total = 0;
	rmv = 0;
}

int Table::getTotal(){
	return total;
}

int Table::getScore(int num){
	return scores[num];
}

bool Table::checkPlayed(Card& card){
	int value = (card.getValue() > 10 ? 10 : card.getValue());
	
	if (value + total > 31){
		cout << "You can't do that" << endl;
		return false;
	}
	return true;
}

int Table::calculate(Card& card){
	int sum = 0;
	int value = (card.getValue() > 10 ? 10 : card.getValue());
	
	cards.push_back(card);
	
	sum += pairs();
	sum += run();
	
	cout << "The " << card.toString() << " was played for " << sum << "pts." << endl;
	
	total += value;
	return sum;
}

void Table::resetTotal(){
	total = 0;
}

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

int Table::run(){
	int count, start;
	
	for (int num = 7; num > 2; --num){ /* Test run sizes 3 - 7 */
		Deck hand;
		count = 1;
		
		for (int i = 0; i < num; ++i){
			hand.push_back(cards[cards.size() - i]);
		}
		
		sortCards(hand);
		if (num == 7 && hand[hand.size() - 1].getValue() > 7){
		} else if (num == 6 && hand[hand.size() - 1].getValue() > 7){
		} else if (num == 5 && hand[hand.size() - 1].getValue() > 8){
		} else if (num == 4 && hand[hand.size() - 1].getValue() > 9){
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

void Table::sortCards(Deck& hand){
        sort(hand.begin(), hand.end());
}

bool Table::pegging(){
	/* Needs a loop that rotates through the players */
	/* 	Needs an option fo a player to GO 	 */
	/* Should show cards remaining and current total */
	
	int num;
	
	cout << "Got here #3" << endl;
	
	for (int i = 0; ; ++i){
		if (i == players.size()){
			i = 0;
		}
		if (players[i].size() == 0){
		} else {
			num = playCard(players[i]);
			removeCard(rmv, i);
		}
		
		scores[i] += num;
		
		if (scores[i] >= 120){
			return true;
		}
	}
	
	return false; 
}

int Table::playCard(Deck& hand){
	int num;
	
	printCards(hand);
	cout << "\t5) GO" << endl;
	
	do{
		cout << "Play What card [0-" << hand.size() << "]: ";
		cin >> num;
	} while (num < 0 && num > hand.size() + 1 && checkPlayed(hand[num]));
	
	rmv = num - 1;
		
	return calculate(hand[num - 1]);
}

void Table::printCards(Deck& hand){
	int i;
	
	cout << "Your Hand: " << endl;
	
	for (i = 0; i < hand.size(); ++i){
		cout << "\t" << i + 1 << ") " << hand[i].toString() << endl;
	}
	
	for (; i < 4; ++i){
		cout << "\t" << i + 1 << ")  * of ********" << endl;
	}
}

void Table::removeCard(int num, int play){
	cards.push_back(players[play][num]);
	players[play].erase(players[play].begin() + num);
}
