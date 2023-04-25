/*
 * James Contini
 * jcontini
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
   int* p; // parent
   int* d; // discover time
   int order; // # of verticies
   int size; // # of edges
   int* f; // finish time
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
	G->wgb = (uint8_t*)calloc(sizeof(uint8_t), (n + 1));
	G->p = (int*)calloc(sizeof(int), (n + 1));
	G->d = (int*)calloc(sizeof(int), (n + 1));
	G->f = (int*)calloc(sizeof(int), (n + 1));
	G->order = n;
	G->size = 0;
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
	free((*pG)->f);
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

int getSize(Graph G) {
	if (G == NULL) {
      printf("Graph Error: calling getSize() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
	return G->size;
}

int getParent(Graph G, int u) { /* Pre: 1<=u<=n=getOrder(G) */
	if (G == NULL) {
      printf("Graph Error: calling getParent() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
	if ( !(u > 0 && u <= getOrder(G)) ) {
      printf("Graph Error: calling getParent() with an invalid vertex\n");
      exit(EXIT_FAILURE);
   }
	return (G->p)[u];
}

int getDiscover(Graph G, int u) { /* Pre: 1<=u<=n=getOrder(G) */
	if (G == NULL) {
      printf("Graph Error: calling getDiscover() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
	if ( !(u > 0 && u <= getOrder(G)) ) {
      printf("Graph Error: calling getDiscover() with an invalid vertex\n");
      exit(EXIT_FAILURE);
   }
	return (G->wgb)[u] == black ? (G->d)[u] : UNDEF; 
}

int getFinish(Graph G, int u) {   /* Pre: 1<=u<=n=getOrder(G) */
	if (G == NULL) {
      printf("Graph Error: calling getFinish() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if ( !(u > 0 && u <= getOrder(G)) ) {
      printf("Graph Error: calling getFinish() with an invalid vertex\n");
      exit(EXIT_FAILURE);
   }
	return (G->wgb)[u] == black ? (G->f)[u] : UNDEF;
}

void addEdge(Graph G, int u, int v) {
	if (G == NULL) {
      printf("Graph Error: calling addEdge() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
	addArc(G, u, v);
	addArc(G, v, u);
	G->size -= 1;
	return;
}


void addArc(Graph G, int u, int v) {
	if (G == NULL) {
      printf("Graph Error: calling addEdge() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
	
	List uList = G->adj[u];
	moveFront(uList);

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
	G->size += 1;
}

void visit(Graph G, int x, int* time) {
   (G->d)[x] = (++(*time)); // incremented then displayed
   (G->wgb)[x] = gray;
   List adj = (G->adj)[x]; // caching adj List
   moveFront(adj);
   while ( index(adj) != -1 ) {
      if ( (G->wgb)[get(adj)] == white ) {
         (G->p)[get(adj)] = x;
         visit(G, get(adj), time);
      }
      moveNext(adj);
   }
   (G->wgb)[x] = black;
   (G->f)[x] = (++(*time));
}

void DFS(Graph G, List S) {
	if ( length(S) != getOrder(G) ) {
      printf("Graph Error: calling DFS() with an incompatible vertex list\n");
      exit(EXIT_FAILURE);
	}

	moveFront(S);
	while ( index(S) != -1 ) {
		(G->wgb)[get(S)] = white;
		(G->p)[get(S)] = NIL;
		moveNext(S);
	}

	int time = 0;
	moveBack(S);
	while ( index(S) != -1 ) {
		if ( (G->wgb)[front(S)] == white ) {
			visit(G, front(S), &time);			
		}
		deleteFront(S);
	}
	
	for (;time > 0; time -= 1) { // in decreasing finishing time order
		for (int i = 1; i <= getOrder(G); i++) { // look through the verticies
			if (getFinish(G, i) == time) { // if that vertex has the current time were on append it, then go next
				append(S, i);
				break;
			}
		}
	}


}

/*** Other operations ***/ ///////////// might have issue with addArc because a precon prevents adding a self arc
Graph transpose(Graph G) {
	if (G == NULL) {
      printf("Graph Error: calling transpose() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
	Graph F = newGraph(getOrder(G));
	for (int i = 1; i <= getOrder(G); i++) { // for all verticies in G
		List i_adj_list = (G->adj)[i]; // cache adj list of vertex i
		moveFront(i_adj_list); // starting at adj vertex 1 of i
		while ( index(i_adj_list) != -1 ) { // loop over all adj verticies of i
			addArc(F, get(i_adj_list), i);// add arc from adj vertexes to i in Graph F
			moveNext(i_adj_list); 
		}
	}
	return F; 
}
/*
Graph copyGraph(Graph G) {
	
}
*/
void printGraph(FILE* out, Graph G) {
	for (int i = 1; i <= getOrder(G); i++) {
		fprintf(out, "%d: ", i);
		if ( length(G->adj[i]) > 0 ) {
			printList(out, G->adj[i]);
		}
		fprintf(out, "\n");
   }
	return;
}
