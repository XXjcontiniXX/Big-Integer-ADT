#include <iostream>
#include <string>
#include "BigInteger.h"
#include <cassert>

using namespace std;


int main () {
	BigInteger N = BigInteger("11122222222333333333444444444555555555666666666");
	BigInteger B = BigInteger("11122222222333333333444444444555555555666666666");	
	assert(!N.compare(B));
	
	BigInteger bigger = BigInteger("-11122222222333333333444444444555555555666666662");
	BigInteger smaller = BigInteger("11122222222333333333444444444555555555666666661");
	cout << "\n\n"	;
	BigInteger zero = BigInteger("-00001");
	BigInteger zeroer = BigInteger("-0000000000000000000000");
	//cout << zero << " above me is like 11 ones \n";
	cout << zero.sign() << endl;
	cout << zeroer.sign() << endl;
	assert(zero.compare(zeroer) == -1);

	// add tests //
	cout << "\n\n\nBeginning add tests:\n";
	BigInteger two = BigInteger("9999999999"); 
	BigInteger one = BigInteger("1000000000000090000000000000");
	cout << one;
	cout << '+' << '\n';
	cout << two;
	cout << "Addition: " << one.add(two) << "\n";

	cout << "\n\n\nBeginning subtract tests:\n";
	
	BigInteger four = BigInteger("1111111111111111111");
	BigInteger three = BigInteger("111111111");	

	
	cout << three;
	cout << '-' << '\n';
	cout << four;
	cout << "Subtraction: " << three.sub(four) << "\n";
	
	//assert(smaller.sign() == 1);
	//cout << bigger.compare(smaller) << " this gotta be a -1 i think\n";
	
	
	//cout << 	N;
	//BigInteger P = BigInteger(N);
	
	//cout << P;
	return 0;
}
