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
   int index;
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
   L->index = -1;
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
      free(*pL);
      *pL = NULL;
   }
}


// Access functions -----------------------------------------------------------

// length()
// Returns the length of L.
int length(List L){
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
   return L->index == -1 ? -1 : L->index; // if cursor -1 return that else return cursor
}

// front()
// Returns the value at the front of L.
// Pre: length > 0
ListElement front(List L){
   if( L==NULL ){
      printf("List Error: calling front() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( length(L) < 1 ){
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
   if( length(L) < 1 ){
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
   if( length(L) < 1 ){
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
   if( A==NULL ){
      printf("List Error: calling equals() on NULL List reference: A\n");
      exit(EXIT_FAILURE);
   }
	if( B==NULL ){
      printf("List Error: calling equals() on NULL List reference: B\n");
      exit(EXIT_FAILURE);
   }
	if (length(A) != length(B)) { // not same length FALSE
      return false;
   }
   if (index(A) != index(B)) { // diff cursor diff state FALSE
      return false;
   }
   List tA = A; // create copies
   List tB = B; // ^^^
   moveBack(tA); // move cursor to end
   moveBack(tB); // ^^^
   while ( !(index(tA) < 0) ) { // while cursor is defined
      if (get(tA) != get(tB)) { // see if the elements are equivalent
         return false; // if not return false
      }
      movePrev(tA); // continue to move towards front 
      movePrev(tB); // ^^^
   }
   return true; // iff same length, same cursor index, same elements in same spots, they're equivalent

}


// Manipulation procedures ---------------------------------------------------- 

// Resets L to its original empty state.
void clear(List L) {
   if( L==NULL){
      printf("List Error: calling clear() on NULL List reference\n");
      exit(EXIT_FAILURE);
	}
   while( length(L) > 0) { // while still elements in there
   	deleteBack(L); // delete until empty
   }
   return;
}

// Overwrites the cursor element’s data with x.                           
// Pre: length()>0, index()>=0
void set(List L, int x) {
   if( L==NULL ){
      printf("List Error: calling set() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( length(L) < 1 ){
      printf("List Error: calling set() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   if( index(L) < 0 ){ // if cursor index is undefined i.e. -1 exit the program
      printf("List Error: calling set() on a List with an undefined cursor\n");
      exit(EXIT_FAILURE);
   }
   Node N = L->front;
   while ( true ) { 
      if (N->index == index(L)) {
         N->data = (ListElement)x;
         break;
      }    
      N = N->next;
      if (N == NULL) {
         printf("List Error: calling set() on a List with cursor outside of list\n");
         exit(EXIT_FAILURE);
      }
   }
      
}

// If L is non-empty, sets cursor under the front element,                          
// otherwise does nothing.
void moveFront(List L) {
   if( L==NULL ){
      printf("List Error: calling moveFront() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( length(L) < 1 ){
      return;
   }
   L->index = 0; // sets to 0th element maybe this is incorrect i dont think so tho
   return;
}

// If L is non-empty, sets cursor under the back element,                          
// otherwise does nothing.
void moveBack(List L) {
   if( L==NULL ){
      printf("List Error: calling moveBack() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( length(L) < 1 ){
      return;
   }
   L->index = L->back->index;
   return;
}

// If cursor is defined and not at front, move cursor one                           
// step toward the front of L; if cursor is defined and at                           
// front, cursor becomes undefined; if cursor is undefined                           
// do nothing
void movePrev(List L) {
   if( L==NULL ){
      printf("List Error: calling movePrev() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( L->index < 0 ){
      return;
   }
   if( index(L) == L->front->index ){
      L->index = -1;
      return;
   }
   L->index = L->index - 1;
   return;
}

// If cursor is defined and not at back, move cursor one                           
// step toward the back of L; if cursor is defined and at                         
// back, cursor becomes undefined; if cursor is undefined                           
// do nothing
void moveNext(List L) {
   if( L==NULL ){
      printf("List Error: calling moveNext() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( L->index < 0 ){
      return;
   }
   if( index(L) == L->back->index ){
      L->index = -1;
      return;
   }
   L->index = L->index + 1;
   return;
}

