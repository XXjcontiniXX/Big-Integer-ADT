#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<assert.h>
#include"Matrix.h"
     
int main(int argc, char* argv[]){
	Matrix M = newMatrix(3);
	Matrix Mp = newMatrix(3);
	Matrix T1 = newMatrix(4);
	Matrix T2 = newMatrix(4);
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
	Matrix S = diff(M, Mp);
	printMatrix(stdout, S);
	makeZero(S);
	printMatrix(stdout, S);
	assert(!equals(S, Mp));

	changeEntry(T1, 1, 1, 3);
   changeEntry(T1, 2, 1, 3);
   changeEntry(T1, 1, 3, 3);
   changeEntry(T1, 2, 3, 3);
	
	changeEntry(T2, 1, 1, 3);
   changeEntry(T2, 2, 1, 3);
   changeEntry(T2, 1, 3, 3);
   changeEntry(T2, 2, 3, 3);
	assert(equals(T1, T2));
	//assert(NNZ(M) == 3);
	//printMatrix(stdout, M);
	//printf("\n");
	//printMatrix(stdout, scalarMult(3, M));
	return 0;
}
