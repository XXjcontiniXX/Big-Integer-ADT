// James Contini
// jcontini
// pa4
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "Matrix.h"
#include "List.h"
#include <assert.h>

typedef struct EntryObj* Entry;

typedef struct EntryObj {
	int r;
	int c;
	double val;
} EntryObj;

typedef struct MatrixObj {
	List* lists; // array of lists
	int dim; // dimension
	int nze;	// non zero entries
} MatrixObj;


void printEntry(FILE* out, Entry E);
double vectorDot(List P, List Q);

Entry newEntry(double val, int r, int c) {
   Entry E = (Entry)malloc(sizeof(EntryObj));
   if (E == NULL) {fprintf(stderr, "Entry Error: newEntry allocation failed"); exit(EXIT_FAILURE);}
	E->val = val;
   E->r = r;
   E->c = c;
   return E;
}

// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n) {
	Matrix M = (Matrix)malloc(sizeof(MatrixObj));
	if (M == NULL) {fprintf(stderr, "Matrix Error: newMatrix allocation failed"); exit(EXIT_FAILURE);}
	M->lists = (List*)malloc(n*sizeof(List));
	for (int i = 0; i < n; i += 1) {
		(M->lists)[i] = newList();
	}
	M->nze = 0;
	M->dim = n;
	return M;
}

// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM) {
	for (int i = 0; i < (*pM)->dim; i += 1) {
		freeList( &(((*pM)->lists)[i]) );
	}
	free((*pM)->lists);
	free(*pM);
	*pM = NULL;
	return;
}
// Access functions
// size()
// Return the size of square Matrix M.
int size(Matrix M) {
	if( M==NULL ){
      printf("Matrix Error: calling size() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
   }
	return M->dim;
}
// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M) {
	if( M==NULL ){
      printf("Matrix Error: calling NNZ() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
   }
	return M->nze;
}

int entryCmp(Entry A, Entry B) {
	uint8_t r = ( (A->r) == (B->r) );
	uint8_t c = ( (A->c) == (B->c) );
   uint8_t val = ( (A->val) == (B->val) );
   if ( r + c + val < 3 ) { // if any condition is not
      return 0;
   }
	return 1;
}

int rowCmp(List A, List B) {
	moveFront(A);
	moveFront(B);
	if (length(A) - length(B) != 0) {
		return 0;
	}
	while (index(A) != -1) {
		Entry Aa = get(A);
		Entry Bb = get(B);
		if ( entryCmp(Aa, Bb) == 0 ) {
			return 0;
		}
		moveNext(A);
		moveNext(B);
	}
	return 1;
}

// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B) {
	if ( size(A) != size(B)) {
		return 0;
	}
   for (int i = 0; i < size(A); i++) {
      if ( !rowCmp( (A->lists)[i], (B->lists[i])) ) {
			return 0;
		}
	}
	return 1;
}
// Manipulation procedures
// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M) {
	if( M==NULL ){
      fprintf(stderr, "Matrix Error: calling makeZero() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
   }
	for (int i = 0; i < size(M); i++) {
		clear( ((M->lists)[i]) );
	}
	M->nze = 0;
}
// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x) {
	if( M==NULL ){
      fprintf(stderr, "Matrix Error: calling changeEntry() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
   }
	
	if( !(i > 0 && j > 0 && i <= size(M) && j <= size(M)) ){
      fprintf(stderr, "Matrix Error: calling changeEntry() with invalid row or column values\n");
      exit(EXIT_FAILURE);
   }

	Entry E = NULL;
	moveFront((M->lists)[i-1]);
	while ( index(M->lists[i-1]) != -1 ) {
		E = get((M->lists)[i-1]);	     // get Entry at some index of row_i	
		if ( j < E->c ) { // if j is immeidtaly behind first column # insertBefore
			if (x == 0) {return;} // if they wanna put a zero there tho do nothing
			insertBefore((M->lists)[i-1], newEntry(x, i, j));
			M->nze += 1;
			return;
		}	

		if ( (E->c) == j ) {   // if that Entry's column # is correct
			if (x == 0) {
				delete((M->lists)[i-1]); 
				M->nze -= 1; // for sure were down a nze cuz there are no zero entries
			}else{
				E->val = x;
			}
			return;
		}
		moveNext((M->lists)[i-1]);		  // moveNext() if wrong column
	}
	if (x == 0) {return;} // if we tryna put a zero in do nothing
	append((M->lists)[i-1], newEntry(x, i, j)); // if we never found the right c append it to end cuz we looked through every one and its not before
	M->nze += 1;
}

