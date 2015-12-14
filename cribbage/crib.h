/*************
Thaddeus Ciras
crib.h
*************/

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

static vector<string> faces = {"Joker","A","2","3","4","5","6","7","8","9","10","J","Q","K"};
static vector<string> suits = {"Spades","Hearts","Clubs","Diamonds"};

class Card{
private:
	int value;
	int suit;
public:
  	Card(int, int);
	string toString();
	int getValue(){
		return value;
	}
	int getSuit(){
		return suit;
	}
	bool operator<(const Card&) const;
};

typedef vector<Card> Deck;

class Hand{
protected:
	Deck hand;
	int score;
public:
	Hand();
	void calculate(Card&, int);
	int pair(int);
	int fifteen(int);
	int run(int);
	int flush(int, int);
	int noobs(int);
	void print();
	int getScore();
	void removeCard(int);
	void clearHand();
	Card& getCard(int);
};


class DeckOfCards{
private:
	Deck deck;
	int currentCard;
public:
	DeckOfCards();
	void shuffle();
	Card dealCard();
	bool moreCards();
	void printDeck();
	void reset();
};

class Player : public Hand{
private:
	int pnum;
	int pts;
public:
	Player();
	Player(int);
	void addCard(Card);
	void peg(int);
	int getPts();
	Deck& getHand();
	void printHand();
	void sortHand();
};

class Crib : public Player{
private:
	int belong;
public:
	Crib();
	void printCrib();
};

typedef vector<Player> Wood;

class Board{
private:
	Wood players;
	Crib crib;
	int who;
public:
	Board(int);
	void peg(int, int);
	int getPlayer(int);
	void addPlayer();
	int getWho();
	void clearHands();
	void setWho();
	bool count();
	bool pegging();
	bool playTurn(DeckOfCards&);
	int numPlayers();
	void addCrib(Card&);
	void printAll();
	void toCrib(int, Deck&);
	Wood& getPlayers();
};

typedef vector<Deck> Box;

class Table{
private:
	int total;
	Box players;
	Deck cards;
public:
	Table(Wood);
	int getTotal();
	bool checkPlayed(Card&);
	int pairs();
	int run();
	void resetTotal();
	void sortCards(Deck&);
	bool pegging();
	int playCard(Deck&);
	void printCards(Deck&);
	int calculate(Card&);
};

