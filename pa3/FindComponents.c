/*
jcontini
pa3
James Contini
*/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<assert.h>
#include<stdint.h>
#include"Graph.h"
#define MAX_LEN 300

int main(int argc, char* argv[]){
  // int line_count;
   FILE *in, *out;
   char line[MAX_LEN];
   int source;
   int destination;

   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // open files for reading and writing
   in = fopen(argv[1], "r");
      if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }

   out = fopen(argv[2], "w");
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

   Graph G;

   while( fgets(line, MAX_LEN, in) != NULL )  {
      //printf("line: %s\n", line);
      G = newGraph(atoi(line));
      break;
   }
   
	while( fgets(line, MAX_LEN, in) != NULL)  {
		sscanf(line, "%d %d", &source, &destination);
		if (source + destination == 0) {
         break;
      }
		//printf("source: %d, destination: %d", source, destination);
		addArc(G, source, destination);
   }

	List L = newList();
	List T = newList();
   for (int i = 1; i <= getOrder(G); i++) {
      append(L, i);
   }
   DFS(G, L);
   Graph Gt = transpose(G);
   DFS(Gt, L);
	
	fprintf(out, "Adjacency list representation of G:\n");
	printGraph(out, G);
	fprintf(out, "\n");	

	int comp_num = 0;
	moveBack(L);
	while ( index(L) != -1 ) {
		if ( getParent(Gt, (int)get(L)) == NIL) {
			comp_num += 1;
		}
		movePrev(L);
	}
	moveBack(L);

	fprintf(out, "G contains %d strongly connected components:\n", comp_num);
	for (int i = 1; i <= comp_num; i++) {
		fprintf(out, "Component %d: ", i);
		clear(T);
		
		while ( index(L) != -1 ) {
			prepend(T, get(L));
      	if ( getParent(Gt, (int)get(L)) == NIL) {
				printList(out, T);
				printf("get(L) = %d\n", get(L));
				fprintf(out, "\n");
				movePrev(L);
				break;
			}
      	movePrev(L);
   	}	
	}

	freeGraph(&Gt);
	freeGraph(&G);
	freeList(&L);
	freeList(&T);
	return 0;
   // start from moveBack and movePrev until getParent() is NIL then the tree is don	
}
