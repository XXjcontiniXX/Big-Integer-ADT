// James Contini
// jcontini
// Pa5

#include <iostream>
#include"List.h"
#include <assert.h>
using namespace std;


void shuffle(List& D);

int main(){ 
	List* A = new List();
	List* B = new List();
	A->insertAfter(1);
	cout << A->moveNext();
	A->insertAfter(2);
	cout << A->moveNext();
	A->insertAfter(3);
	
	B->insertBefore(1);
   cout << B->movePrev();
   B->insertBefore(2);
   cout << B->movePrev();
   B->insertBefore(3);
	
	cout << (*A);
	cout << (*B);

	A->clear();
	B->clear();
	////////////////	

	A->insertAfter(1);
   A->moveNext();
   A->insertAfter(2);
   A->moveNext();
   A->insertAfter(3);
	A->moveBack();

	A->setBefore(1);
	A->movePrev();
	A->setBefore(2);
   A->movePrev();
	A->setBefore(3);
   A->movePrev();
	
	cout << (*A);	
	(*B) = (*A);
	cout << (*B);
	
	assert((*A) == (*B));
	A->insertAfter(1);
	
	assert( !((*A) == (*B)) );
	
	A->clear();
	B->clear();
	///////////////
	cout <<	"\n\n\n\n";
	cout << "Begin complicated function tests:\n";
	A->moveFront();
	
	A->insertAfter(1);
   A->moveNext();
   A->insertAfter(2);
   A->moveNext();
   A->insertAfter(3);
   A->moveBack();	
	
	A->moveFront();
	cout << "\nfindNext test\n";	
	cout << A->findNext(3);
	cout << (*A);
	cout << "\nfindPrev test\n";
	cout << A->findPrev(1);
	cout << (*A);
	
	cout << "\ncleanup test\n";

	B->moveFront();

   B->insertAfter(1);
   B->moveNext();
   B->insertAfter(1);
   B->moveNext();
   B->insertAfter(3);
   B->moveNext();
   B->insertAfter(1);
   B->moveNext();
	B->insertAfter(5);
   B->moveNext();
	B->insertAfter(5);
   B->moveNext();
   B->insertAfter(3);
   B->moveNext();
   B->insertAfter(1);
   B->moveNext();
   B->insertAfter(3);
	B->moveNext();
	B->insertAfter(5);
   B->moveNext();
	B->moveFront();
	B->moveNext();
	
	cout << (*B);
	B->cleanup();
	cout << "cleaning up B\n";	
	cout <<(*B);

	A->clear();
	B->clear();
	//////////////
	A->insertAfter(1);
  	A->moveNext();
   A->insertAfter(2);
  	A->moveNext();
   A->insertAfter(3);

   B->insertBefore(1);
   B->movePrev();
   B->insertBefore(2);
   B->movePrev();
   B->insertBefore(3);
	cout << "print A then B\n";
	cout << (*A);
	cout << (*B);
	cout << "concating them\n";


	List C = (A->concat(*B));
	
	cout << (C); 

	cout << (int)(A->equals(*B));
	cout << "\nto_string function\n";
	cout << C.to_string();

	cout << "\n\n\nTesting shuffle now\n\n\n";
	A->clear();
	A->moveFront();
	
	A->insertAfter(0);
   A->moveNext();
	A->insertAfter(1);
   A->moveNext();
   A->insertAfter(2);
   A->moveNext();
   A->insertAfter(3);	
	A->moveNext();
   A->insertAfter(4);
   A->moveNext();
   A->insertAfter(5);
	A->moveNext();
   A->insertAfter(6);		
	A->moveNext();
   A->insertAfter(7);	

	cout << A->to_string();

	shuffle(*A);
	cout << "\n\n";	
	cout << A->to_string();
	cout << "\n";

	delete A;
	delete B;
	
	return 0;
}


void shuffle(List& D) {
   int size = D.length();
   ListElement key;
   for (int i = 0; i < size/2; i += 1) {
		D.moveFront();
      key = D.moveNext();
      D.eraseBefore();
      while (D.position() < size/2 + i) { // so position() will have hit the size/2 when loop is over
         D.moveNext();
         if (D.position() == size/2 + i) {
            D.insertBefore(key);
         }
      }
   }
}
