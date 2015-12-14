/*************
Thaddeus Ciras
cribFuns.cpp
*************/

#include "crib.h"

Crib::Crib(){
	belong = 0;
}

void Crib::printCrib(){
	cout << endl << endl << "The crib contains:" << endl;
	print();
}
