//-----------------------------------------------------------------------------
// List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj{
   ListElement data;
   Node next;
   Node prev;
   int index;
} NodeObj;

// private QueueObj type
typedef struct ListObj{
   Node front;
   Node back;
   int cursor;
   int length;
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(ListElement data){
   Node N = malloc(sizeof(NodeObj));
   assert( N!=NULL );
   N->data = data;
   N->next = NULL;
   N->prev = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// newList()
// Returns reference to new empty List object.
List newList(){
   List L;
   L = malloc(sizeof(ListObj));
   assert( L!=NULL );
   L->front = L->back = NULL;
   L->cursor = -1;
   L->length = 0;
   return(L);
}

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL){
   if(pL!=NULL && *pL!=NULL) { 
      while( length(*pL) > 0) { // while still elements in there
        deleteBack(*pL); 		 
      }
      free(*pQ);
      *pQ = NULL;
   }
}


// Access functions -----------------------------------------------------------

// length()
// Returns the length of L.
int length(Queue L){
   if( L==NULL ){
      printf("Queue Error: calling length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return(L->length);
}

// Returns index of cursor element if defined, -1 otherwise. 
int index(List L) {
   if( L==NULL ){
      printf("List Error: calling index() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return L->cursor == -1 ? -1 : L->cursor; // if cursor -1 return that else return cursor
}

// front()
// Returns the value at the front of L.
// Pre: length > 0
ListElement front(List L){
   if( L==NULL ){
      printf("List Error: calling front() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( length(L) == 0 ){
      printf("List Error: calling front() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   return(L->front->data);
}


// back()
// Returns the value at the back of L.
// Pre: length > 0
ListElement back(List L){
   if( L==NULL ){
      printf("List Error: calling back() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( length(L) == 0 ){
      printf("List Error: calling back() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   return(L->back->data);
}


// get()
// Returns the value at the cursor of L.
// Pre: length > 0, index() >= 0
ListElement get(List L){
   if( L==NULL ){
      printf("List Error: calling get() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( length(L) == 0 ){
      printf("List Error: calling get() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   if( index(L) < 0 ){ // if cursor index is undefined i.e. -1 exit the program
      printf("List Error: calling get() on a List with an undefined cursor\n"); 
      exit(EXIT_FAILURE);
   }
   return(L->back->data);
}


// Returns true iff Lists A and B are in same                              
// state, and returns false otherwise.
bool equals(List A, List B) {
   if (length(A) != length(B)) { // not same length FALSE
      return false;
   }
   if (index(A) != index(B)) { // diff cursor diff state FALSE
      return false;
   }
   List tA = A; // create copies
   List tB = B; // ^^^
   moveBack(tA); // move cursor to end
   moveback(tB); // ^^^
   while ( !(index(tA) < 0) ) { // while cursor is defined
      if (get(tA) != get(tB)) { // see if the elemnts are equivalent
         return false; // if not return false
      }
      movePrev(tA); // continue to move towards front 
      movePrev(tB); // ^^^
   }
   return true; // iff same length, same cursor index, same elements in same spots, they're equivalent

}


// Manipulation procedures ---------------------------------------------------- 

// Resets L to its original empty state. 
