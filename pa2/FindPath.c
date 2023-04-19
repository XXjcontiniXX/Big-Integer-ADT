/*
1909086
pa1
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
	
	//bool init = false;
	bool print = false;
	List L = newList();
   while( fgets(line, MAX_LEN, in) != NULL)  {
		
		sscanf(line, "%d %d", &source, &destination);
		
		//printf("source: %d, destination: %d", source, destination);
		
		if ( source + destination == 0) {
			if (print == true) {
				return 0;
			}
			print = true;
			printGraph(out, G);
			fprintf(out, "\n");
			continue;
		}
	
		if (!print) {
			addEdge(G, source, destination);
		}
		
		if (print) {
			BFS(G, source);
			getPath(L, G, destination);
			fprintf(out, "The distance from %d to %d is ", source, destination);
			if ( length(L) - 1 == 0 ) {
				fprintf(out, "infinity\n");
				fprintf(out, "No %d-%d path exists\n", source, destination);
			}else{
				fprintf(out, "%d\n", length(L) - 1);
				fprintf(out, "A shortest %d-%d path is: ", source, destination);
				printList(out, L);
				fprintf(out, "\n");
			}
		
			fprintf(out, "\n");		
			clear(L);
		}
			// when 0 0 occurs, we have to switch from addEdging to BFS and getPath
	}
	return 0;
}