// Matrix Arithmetic operations
// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A) {
	Matrix M = newMatrix(size(A));
   Entry E = NULL;
   for (int i = 0; i < size(A); i++) {
      moveFront((A->lists)[i]);
      while ( index((A->lists)[i]) != -1 ) {
         E = get((A->lists)[i]);
         changeEntry(M, E->r, E->c, E->val); // reverse column and row but same val
         moveNext((A->lists)[i]);
      }
   }
   return M;

}
// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A) {
	Matrix M = newMatrix(size(A));
	Entry E = NULL;
	for (int i = 0; i < size(A); i++) {
		moveFront((A->lists)[i]);
		while ( index((A->lists)[i]) != -1 ) {
			E = get((A->lists)[i]);
			changeEntry(M, E->c, E->r, E->val); // reverse column and row but same val
			moveNext((A->lists)[i]);
		}
	}
	return M;
}

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A) {
	if( A==NULL ){
      fprintf(stderr, "Matrix Error: calling scalarMult() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
   }
	Entry Ea = NULL;
	Matrix M = newMatrix(size(A));
	for (int i = 0; i < size(A); i++) {
      moveFront((A->lists)[i]);
      while ( (index((A->lists)[i]) != -1) ) {
			Ea = get((A->lists)[i]);
			changeEntry(M, Ea->r, Ea->c, Ea->val * x);
         moveNext((M->lists)[i]);
			moveNext((A->lists)[i]);
      }
   }
	return M;
}

void modEntry(Matrix M, char o, int i, int j, double x) {
	if( M==NULL ){
      fprintf(stderr, "Matrix Error: calling modEntry() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
   }

   Entry E = NULL;    // E will cache every entry
   if ((M->lists)[i-1] == NULL) {
      fprintf(stderr, "Matrix Error: calling modEntry() on row that doesn't exist\n");
      exit(EXIT_FAILURE);
   } 
	
	if ( o == 'a') {
		x = x;	
	}
	if (o == 's') {
		x = x * (double)(-1);
	}

   moveFront((M->lists)[i-1]);
   while ( index(M->lists[i-1]) != -1 ) {
      E = get((M->lists)[i-1]);       // get Entry at some index of row_i
		if ( j < E->c ) {
			if (x == 0) {return;}
         insertBefore((M->lists)[i-1], newEntry(x, i, j));
         M->nze += 1;
         return;
      }
      if ( (E->c) == j ) {   // if entry exists combine them 
			if (E->val + x == 0) {
            delete((M->lists)[i-1]);
            M->nze -= 1; // for sure were down a nze cuz there are no zero entries
         }else{
            E->val = E->val + x;
         }
         return;
		}

      moveNext((M->lists)[i-1]);      // moveNext() if wrong column
   }
	if (x == 0) {return;}
   append((M->lists)[i-1], newEntry(x, i, j));
   M->nze += 1;
}

// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B) {
	if( A==NULL || B==NULL){
      fprintf(stderr, "Matrix Error: calling sum() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
   }
	if( size(A) != size(B) ){
      fprintf(stderr, "Matrix Error: calling sum() on Matricies of different dimensions\n");
      exit(EXIT_FAILURE);
   }
	Entry Ea = NULL;
	Entry Eb = NULL;
   Matrix M = newMatrix(size(A));
	if (A == B) {
		double sum = 0;
      for (int i = 0; i < size(A); i += 1) {
			moveFront((A->lists)[i]);
			while ( index((A->lists)[i]) != -1 ) {
         	Ea = get((A->lists)[i]);
				sum = (Ea->val)* (double)(2);
				changeEntry(M, Ea->r, Ea->c, sum);
				moveNext((A->lists)[i]);
      	}
   	}
		return M;
	}
	
   for (int i = 0; i < size(A); i++) {
		moveFront((A->lists)[i]);
		moveFront((B->lists)[i]);
		
		while ( index((A->lists)[i]) != -1 ) {
			Ea = get( (A->lists)[i] );
			changeEntry(M, Ea->r, Ea->c, Ea->val);
			moveNext((A->lists)[i]);
		}
		
      while ( index((B->lists)[i]) != -1 ) {
			Eb = get((B->lists)[i]);
			modEntry(M, 'a', Eb->r, Eb->c, Eb->val); // add entries together
			moveNext((B->lists)[i]);
      }

   }
   return M;

}
// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B) {
	if( A==NULL || B==NULL){
      fprintf(stderr, "Matrix Error: calling sum() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
   }
   if( size(A) != size(B) ){
      fprintf(stderr, "Matrix Error: calling sum() on Matricies of different dimensions\n");
      exit(EXIT_FAILURE);
   }
	
	if (A == B) {
		Matrix M = newMatrix(size(A));
		return M;
	}
   Entry Ea = NULL;
   Entry Eb = NULL;
   Matrix M = newMatrix(size(A));
	
	for (int i = 0; i < size(A); i++) {
      moveFront((A->lists)[i]);
      moveFront((B->lists)[i]);

      while ( index((A->lists)[i]) != -1 ) {
         Ea = get( (A->lists)[i] );
         changeEntry(M, Ea->r, Ea->c, Ea->val);
         moveNext((A->lists)[i]);
      }

      while ( index((B->lists)[i]) != -1 ) {
         Eb = get((B->lists)[i]);
         modEntry(M, 's', Eb->r, Eb->c, Eb->val); // add entries together
         moveNext((B->lists)[i]);
      }

   }
   return M;

}

// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B) {
	if( A==NULL || B==NULL){
      fprintf(stderr, "Matrix Error: calling product() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
   }
   if( size(A) != size(B) ){
      fprintf(stderr, "Matrix Error: calling product() on Matricies of different dimensions\n");
      exit(EXIT_FAILURE);
   }

	Matrix Bt = transpose(B);
	Matrix prod = newMatrix(size(A));
	double vdot;
	for (int i = 0; i < size(A); i += 1) {
		for (int j = 0; j < size(Bt); j += 1) {
			vdot = vectorDot((A->lists)[i], (Bt->lists)[j]);
			if ( vdot == 0 ) {continue;}
      	changeEntry(prod, i+1, j+1, vdot);
		}		
	}
	freeMatrix(&Bt);
	return prod;
}

double vectorDot (List L, List Q) {
	if (L == NULL) {
		return 0;
	} 
	if (Q == NULL ) {
		return 0;
	}
	moveFront(L);
	Entry El = NULL;
	Entry Eq = NULL;
	double sum = 0;	

	while ( index(L) != -1 ) {
		El = get(L); // start with first element of L
		moveFront(Q); // start at beginning of Q
		while ( index(Q) != -1 ) { 
			Eq = get(Q);
			if ( El->c == Eq->c ) { // if they are the same element
				sum += El->val * Eq->val;
				break;
			}
			moveNext(Q);
		}
		moveNext(L);
	}
	return sum;
} 
// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M) {
	for (int i = 0; i < size(M); i++) {
		if ( length((M->lists)[i]) == 0 ) {continue;}
      moveFront((M->lists)[i]);
		fprintf(out, "%d: ", i + 1);
		while( index((M->lists)[i]) != -1) {
			printEntry(out, get((M->lists)[i]));
			moveNext((M->lists)[i]);
      }
		fprintf(out, "\n");
   }
	return;
}


void printEntry(FILE* out, Entry E) {
	fprintf(out, "(%d, %.1lf) ", E->c, E->val);
}



