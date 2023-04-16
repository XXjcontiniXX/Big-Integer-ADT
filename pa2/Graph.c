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
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>
#include "Graph.h"

typedef struct GraphObj{
   List* adj; // an array of Lists, each List contains the neighbors of vertex i
   uint8_t* wgb; // vertex can take the form "w" "g" or "b"
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
	G->wgb = (uint8_t*)malloc(sizeof(uint8_t)*(n + 1));
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
	for (int i = 1; i <= getOrder(G); i++) {
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
void BFS(Graph G, int s) {
	for (int i = 1; i <= getOrder(G); i++) {
		if ( i == s ) {continue;}
		(G->wgb)[i] = white;
		(G->d)[i] = INF;
		(G->p)[i] = NIL;
   }
	(G->wgb)[s] = gray;
	(G->d)[s] = 0;
   (G->p)[s] = NIL;
	List Q = newList(); // start the queue
	append(Q, s); // add source to the queue
	while ( length(Q) != 0 ) {
		int x = (int)front(Q); // dequeue front
		deleteFront(Q); // ^^
		List L = (G->adj)[x]; // cache x adj List
		moveFront(L); // start at beginning
		while ( index(L) != -1 ) { // while we havent seen every elemet in x adj List
			int y = get(L); // starting at y in x's L
			if ( (G->wgb)[y] == white ) { // this adj member hasnt been visited then
				(G->wgb)[y] = gray; //
				(G->d)[y] = (G->d)[x] + 1; // 
				(G->p)[y] = x; // 
				append(Q, y); // then append y to the queue to have its adj members peaked at 
			}
			moveNext(L); // lets check the next adj member and do it again
		}
		(G->wgb)[x] = black; // Do this full thing for every element in the graph, so ixnay this one
	}
	
	

}

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
