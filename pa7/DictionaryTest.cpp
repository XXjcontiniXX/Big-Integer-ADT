#include <iostream>
#include "Dictionary.h"

using namespace std;



int main () {
	Dictionary A = Dictionary();
	A.setValue("b", 0);
	A.setValue("a", 0);
	A.setValue("c", 0);
	A.setValue("d", 0);
	A.setValue("e", 0);
	cout << A;
	return 0;
}
