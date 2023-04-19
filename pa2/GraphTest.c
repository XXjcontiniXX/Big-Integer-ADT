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
	int i, s, max, min, d, n=35;
   List  C = newList(); // central vertices 
   List  P = newList(); // peripheral vertices 
   List  E = newList(); // eccentricities 
	Graph F = NULL;
   // Build graph G 
   F = newGraph(n);
   for(i=1; i<n; i++){
      if( i%7!=0 ) addEdge(F, i, i+1);
      if( i<=28  ) addEdge(F, i, i+7);
   }
   addEdge(F, 9, 31);
   addEdge(F, 17, 13);
   addEdge(F, 14, 33);

   // Print adjacency list representation of G
   printGraph(stdout, F);

   // Calculate the eccentricity of each vertex 
   for(s=1; s<=n; s++){
      BFS(F, s);
      max = getDist(F, 1);
      for(i=2; i<=n; i++){
         d = getDist(F, i);
         max = ( max<d ? d : max );
      }
      append(E, max);
   }

   // Determine the Radius and Diameter of G, as well as the Central and 
   // Peripheral vertices.
   append(C, 1);
   append(P, 1);
   min = max = front(E);
   moveFront(E);
   moveNext(E);
   for(i=2; i<=n; i++){
      d = get(E);
      if( d==min ){
         append(C, i);
      }else if( d<min ){
         min = d;
         clear(C);
         append(C, i);
      }
      if( d==max ){
         append(P, i);
      }else if( d>max ){
         max = d;
         clear(P);
         append(P, i);
      }
      moveNext(E);
   }

   // Print results 
   printf("\n");
   printf("Radius = %d\n", min);
   printf("Central vert%s: ", length(C)==1?"ex":"ices");
   printList(stdout, C);
   printf("\n");
   printf("Diameter = %d\n", max);
   printf("Peripheral vert%s: ", length(P)==1?"ex":"ices");
   printList(stdout, P);
   printf("\n");

   // Free objects 
   freeList(&C);
   freeList(&P);
   freeList(&E);
	
	
	Graph G = newGraph(10);
   addEdge(G, 1, 2);
   addEdge(G, 1, 3);
   addEdge(G, 2, 4);
   addEdge(G, 3, 4);
   addEdge(G, 4, 2);
   addEdge(G, 4, 3);
   BFS(G, 1);
	assert(getOrder(G) != 4);
	assert(getParent(G, 2) == 1);
	List L = newList();
	getPath(L, F, 4);
	assert(length(L) == 8);
	printList(stdout, L);
	printf("\n");
	//printGraph(stdout, G);
	freeList(&L);
	freeGraph(&F);
	freeGraph(&G);
	return 0;
}

