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
	BigInteger one = BigInteger("-9999999999"); 
	BigInteger two = BigInteger("1000000000000090000000000000");
	BigInteger twotwo = BigInteger("9999999999");
	cout << twotwo << "+\n" << two << "-\n" << twotwo << "\n" << "= " << twotwo.add(two.sub(twotwo)) << "\n";
	BigInteger fix = one.sub(two);
	cout << "\n\n";
	cout << "one - two\n";
	cout << one << "-\n" << two << "=\n" << fix << "\n";
	cout << "\n\n";
	cout << fix << "+\n" << twotwo << "=\n" << fix.add(twotwo) << "\n"; 

	cout << "\n\n\nBeginning subtract tests:\n";
	
	BigInteger four = BigInteger("1111111111111111111");
	BigInteger three = BigInteger("1111111111110000");	

	
	cout << three;
	cout << '-' << '\n';
	cout << four;
	BigInteger fourfour = three.sub(four);
   cout << "Subtraction: " << fourfour << "\n";
   cout << fourfour << "+\n" << four << "= \n" << four + fourfour; ///

	//assert(three.sub(four).add(four) == three); 	

	cout << "\n\n\nBeginning multiply tests:\n";

   BigInteger five = BigInteger("100000000");
   BigInteger six = BigInteger("100000000");


   cout << five;
   cout << '*' << '\n';
   cout << six;
	cout << "\n\n\n\n\n We are going to catch it here:\n";
	BigInteger var1 = BigInteger("1000000000000090000000000000");
   BigInteger var2 = BigInteger("9999999999");
	cout << var1 << "+\n" << var2;
	cout << "\n";
	BigInteger var3 = var2 + var1; //// 
	cout << "= " << var3;
	BigInteger var4 = var3.sub(var2);
	cout << "\n" << var3 << "-\n" << var2 << "= " << var4 << "whereas it should equal: " << var1;
	cout << "\n\n\n\n";
	cout << var2 << "\n+\n" << var2 << "=\n" << var2 + var2;
 	cout << "Multiply: " << five.mult(six) << "\n";
	//assert(smaller.sign() == 1);
	//cout << bigger.compare(smaller) << " this gotta be a -1 i think\n";
	/*cout << "\n\n\nseparate test\n";
	BigInteger test = BigInteger("100000000");
	BigInteger ans = BigInteger();
	for(long i = 0 ; i < 100000000; i += 1) {
		ans = ans + test;
		cout << ans;
	}
	*/
	//cout << 	N;
	//BigInteger P = BigInteger(N);
	
	//cout << P;
	return 0;
}
