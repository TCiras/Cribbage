/*************
Thaddeus Ciras
cardFuns.cpp
*************/

#include "crib.h"

Card::Card(int f = 0, int s = 0){
	value = f;
	suit = s;
}

string Card::toString(){
	string cardName;
	cardName += faces[value];
	cardName += " of ";
	cardName += suits[suit];
	return cardName;
}

bool Card::operator<(const Card& arg) const{
	return value < arg.value;
}


