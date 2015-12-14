/*************
Thaddeus Ciras
playerFuns.cpp
*************/

#include "crib.h"

Player::Player(){
	pnum = 0;
	pts = 0;
}

Player::Player(int num = 0){
       	pnum = num;
	pts = 0;
}

void Player::addCard(Card add){
        hand.push_back(add);
}

void Player::peg(int num){
	pts += num;
}

int Player::getPts(){
	return pts;
}

Deck& Player::getHand(){
        return hand;
}

void Player::printHand(){
        cout << endl << endl << "Player " << pnum + 1 << "'s hand contains:" << endl;
	print();
}

void Player::sortHand(){
	sort(hand.begin(), hand.end());
}

