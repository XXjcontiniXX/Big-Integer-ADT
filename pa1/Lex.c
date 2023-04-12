/*
James Contini
1909086
pa1   
*/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<assert.h>
#include<stdint.h>
#include"List.h"

#define MAX_LEN 300

int main(int argc, char* argv[]){ 
   int line_count;
   FILE *in, *out;
   char line[MAX_LEN];
// char tokenBuffer[MAX_LEN];
  // char* token;
   char** strarr;

   // check command line for correct number of arguments
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

   // read each line of input file, then count and print tokens
   line_count = 0;
   while( fgets(line, MAX_LEN, in) != NULL)  {
      line_count++;
   }
   rewind(in);

   strarr = malloc(line_count * sizeof(char*));
   uint32_t i = 0;
   while( fgets(line, MAX_LEN, in) != NULL)  {
      strarr[i] = (char*)malloc(strlen(line) + 1);
      strcpy(strarr[i], line);
      i++;
   }

   List L = newList();
   int opt = -1;
   for (int i = 0; i < line_count; i++) {
      /*printf("Line: %d\n",i);
      if (i == 3){
      	printList(stdout, L);
	printf("index(L): %d\n", index(L));
      }*/
      if ( length(L) > 0 ) {
         while ( index(L) != -1 && strcmp(strarr[i], strarr[get(L)] ) > 0 ) { // line were on comes after or with cursor
            moveNext(L);
	    opt = 1;
	    if ( index(L) == -1 ) {
	       break;
	    }
	 } 

         while ( opt != 1 && strcmp(strarr[i], strarr[get(L)]) < 0 ) { // line were on comes before or with cursor
            movePrev(L);
	    opt = 0;
	    if ( index(L) == -1 ) {
	       break;
	    }
	 }
	 
	 if (opt == -1) {
	    insertAfter(L, i);
	    opt = -1;
	    continue;
	 }

         if( opt == 0 && index(L) == -1 ) {
            prepend(L, i);
	    opt = -1;
	    moveBack(L);
            continue;
         }
 
         if ( opt == 0 && index(L) != -1 ) {
            insertAfter(L, i);
	    opt = -1;
            continue;
         }
	 if ( opt == 1 && index(L) == -1 ) {
	    append(L, i);
	    opt = -1;
	    moveFront(L);
	    continue;
	 }
	 if ( opt == 1 && index(L) != -1 ) {
	    insertBefore(L, i);
	    opt = -1;
	    continue;
	 }
	 fprintf(stderr, "how did we get here?\n");
	 exit(EXIT_FAILURE);

      }else{
         append(L, i);
         moveFront(L);
      }            
   }
   moveFront(L);
   while (index(L) != -1) { 
      fprintf(out, "%s", strarr[get(L)]);
      moveNext(L);
   }
   
   freeList(&L);
   for (int i = 0; i < line_count; i++) { 
      free(strarr[i]);
   }
   free(strarr);

   // close files 
   fclose(in);
   fclose(out);

   return(0);
}
