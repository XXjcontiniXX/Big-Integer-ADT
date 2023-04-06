//-----------------------------------------------------------------------------
// Queue.c
// Implementation file for Queue ADT
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "Queue.h"

// private structs, functions and constants -----------------------------------

// InitialSize
static const int InitialSize = 10;

// QueueObj
typedef struct QueueObj{
   QueueElement* item;  // array of Queue items
   int physicalSize;    // current length of underlying array
   int length;          // number of items in this Queue
   int cursor;		// cursor
   int front;           // index of front element
   int back;            // index of back element
} QueueObj;

// doubleItemArray
// Doubles the physical size of the underlying array Q->item.
void doubleItemArray(Queue Q){
   int i;
   int newSize = 2*(Q->physicalSize);
   QueueElement* oldArray = Q->item;
   QueueElement* newArray = calloc(newSize, sizeof(QueueElement));
   assert( newArray!=NULL );

   for(i=0; i<Q->length; i++){
      newArray[i] = oldArray[(Q->front+i)%(Q->physicalSize)];
   }
   free(oldArray);

   Q->item = newArray;
   Q->physicalSize = newSize;
   Q->front = 0;
   Q->back = Q->length-1;
}


// Constructors-Destructors ---------------------------------------------------

// newQueue()
// Returns reference to new empty Queue object.
Queue newQueue(){
   Queue Q;
   Q = malloc(sizeof(QueueObj));
   assert( Q!=NULL );
   Q->item = calloc(InitialSize, sizeof(QueueElement));
   assert( Q->item!=NULL );
   Q->physicalSize = InitialSize;
   Q->cursor = -1;
   Q->length = 0;
   Q->front = 0;
   Q->back = -1;
   return(Q);
}

// freeQueue()
// Frees all heap memory associated with Queue *pQ, and sets *pQ to NULL.
void freeQueue(Queue* pQ){
   if(pQ!=NULL && *pQ!=NULL) { 
      free((*pQ)->item);
      free(*pQ);
      *pQ = NULL;
   }
}


// Access functions -----------------------------------------------------------

// getFront()
// Returns the value at the front of Q.
// Pre: !isEmpty(Q)

QueueElement front(Queue Q){
   if( Q==NULL ){
      printf("Queue Error: calling getFront() on NULL Queue reference\n");
      exit(EXIT_FAILURE);
   }
   if( length(Q) == 0 ){
      printf("Queue Error: calling getFront() on an empty Queue\n");
      exit(EXIT_FAILURE);
   }
   return Q->item[Q->front];
}

QueueElement back(Queue Q){
   if( Q==NULL ){
      printf("Queue Error: calling getFront() on NULL Queue reference\n");
      exit(EXIT_FAILURE);
   }
   if( length(Q) == 0 ){
      printf("Queue Error: calling getFront() on an empty Queue\n");
      exit(EXIT_FAILURE);
   }
   return Q->item[Q->back];
}

int index(Queue Q) {
   if( Q==NULL ){
      printf("Queue Error: calling getFront() on NULL Queue reference\n");
      exit(EXIT_FAILURE);
   }
   return Q->cursor;
}

int length(Queue Q){
   if( Q==NULL ){
      printf("Queue Error: calling getLength() on NULL Queue reference\n");
      exit(EXIT_FAILURE);
   }
   return(Q->length);
}

int get(Queue Q) {
   if( Q==NULL ) { // Exit if NULL 
      printf("Queue Error: calling getFront() on NULL Queue reference\n");
      exit(EXIT_FAILURE);
   }
   if( !(length(Q) > 0) ) { // Exit if length is 0 or lesser
      printf("Queue Error: calling getFront() on an empty Queue\n");
      exit(EXIT_FAILURE);
   }
   if ( !(Q->cursor => 0) ) {  // Exit if cursor is NOT >= 0
       printf("Queue Error: calling getFront() on an empty Queue\n");
      exit(EXIT_FAILURE);
   }
	return Q->item[Q->cursor];	
}

bool equals(Queue Q, Queue Q) {
	
}


// Manipulation procedures ----------------------------------------------------

// Enqueue()
// Places new data at the back of Q.
void Enqueue(Queue Q, QueueElement data)
{
   if( Q==NULL ){
      printf("Queue Error: calling Enqueue() on NULL Queue reference\n");
      exit(EXIT_FAILURE);
   }

   if( (Q->length)==(Q->physicalSize) ){
      doubleItemArray(Q);
   }
   Q->back = ((Q->back)+1)%(Q->physicalSize);
   Q->item[Q->back] = data;
   Q->length++;
}

// Dequeue()
// Deletes data at front of Q.
// Pre: !isEmpty(Q)
void Dequeue(Queue Q){
   if( Q==NULL ){
      printf("Queue Error: calling Dequeue() on NULL Queue reference\n");
      exit(EXIT_FAILURE);
   }
   if( isEmpty(Q) ){
      printf("Queue Error: calling Dequeue on an empty Queue\n");
      exit(EXIT_FAILURE);
   }

   Q->front = ((Q->front)+1)%(Q->physicalSize);
   Q->length--;
}


// Other Functions ------------------------------------------------------------

// printQueue()
// Prints a string representation of Q consisting of a space separated list 
// of ints to stdout.
void printQueue(Queue Q){
   if( Q==NULL ){
      printf("Queue Error: calling printQueue() on NULL Queue reference\n");
      exit(EXIT_FAILURE);
   }

   int i;
   for(i=0; i<Q->length; i++){
      printf(FORMAT" ", Q->item[(Q->front+i)%(Q->physicalSize)]);
   }
   printf("\n");
}

// equals()
// Returns true if A is same int sequence as B, false otherwise.
bool equals(Queue A, Queue B){
   if( A==NULL || B==NULL ){
      printf("Queue Error: calling equals() on NULL Queue reference\n");
      exit(EXIT_FAILURE);
   }

   int n, m, i;
   n = A->physicalSize;
   m = B->physicalSize;
   bool eq = (A->length == B->length);

   for(i = 0; eq && (i < A->length); i++){
      eq = ( A->item[(A->front+i)%n] == B->item[(B->front+i)%m] );
   }
   return eq;
}
