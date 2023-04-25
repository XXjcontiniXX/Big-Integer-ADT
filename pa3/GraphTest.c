/*
 * James Contini
 * 1909086
 * pa3
 * */
//-----------------------------------------------------------------------------
// GraphTest.c
// Test file for Graph (DFS) ADT
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "Graph.h"


int main(int argc, char* argv[]) {
   Graph G = newGraph(8);
	addArc(G, 1, 2);
	addArc(G, 2, 3);
	addArc(G, 2, 5);
	addArc(G, 2, 6);
	addArc(G, 3, 4);
	addArc(G, 3, 7);
	addArc(G, 4, 3);
	addArc(G, 4, 8);
	addArc(G, 5, 1);
	addArc(G, 5, 6);
	addArc(G, 6, 7);
	addArc(G, 7, 6);
	addArc(G, 7, 8);
	addArc(G, 8, 8);
	//printGraph(stdout, G);

	List L = newList();
	for (int i = 1; i < 9; i++) {
		append(L, i);
	}
	DFS(G, L);
	//printList(stdout, L);	
	Graph Gt = transpose(G);
	Graph Gtt = copyGraph(Gt);
	/*printf("\n");
	printGraph(stdout, F);
	*/
	DFS(Gtt, L);
	printList(stdout, L); // L has the answer in it
	// start from moveBack and movePrev until getParent() is NIL then the tree is done
	return 0;
}	
