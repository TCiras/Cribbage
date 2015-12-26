/*************
Thaddeus Ciras
playerFuns.cpp
*************/

#include "crib.h"

/*
	Constructor
*/
Player::Player(){
	pnum = 0;
	pts = 0;
}

/*
	Constructor
	Input:
		num = set the player number to something other than 0
*/
Player::Player(int num = 0){
       	pnum = num;
	pts = 0;
}

/*
	Adds a card to the player's hand
	Input:
		add = the card to add to the hand
*/
void Player::addCard(Card add){
        hand.push_back(add);
}

/*
	Move's the player's peg by adding points to their total score
	Input:
		num = number of points to add
*/
void Player::peg(int num){
	pts += num;
}

/*
	Getter fot the number of points
*/
int Player::getPts(){
	return pts;
}

/*
	Getter for the hand
*/
Deck& Player::getHand(){
        return hand;
}

/*
	Print function wrapper for special message
*/
void Player::printHand(){
        cout << endl << endl << "Player " << pnum + 1 << "'s hand contains:" << endl;
	print();
}

/*
	Sort the cards in the player's hand making calculations easier
*/
void Player::sortHand(){
	sort(hand.begin(), hand.end());
}

