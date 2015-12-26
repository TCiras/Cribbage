/*************
Thaddeus Ciras
cardFuns.cpp
*************/

#include "crib.h"

/*
	Constructor
	Inputs:
		f = Card Value (Default: A)
		s = Card Suit (Default: Club)
*/
Card::Card(int f = 1, int s = 0){
	value = f;
	suit = s;
}

/*
	Converts a card's data to a string
	Output:
		The string
*/
string Card::toString(){
	string cardName;
	cardName += faces[value];
	cardName += " of ";
	cardName += suits[suit];
	return cardName;
}

/*
	Overloaded Less Than Operator
*/
bool Card::operator<(const Card& arg) const{
	return value < arg.value;
}


