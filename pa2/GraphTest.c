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
	addEdge(G, 1, 5);
	addEdge(G, 5, 1);
	BFS(G, 2);
	//addEdge(G, 4, 5);
	printGraph(stdout, G);
	freeGraph(&G);
	return 0;
}

