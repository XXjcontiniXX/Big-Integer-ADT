//-----------------------------------------------------------------------------
// ListTest.c
// Another test client for Queue ADT
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "List.h"
#include <assert.h>

int main(int argc, char* argv[]){
	List L = newList();
	List C = newList();
	// Normal and defined cursor in the back
	
	prepend(L, 3);
        append(L, 4);
        prepend(L, 2);
        append(L, 5);
        prepend(L, 1);
	append(L, 6);
	

	//printList(stdout, L);
	
	append(C, 1);
	append(C, 2);
	append(C, 3);
	append(C, 4);
	append(C, 5);
	append(C, 6);
	
	//printList(stdout, C);

	assert(equals(C, L)); // undefined cursor

	moveFront(L);
	List Lcopy = copyList(L); // copy of L made
	assert(!(equals(C, L))); // cursor changed and asserting incorrectness
	
	//printList(stdout, L);
	//printList(stdout, Lcopy);

	assert(equals(Lcopy, L)); // asserting copy and L work

	moveBack(L);
	moveBack(C);
	printf("get(L): %d\n", get(L));
	assert(equals(C, L)); // cursor moved to same spot
	
	printList(stdout, L);
	printf("get(L) %d\n", get(L));
	set(L, 0);
	
	assert(!(equals(C, L))); // changing data

	set(C, 0);
	assert(equals(C, L)); // equalizing data
	
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
	set(C, 6);
	printf("Passed moveNext() and movePrev() checks\n");

	//^^Quickly testing moveback and front works as designed for small case before rigourous testing
	printf("\n\n\n");
	printf("Rigorous testing beginning with these two lists:\n");
	printList(stdout, L);
	printList(stdout, C);
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
			printList(stdout, L);
			assert(equals(sL, L));
			
			// when cursor is L->front
			// when cursor is in the middle
		// insertBefore
			// when cursor is L->front
			moveBack(C);
                        for (int i = 7; i < 16; i++) {
                                insertBefore(C, i);
                                movePrev(L);
                        }
                        printList(stdout, sC);
                        printList(stdout, C);
                        assert(equals(sC, C));
			// when cursor is in the middle

	// Tesing insertAfter() and insertBefore for undefined

	
	


	freeList(&C);
	freeList(&L);
	freeList(&Lcopy);
	freeList(&sL);
	freeList(&sC);
	return 0;
}
