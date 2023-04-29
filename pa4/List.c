/*
 * James Contini
 * jcontini
 * pa4
 * */
//-----------------------------------------------------------------------------
// List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "Matrix.h"
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
   Node cursor;
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
   L->cursor = NULL;
   L->front = L->back = NULL;
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
      printf("List Error: calling length() on NULL List reference\n");
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
   return L->cursor == NULL ? -1 : L->cursor->index; // if cursor -1 return that else return cursor
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
   return(L->cursor->data);
}

/*
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
   if ((length(A) == 0) && (length(B) == 0)) {
   	return true;
   }
   if ((length(A) == 0) || (length(B) == 0)) { // if length a or b is zero and we know the lengths dont equal then its false
   	return false;
   }
	ListElement Ac = A->cursor;
	ListElement Bc = B->cursor;
   moveBack(A); // move cursor to end
   moveBack(B); // ^^^
   while ( index(A) != -1 ) { // while cursor is defined
      if ( !entryCmp(A, B) ) { // see if the elements are equivalent
         return false; // if not return false
      }
      movePrev(A); // continue to move towards front 
      movePrev(B); // ^^^
   }
	A->cursor = Ac;
	B->cursor = Bc;
   return true; // iff same length, same cursor index, same elements in same spots, they're equivalent

}
*/

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
void set(List L, ListElement x) {
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
   L->cursor->data = (ListElement)x;
   return;
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
   L->cursor = L->front;
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
   //printf("Printing L->back->index: %d\n", L->back->index);
   L->cursor = L->back;
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
   if( index(L) < 0 ){
      return;
   }
   if( index(L) == L->front->index ){
      L->cursor = NULL;
      return;
   }
   L->cursor = L->cursor->prev;
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
   if( index(L) < 0 ){
      return;
   }
   if( index(L) == L->back->index ){
      L->cursor = NULL;
      return;
   }
   L->cursor = L->cursor->next;
   return;
}

// Insert new element into L.  If L is non-empty,                               
// insertion takes place before front element.
void prepend(List L, ListElement x) {
	if( L==NULL ){
      printf("List Error: calling prepend() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
	Node N = newNode((ListElement)x);
   if ( length(L) == 0 ) {
      L->back = N;
      L->front = N;
      N->index = 0;
      L->length = 1;
      return;
   }	
	N->index = 0;
	N->next = L->front;
	N->prev = NULL;
	L->front->prev = N;
	L->front = N;

	int indexes = 1; // indexes is the index of the first node
	Node iter = L->front;
	while (iter->next != NULL) {
		iter->next->index += 1; // N's index becomes indexes
		iter = iter->next; // N is the next node
		indexes += 1; // indexes increments
	}
	L->length += 1;
	return;
}

// Insert new element into L.  If L is non-empty,                               
// insertion takes place after back element.
void append(List L, ListElement x){
   if( L==NULL ){
      printf("List Error: calling append() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   Node N = newNode((ListElement)x);

   if ( length(L) == 0 ) {
      L->back = N;
      L->front = N;
      N->index = 0;
      L->length = 1;
      return;         	   		
   }

   N->index = L->back->index + 1;
   N->prev = L->back;
   N->next = NULL;
   L->back->next = N;
   L->back = N;
  
   L->length += 1;
   return;
}

// Insert new element before cursor.                                     
// Pre: length()>0, index()>=0 
void insertBefore(List L, ListElement x) {
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
   N->prev = L->cursor->prev;
   N->next = L->cursor;
   L->cursor->prev->next = N;
   L->cursor->prev = N;
   Node iter = L->cursor;
	while ( iter != NULL) { // since "N" becomes "after", N->next n beyond need their index +1'd
		iter->index += 1;
		iter = iter->next;
	}
	L->length += 1;
	return;
}

// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, ListElement x) {
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
   if ( index(L) == L->back->index ) { // covers no N->next case
      append(L, x);
      return;
   }
	
   Node N = newNode((ListElement)x);
   N->index = index(L) + 1; // set the new node's index to the cursor
	N->prev = L->cursor; 
	N->next = L->cursor->next;
	L->cursor->next->prev = N;
	L->cursor->next = N;
   while ( N->next != NULL) { // since "N" becomes "after", N->next n beyond need their index +1'd
      N->next->index += 1;
	   N = N->next;
   }
   L->length += 1;
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
   if(length(L) == 1){
        freeNode(&(L->front));
        L->front = NULL;
        L->back = NULL;
        L->cursor = NULL;
        L->length = 0;
        return;
   }
   if ( (index(L) != -1) && (L->front->index == L->cursor->index) ) {
      L->cursor = NULL;
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
   if(length(L) == 1){
   	freeNode(&(L->front));
	L->front = NULL;
	L->back = NULL;
	L->cursor = NULL;
	L->length = 0;
	return;
   }

   if( (index(L) != -1) && (L->back->index == L->cursor->index) ){
      L->cursor = NULL;
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
		freeNode(&(L->front));
		L->front = NULL;
		L->back = NULL;
		L->cursor = NULL;
		L->length = 0;
		return;
	}
	if ( index(L) == 0 ) { // covers no N->prev case
      deleteFront(L);
		L->cursor = NULL;
      return;
   }
	if ( index(L) == L->back->index) { // covers no N->next case
      deleteBack(L);
		L->cursor = NULL;
      return;
   }

	L->cursor->prev->next = L->cursor->next;
	L->cursor->next->prev = L->cursor->prev;
	Node iter = L->cursor->next;
	freeNode(&(L->cursor));
	L->cursor = NULL;

	while ( iter != NULL) { // starting after front start decrementing indexes
      iter->index -= 1;
      iter = iter->next;
   }

	L->length = L->length - 1;
	return;
}

// Prints to the file pointed to by out, a                                      
// string representation of L consisting                                      
// of a space separated sequence of integers,                                     
// with front on left.
/*void printList(FILE* out, List L) {
   if( L==NULL ){
      printf("List Error: calling printList() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( length(L) < 1 ){
      printf("List Error: calling printList() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   Node N = L->front;
   do {
      fprintf(out, "%d ", (int)N->data);
      N = N->next;
   } while (N != NULL);
}

*/
// Returns a new List representing the same integer                          
// sequence as L. The cursor in the new list is undefined,                         
// regardless of the state of the cursor in L. The state                          
// of L is unchanged.
List copyList(List L) {
   if( L==NULL ){
      printf("List Error: calling copyList() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   List C = newList();

   if ( length(L) == 0 ) { // if length is 0 just return empty list
      C->length = 0;
      return C;
   }

	moveFront(L);
   while (index(L) != -1) {
      append(C, get(L)); // append node
      moveNext(L);
   }

   C->length = length(L);
   return C;
}


