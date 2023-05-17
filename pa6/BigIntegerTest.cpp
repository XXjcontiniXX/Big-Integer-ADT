#include <iostream>
#include <string>
#include "BigInteger.h"
#include <cassert>

using namespace std;


int main () {
	BigInteger N = BigInteger("11122222222333333333444444444555555555666666666");
	BigInteger B = BigInteger("11122222222333333333444444444555555555666666666");	
	assert(!N.compare(B));
	
	BigInteger bigger = BigInteger("11122222222333333333444444444555555555666666662");
	BigInteger smaller = BigInteger("11122222222333333333444444444555555555666666661");
	
	cout << bigger.compare(smaller) << " this gotta be a -1 i think\n";
	
	
	cout << 	N;
	//BigInteger P = BigInteger(N);
	
	//cout << P;
	return 0;
}
