/*****************************************************************************************
 *
 * James Contini
 * 1909086
 * pa1
 * 
TestClient.c
*  Test client for List ADT
*****************************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include"List.h"

int main(int argc, char* argv[]){
   
   List A = newList();
   List B = newList();
   List C = NULL;
   int i;

   for(i=1; i<=20; i++){
      append(A,i);
      prepend(B,i);
   }
   printList(stdout,A); 
   printf("\n");
   printList(stdout,B); 
   printf("\n");

   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%d ", get(A));
   }
   printf("\n");
   for(moveBack(B); index(B)>=0; movePrev(B)){
	printf("%d ", get(B));
   }
   printf("\n");

   C = copyList(A);
   printf("%s\n", equals(A,B)?"true":"false");
   printf("%s\n", equals(B,C)?"true":"false");
   printf("%s\n", equals(C,A)?"true":"false");


   moveFront(A);
   for(i=0; i<5; i++) moveNext(A); // at index 5
   insertBefore(A, -1);            // at index 6
   for(i=0; i<9; i++) moveNext(A); // at index 15
   insertAfter(A, -2);
   for(i=0; i<5; i++) movePrev(A); // at index 10
   delete(A);
   printList(stdout,A);
   printf("\n");
   printf("%d\n", length(A));
   clear(A);
   printf("%d\n", length(A));
   printf("\n\nEnd provided tests\n\n");

   freeList(&A);
   freeList(&B);
   freeList(&C);

   /// ///
	////////////// Begin my tests.
	/// ///
	List L = newList();
	List F = newList();
	// Normal and defined cursor in the back
	
	prepend(L, 3);
        append(L, 4);
        prepend(L, 2);
        append(L, 5);
        prepend(L, 1);
	append(L, 6);
	//printList(stdout, L);
	append(F, 1);
	append(F, 2);
	append(F, 3);
	append(F, 4);
	append(F, 5);
	append(F, 6);
	
	//printList(stdout, C);

	assert(equals(F, L)); // undefined cursor

	moveFront(L);
	List Lcopy = copyList(L); // copy of L made
	assert(!(equals(F, L))); // cursor changed and asserting incorrectness
	
	//printList(stdout, L);
	//printList(stdout, Lcopy);

	assert(equals(Lcopy, L)); // asserting copy and L work

	moveBack(L);
	moveBack(F);
	printf("get(L): %d\n", get(L));
	assert(equals(F, L)); // cursor moved to same spot
	
	printList(stdout, L);
	printf("get(L) %d\n", get(L));
	set(L, 0);
	
	assert(!(equals(F, L))); // changing data

	set(F, 0);
	assert(equals(F, L)); // equalizing data
	
	// checking undefined feature in movePrev()
	for (int i = 0; i < 10; i++) {
		movePrev(L);
	}
	assert(index(L) == -1);
	moveFront(L); // moving cursor back
	
	for (int i = 0; i < 10; i++) {
                moveNext(L);
        }	
	assert(index(L) == -1);
	moveBack(L); // moving cursor backi
	set(L, 6);
	set(F, 6);
	printf("Passed moveNext() and movePrev() checks\n");

	//^^Quickly testing moveback and front works as designed for small case before rigourous testing
	printf("\n\n\n");
	printf("Rigorous testing beginning with these two lists:\n");
	printList(stdout, L);
	printList(stdout, F);
	List sL = newList(); 
	List sC = newList();  
	for (int i = 1; i < 16; i++) {
		append(sL, i);
	}
	for (int i = 1; i < 16; i++) {
		append(sC, i);
	}
	moveBack(sL);
	moveBack(sC);
	// Testing insertAfter() and insertBefore for defined cursor
		// insertAfter()
			// when cursor is L->back
			moveBack(L);
			for (int i = 7; i < 16; i++) {
				insertAfter(L, i);
				moveNext(L);
			}
			printList(stdout, sL);
			printf("\n");
			printList(stdout, L);
			printf("\n");
			assert(equals(sL, L)); //asserting equality
			
		// insertBefore
			// when cursor is L->front
			moveBack(F);
                        for (int i = 7; i < 16; i++) {
                                insertBefore(F, i);
                                movePrev(F);
                        }
			printList(stdout, F);
			printf("\n");
			printList(stdout, sC);
			printf("\n");
         assert(!(equals(sC, F))); // asserting inequality
	List X = newList();
	append(X, 1);
   append(X, 2);
   moveFront(X);
   delete (X);
   append(X, 3);
   append(X, 5);
   moveFront(X);
   insertAfter(X, 12);
   delete(X);
   printf("(should be 3) Length: %d\n", length(X));

	freeList(&X);
	freeList(&F);
	freeList(&L);
	freeList(&Lcopy);
	freeList(&sL);
	freeList(&sC);
	
   return(0);
}

/*
Output of this program:
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
false
false
true
1 2 3 4 5 -1 6 7 8 9 11 12 13 14 15 -2 16 17 18 19 20
21
0
*/
