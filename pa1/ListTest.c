//-----------------------------------------------------------------------------
// ListTest.c
// Another test client for Queue ADT
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"

int main(int argc, char* argv[]){
	List L = newList();
	append(L, 1);
	append(L, 2);
	append(L, 3);
	append(L, 4);
	append(L, 5);
	append(L, 6);
	prepend(L, 0);
	moveBack(L,
	printList(stdout, L);
}
