#include <iostream>
#include "Dictionary.h"

using namespace std;



int main () {
	Dictionary A = Dictionary();
	Dictionary B = Dictionary();
	A.setValue("b", 0);
	A.setValue("a", 0);
	A.setValue("c", 0);
	A.setValue("d", 0);
	A.setValue("e", 0);
	cout << A;	
	B = A;
	//cout << "\n";
	//cout << B;
	B = Dictionary(B);
	cout << B;
	return 0;
}
