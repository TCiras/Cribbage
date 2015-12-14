/*************
Thaddeus Ciras
handFuns.cpp
*************/

#include "crib.h"

Hand::Hand(){
	score = 0;
}

int Hand::pair(int fifth){
	/* Fifth needs to be the value */
	vector<int> cards = {hand[0].getValue(), hand[1].getValue(), hand[2].getValue(), hand[3].getValue(), fifth};
	int matches = 0;
	
	sort(cards.begin(), cards.end());
	
	/* 4 Kind Test */
	if (cards[0] == cards[1] && cards[0] == cards[2] && cards[0] == cards[3]){
		// cout << "P: 12" << endl;
		return 12;
	} else if (cards[1] == cards[2] && cards[1] == cards[3] && cards[1] == cards[4]){
		// cout << "P: 12" << endl;
		return 12;
	}
	/* 3 Kind Test */
	else if (cards[0] == cards[1] && cards[0] == cards[2]){
		// cout << "P: 6" << endl;
		return 6;
	} else if (cards[1] == cards[2] && cards[1] == cards[3]){
		// cout << "P: 6"  << endl;
		return 6;
	} else if (cards[2] == cards[3] && cards[2] == cards[4]){
		// cout << "P: 6" << endl;
		return 6;
	}
	/* 2 Pair Test */
	else if (cards[0] == cards[1] && cards[3] == cards[4]){
		// cout << "P: 4" << endl;
		return 4;
	} else if (cards[0] == cards[1] && cards[2] == cards[3]){
		// cout << "P: 4" << endl;
		return 4;
	} else if (cards[1] == cards[2] && cards[3] == cards[4]){
		// cout << "P: 4" << endl;
		return 4;
	}
	/* 1 Pair Test */
	else {
		for (int i = 0; i < 4; ++i){
			if (cards[i] == cards[i + 1]){
				// cout << "P: 2" << endl;
				return 2;
		}	}
	}
	/* No Pairs */
	// cout << "P: 0" << endl;
	return 0;
	
}

int Hand::run(int fifth){
	/* Fifth needs to be the value */
	int start, count, sum = 0, mult = 1, last = -1;
	vector<int> cards = {hand[0].getValue(), hand[1].getValue(), hand[2].getValue(), hand[3].getValue(), fifth};
	
	sort(cards.begin(), cards.end());
	
	for (int h = 0; h < 3; ++h){
		count = 1;
		start = cards[h];
		
 		for (int i = h + 1; i < 5; ++i){
			if (start == cards[i]){
				/* Set Multiplier */
				if (last == -1 || last != cards[i]){
					last = cards[i];
					mult *= 2;
				} else {
					mult = 3;
				}
			} else if (++start == cards[i]){
				++count;
			} else {
				break;
			}
		}
		
		if (count == 5){
			// cout << "R: 5" << mult;
			return 5 * mult;
		} else if (count == 4){
			// cout << "R: " << 4 * mult << endl;
			return 4 * mult;
		} else if (count == 3){
			// cout << "R: " << 3 * mult << endl;
			return 3 * mult;
		} else {
			/* Look for another */
		}
	}
	
	// cout << "R: 0" << endl;
	return 0;
}

void Hand::print(){
        for (int i = 0; i < hand.size(); ++i){
                cout << "\t\t" << i + 1 << ") " << hand[i].toString() << endl;
        }
}

int Hand::fifteen(int fifth){
	/* Fifth needs to be the value */
	vector<int> cards = {hand[0].getValue(), hand[1].getValue(), hand[2].getValue(), hand[3].getValue(), fifth};
	int sum = 0;
	
	for (int i = 0; i < 4; ++i){ /* Two Card */
		int first = (cards[i] > 10 ? 10 : cards[i]);
		for (int j = i + 1; j < 5; ++j){
			int second = (cards[j] > 10 ? 10 : cards[j]);
			if (first + second == 15){
				sum += 2;
			}
		}
	}
	
	for (int i = 0; i < 3; ++i){ /* Three Card */
		int first = (cards[i] >  10 ? 10 : cards[i]);
		for (int j = i + 1; j < 4; ++j){
			int second = (cards[j] > 10 ? 10 : cards[j]);
			for (int k = j + 1; k < 5; ++k){
				int third = (cards[k] > 10 ? 10 : cards[k]);
				// cout << endl << first << "+" << second << "+" << third << "=" << (first + second + third) << endl;
				if ((first + second + third) == 15){
					sum += 2;
				}
			}
		}
	}
	
	for (int i = 0; i < 2; ++i){ /* Four Card */
		int first = (cards[i] > 10 ? 10 : cards[i]);
		int second = (cards[i + 1] > 10 ? 10 : cards[i + 1]);
		int third = (cards[i + 2] > 10 ? 10 : cards[i + 2]);
		for (int j = i + 3; j < 5; ++j){
			int forth = (cards[j] > 10 ? 10 : cards[j]);
			if ((first + second + third + forth) == 15){
				sum += 2;
			}
		}
	}
	
	if ((cards[0] + cards[1] + cards[2] + cards[3] + cards[4]) == 15){ /* Five Card */
		sum += 2;
	}
	
	// cout << "5: " <<sum << endl;
	return sum;
}

int Hand::flush(int fifth, int crib){
	/* Fifth needs to be the suit */
	vector<int> cards = {hand[0].getSuit(), hand[1].getSuit(), hand[2].getSuit(), hand[3].getSuit(), fifth};
	int count = 1;	
	
	for (int i = 1; i < 5; ++i){
		if (cards[0] == cards[i]){
			++count;
		} else {
			break;
		}
	}
	
	if (crib){
		if (count == 5){
			// cout << "F: 5" << endl;
			return 5;
		} else {
			// cout << "F: 0" << endl;
			return 0;
		}
	} else {
		if (count == 5){
			// cout << "F: 5" << endl;
			return 5;
		} else if (count == 4){
			// cout << "F: 4" << endl;
			return 4;
		} else {
			// cout << "F: 0" << endl;
			return 0;
		}
	}	 
}

int Hand::noobs(int fifth){
	/* Fifth needs to be suit */
	int yes = 0;
	
	for (int i = 0; i < 4; ++i){
		if (hand[i].getValue() == 11){
			yes = (hand[i].getSuit() == fifth ? 1 : 0);
		}
	}
	
	return yes;
}

void Hand::calculate(Card& top, int crib){
	int sum = 0, topValue = top.getValue(), topSuit = top.getSuit();
	
	sum += noobs(topSuit);
	sum += flush(topSuit, crib);
	sum += fifteen(topValue);
	sum += pair(topValue);
	sum += run(topValue);
	
	// cout << "T = " << sum << endl;
	score = sum;
	
}

int Hand::getScore(){
	return score;
}

void Hand::removeCard(int num){
        hand.erase(hand.begin() + num - 1);
}

void Hand::clearHand(){
        for (int i = 4; i > 0; --i){
                removeCard(i);
        }
}

Card& Hand::getCard(int num){
	return hand[num];
}
