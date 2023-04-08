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
void moveBack(List L)    
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

// Insert new element into L.  If L is non-empty,                               
// insertion takes place before front element.
void prepend(List L, int x) {
	if( L==NULL ){
      printf("List Error: calling prepend() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
	Node N = newNode((ListElement)x);
	N->index = 0;
	if ( length(L) > 0 ) {
		Node second = L->front;
		L->front = N;
		L->front->next = second; // front->second
		second->prev = L->front; // front-><-second
		
		N = L->front; // N is front node
		int indexes = N->index; // indexes is the index of the first node
		do { 
			N->index = indexes; // N's index becomes indexes
			N = N->next; // N is the next node
			indexes += 1; // indexes increments
		} while( N->next != NULL ); // checks that there will be a next node else break
	}else{
		L->front = N;
		L->back = N;
	}
	return;
}

// Insert new element into L.  If L is non-empty,                               
// insertion takes place after back element.
void append(List L, int x){
   if( L==NULL ){
      printf("List Error: calling append() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
	Node N = newNode((ListElement)x);
	N->index = L->back->index + 1;
   if ( length(L) > 0 ) {
      Node second = L->back;
      L->back = N;
      L->back->prev = second; // second<-back
      second->next = L->back; // second-><-back
   }else{
      L->back = N;
      L->front = N;
   }
   return;
}

// Insert new element before cursor.                                     
// Pre: length()>0, index()>=0 
void insertBefore(List L, int x) {
	if( L==NULL ){
      printf("List Error: calling insertBefore() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( length(L) < 1 ){
      printf("List Error: calling insertBefore() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   if( index(L) < 0 ){ // if cursor index is undefined i.e. -1 exit the program
      printf("List Error: calling insertBefore() on a List with an undefined cursor\n");
      exit(EXIT_FAILURE);
   }
	
	if ( index(L) == 0 ) { // covers no N->prev case
		prepend(L, x);
		return;
	}
	
	Node N = newNode((ListElement)x);
	N->index = index(L); // set the new node's index to the cursor
	Node after = L->front; // the current node on the cursor will become the after node
	while ( true ) {
		if ( after->index == index(L) ) {
			Node before = after->prev;
			N->next = after;
			N->prev = before;
			before->next = N;
			after->prev = N;
			while ( N->next != NULL) { // since "N" becomes "after", N->next n beyond need their index +1'd
				N->next->index += 1;
				N = N->next;
			}
		}
		after = after->next;
	}
	return;
}

// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int x) {
   if( L==NULL ){
      printf("List Error: calling insertAfter() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( length(L) < 1 ){
      printf("List Error: calling insertAfter() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   if( index(L) < 0 ){ // if cursor index is undefined i.e. -1 exit the program
      printf("List Error: calling insertAfter() on a List with an undefined cursor\n");
      exit(EXIT_FAILURE);
   }
	if ( index(L) == length(L) - 1; ) { // covers no N->next case
      append(L, x);
      return;
   }
	
   Node N = newNode((ListElement)x);
   N->index = index(L) + 1; // set the new node's index to the cursor
   Node before = L->front; // the current node on the cursor will become the after node
   while ( true ) {
      if ( before->index == index(L) ) {
         Node after = before->next;
         N->next = after;
         N->prev = before;
         before->next = N;
         after->prev = N;
         while ( N->next != NULL) { // since "N" becomes "after", N->next n beyond need their index +1'd
            N->next->index += 1;
				N = N->next;
         }
      }
      before = before->next;
   }
   return;
}

// Delete the front element. Pre: length()>0
void deleteFront(List L) {
	if( L==NULL ){
      printf("List Error: calling deleteFront() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
	if( length(L) < 1 ){
      printf("List Error: calling deleteFront() on an empty List\n");
      exit(EXIT_FAILURE);
   }
	Node second = L->front->next; // new second node, after front
	second->prev = NULL; // new first node has no prev
	freeNode(&(L->front)); // free the node we dont need
	L->front = second; // front is actually replaced
	L->front->index = 0; // front index set to 0
	Node N = L->front; 
	while ( N->next != NULL) { // starting after front start decrementing indexes
		N->next->index -= 1;
   	N = N->next;
   }
	L->length -= 1; // one less long
	return;
}

// Delete the back element. Pre: length()>0
void deleteBack(List L) {
	if( L==NULL ){
      printf("List Error: calling deleteBack() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
	if( length(L) < 1 ){
      printf("List Error: calling deleteBack() on an empty List\n");
      exit(EXIT_FAILURE);
   }
	Node second = L->back->prev; // second from back is back prev
   second->next = NULL; // new back node no longer has next
	second->index = L->back->index - 1; // new back node has index one less than old back
   freeNode(&(L->back)); // lets free old back now
   L->back = second; // back is actually new back now
	L->length -= 1; // one less long
	return;
}

// Delete cursor element, making cursor undefined.                            
// Pre: length()>0, index()>=0
void delete(List L) {
	if( L==NULL ){
      printf("List Error: calling delete() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( length(L) < 1 ){
      printf("List Error: calling delete() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   if( index(L) < 0 ){ // if cursor index is undefined i.e. -1 exit the program
      printf("List Error: calling delete() on a List with an undefined cursor\n");
      exit(EXIT_FAILURE);
   }
	
	// 3 cases, if delete on one element list clear(), if on end deleteBack(), if in start deleteFront() 
	if( length(L) == 1 ) { 
		clear(L);
		return;
	}
	if ( index(L) == 0 ) { // covers no N->prev case
      deleteFront(L);
      return;
   }
	if ( index(L) == length(L) - 1; ) { // covers no N->next case
      deleteBack(L);
      return;
   }
	
	Node N = L->front;
	while ( true ) {
		if ( index(L) == N->index ) {
			N->prev->next = N->next;
			N->next->prev = N->prev;
			while ( N->next != NULL) { // starting after front start decrementing indexes
      		N->next->index -= 1;
      		N = N->next;
   		}
			freeNode(&(N));
			break;
		}
		N = N->next;
	}
	L->length = L->length - 1;
	return;
}
