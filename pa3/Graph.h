/*
 * James Contini
 * jcontini
 * pa3
 * */
//-----------------------------------------------------------------------------
// Graph.h
// Implementation file for Graph (DFS) ADT
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "List.h"

#define UNDEF 0
#define INF -1
#define NIL 0
#define white 0
#define gray 1
#define black 2


typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);

/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u);     /* Pre: 1<=u<=n=getOrder(G) */
int getDiscover(Graph G, int u);   /* Pre: 1<=u<=n=getOrder(G) */ 
int getFinish(Graph G, int u);   /* Pre: 1<=u<=n=getOrder(G) */ 

/*** Manipulation procedures ***/
void addEdge(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */
void addArc(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */ 
void DFS(Graph G, List S); /* Pre: length(S)==getOrder(G) */ 

/*** Other operations ***/
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);
