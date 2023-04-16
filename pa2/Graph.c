/*
 * James Contini
 * 1909086
 * pa2
 * */
//-----------------------------------------------------------------------------
// Graph.c
// Implementation file for Graph ADT
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "Graph.h"

typedef struct GraphObj{
   List* adj; // an array of Lists, each List contains the neighbors of vertex i
   char* wgb; // vertex can take the form "w" "g" or "b"
   int* p; // predecessor
   int* d; // distance from s to vertex i
   int order; // # of verticies
   int size; // # of edges
   int s; // most recently used source
} GraphObj;

/*** Constructors-Destructors ***/
Graph newGraph(int n) {
	Graph G = (Graph)malloc(sizeof(GraphObj));
	assert(G != NULL);
	G->adj = (List*)malloc(sizeof(List)*(n + 1));
	(G->adj)[0] = NULL;
	for (int i = 1; i <= n; i++) {
		(G->adj)[i] = newList();
	}
	G->wgb = (char*)malloc(sizeof(char)*(n + 1));
	G->p = (int*)malloc(sizeof(int)*(n + 1));
	G->d = (int*)malloc(sizeof(int)*(n + 1));
	G->order = n;
	G->size = 0;
	G->s = NIL;
	return G;
}

void freeGraph(Graph* pG) {
	for (int i = 1; i <= getOrder(*pG); i++) { // dont wanna hit 0 :)
		freeList( &(((*pG)->adj)[i]) );
   }
	free(((*pG)->adj));
	free((*pG)->wgb);
	free((*pG)->p);
	free((*pG)->d);
	free(*pG);
	*pG = NULL;
}

/*** Access functions ***/
int getOrder(Graph G) {
	if (G == NULL) {
		printf("Graph Error: calling getOrder() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
	}
	return G->order;
}

int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);

/*** Manipulation procedures ***/
void makeNull(Graph G) {
	if (G == NULL) {
      printf("Graph Error: calling makeNull() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
	G->size = 0;
	for (int i = 1; i <= getOrder(G) + 1; i++) {
      clear((G->adj)[i]);
   }
	return;
}

void addEdge(Graph G, int u, int v) {
	if (G == NULL) {
      printf("Graph Error: calling addEdge() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }

	List uList = G->adj[u];
	List vList = G->adj[v];
	moveFront(uList);
	moveFront(vList);
	
	if ( length(uList) != 0 ) { // if 0 just append else
		while ( index(uList) != -1 && v > get(uList) ) { // we havent moved past or must continue 
			moveNext(uList); // move next
		}
		if (index(uList) == -1) { // if we moved past
			append(uList, v); // append v
		}else{
			if (v == get(uList)) {
         	return;
      	}
			insertBefore(uList, v); // if we never moved past, we just moved to our spot insert
		}
	}else{
		append(uList, v); // see above
	}
	
	if ( length(vList) != 0 ) { // parrallel logic
		while ( index(vList) != -1 && u > get(vList)) {
			moveNext(vList);
		}
		if (index(vList) == -1) {
         append(vList, u);
      }else{
         insertBefore(vList, u);
      }
		
	}else{
		append(vList, u);
	}
	
}

void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);

/*** Other operations ***/
void printGraph(FILE* out, Graph G) {
	for (int i = 1; i <= getOrder(G); i++) {
		if ( length(G->adj[i]) > 0 ) {
			fprintf(out, "%d: ", i);
			printList(out, G->adj[i]);
			fprintf(out, "\n");
		}
   }
	return;
}
