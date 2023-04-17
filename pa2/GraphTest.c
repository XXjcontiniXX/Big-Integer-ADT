/*
 * James Contini
 * 1909086
 * pa2
 * */
//-----------------------------------------------------------------------------
// GraphTest.c
// Test file for Graph ADT
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "Graph.h"


int main(int argc, char* argv[]) {
	Graph G = newGraph(10);	
	addEdge(G, 1, 2);
	addEdge(G, 1, 3);
	addEdge(G, 2, 4);
	addEdge(G, 3, 4);
	addEdge(G, 4, 2);
	addEdge(G, 4, 3);
	BFS(G, 1);
	List L = newList();
	getPath(L, G, 4);	
	printList(stdout, L);
	printf("\n");
	//printGraph(stdout, G);
	freeList(&L);
	freeGraph(&G);
	return 0;
}

