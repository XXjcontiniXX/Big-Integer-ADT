#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<assert.h>
#include"Matrix.h"
     
int main(int argc, char* argv[]){
	Matrix M = newMatrix(3);
	Matrix Mp = newMatrix(3);
	//assert(size(M) == 3);
   changeEntry(M, 1, 1, 3);
	changeEntry(M, 2, 1, 3);
	changeEntry(M, 1, 2, 3);
	changeEntry(M, 2, 2, 3);
   changeEntry(Mp, 1, 1, 3);
	changeEntry(Mp, 2, 1, 3);
   changeEntry(Mp, 1, 2, 3);
	changeEntry(Mp, 1, 3, 3);
	changeEntry(Mp, 2, 3, 4);
   //changeEntry(Mp, 2, 2, 3);
	printMatrix(stdout, M);
	printf("\n");
	printMatrix(stdout, Mp);
	printf("\ntheir sum:\n");
	Matrix S = sum(M, Mp);
	printMatrix(stdout, S);
	
	//assert(NNZ(M) == 3);
	//printMatrix(stdout, M);
	//printf("\n");
	//printMatrix(stdout, scalarMult(3, M));
	return 0;
}
