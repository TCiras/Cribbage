/*************
Thaddeus Ciras
cribFuns.cpp
*************/

#include "crib.h"

/*
	Constructor
*/
Crib::Crib(){
	belong = 0;
}

/*
	Print Function wrapper for unique headder
*/
void Crib::printCrib(){
	cout << endl << endl << "The crib contains:" << endl;
	print();
}
