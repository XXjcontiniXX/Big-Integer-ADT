// James Contini
// jcontini
// pa4
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<assert.h>
#include"Matrix.h"
     
int main(int argc, char* argv[]){
	/*	
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
	*/
	
	Matrix P = newMatrix(3);
	changeEntry(P, 1, 2, 3);
	changeEntry(P, 1, 3, 3);
	changeEntry(P, 2, 3, 3);
	//changeEntry(P, 3, 1, 3);
   //changeEntry(P, 3, 2, 3);
   //changeEntry(P, 2, 1, 3);

	Matrix Pl = newMatrix(3);
	changeEntry(Pl, 3, 1, 3);
   changeEntry(Pl, 3, 2, 3);
   changeEntry(Pl, 2, 1, 3);
	//changeEntry(Pl, 1, 2, 3);
   //changeEntry(Pl, 1, 3, 3);
   //changeEntry(Pl, 2, 3, 3);
	//modEntry(Pl, 'a', 2, 1, 4);	

	printMatrix(stdout, P);
	printf("\n");
	printMatrix(stdout, Pl);
	printf("\n");
	Matrix Pm = diff(P, Pl);
	printMatrix(stdout, Pm);

	freeMatrix(&P);
	freeMatrix(&Pl);
	freeMatrix(&Pm);
	
	//printMatrix(stdout, transpose(P));
	//assert(NNZ(M) == 3);
	//printMatrix(stdout, M);
	//printf("\n");
	//printMatrix(stdout, scalarMult(3, M));
	return 0;
}
