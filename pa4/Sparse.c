/*
jcontini
pa4
James Contini
*/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<assert.h>
#include<stdint.h>
#include"Matrix.h"
#define MAX_LEN 300

int main(int argc, char* argv[]){
// int line_count;
   FILE *in, *out;
   char line[MAX_LEN];
   int dim = 0;
   int loop1;
	int loop2;
	int row;
	int col;
	double val;

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

   while( fgets(line, MAX_LEN, in) != NULL )  {
		if (dim > 0) {
			break;
		}
		sscanf(line, "%d %d %d", &dim, &loop1, &loop2);
   }
	Matrix A = newMatrix(dim);
	Matrix B = newMatrix(dim);
	int i = 0;
	bool first = true;
	while( fgets(line, MAX_LEN, in) != NULL ) {
		sscanf(line, "%d %d %lf", &row, &col, &val);
		i += 1;
		if (i - 1 == loop1) {
			first = false;
			continue;
		}
		
		if (first) {
			changeEntry(A, row, col, val);
		}
		if (!first) {
			changeEntry(B, row, col, val);
		}
	}
	Matrix C, D, E, F, G, H, I, J;
	C = scalarMult(1.5, A);
	D = sum(A, B);
	E = sum(A, A);
	F = diff(B, A);
	G = diff(A,A);
	H = transpose(A);
	I = product(A, B);
	J = product(B, B);
	
	fprintf(out, "A has %d non-zero entries:\n", loop1);
	printMatrix(out, A);
	fprintf(out, "\n");

	fprintf(out, "B has %d non-zero entries:\n", loop2);
	printMatrix(out, B);
	fprintf(out, "\n");

	fprintf(out, "(1.5)*A =\n");
	printMatrix(out, C);
	fprintf(out, "\n");

	fprintf(out, "A+B =\n");
	printMatrix(out, D);
	fprintf(out, "\n");

   fprintf(out, "A+A =\n");
	printMatrix(out, E);
	fprintf(out, "\n");

   fprintf(out, "B-A =\n");
	printMatrix(out, F);
	fprintf(out, "\n");

	fprintf(out, "A-A =\n");
	printMatrix(out, G);
	fprintf(out, "\n");

   fprintf(out, "Transpose(A) =\n");
	printMatrix(out, H);
	fprintf(out, "\n");

   fprintf(out, "A*B =\n");
	printMatrix(out, I);
	fprintf(out, "\n");

	fprintf(out, "B*B =\n");
	printMatrix(out, J);
	fprintf(out, "\n");
	
	freeMatrix(&A);
	freeMatrix(&B);
	freeMatrix(&C);
	freeMatrix(&D);
	freeMatrix(&E);
	freeMatrix(&F);
	freeMatrix(&G);
	freeMatrix(&H);
	freeMatrix(&I);
	freeMatrix(&J);
	A = NULL;
	return 0;      
}
