#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include"List.h"

#define MAX_LEN 300

int main(int argc, char* argv[]){ 
   int token_count, line_count;
   FILE *in, *out;
   char line[MAX_LEN];
   char tokenBuffer[MAX_LEN];
   char* token;

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
   
   while( fgets(line, MAX_LEN, in) != NULL)  {
      line_count++;
   }

   // close files 
   fclose(in);
   fclose(out);

   return(0);
}
