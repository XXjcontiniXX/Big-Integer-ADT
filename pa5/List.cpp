#include <iostream>
#include "List.h"
#include <stdexcept>

List::Node::Node(ListElement x) {
	data = x;
	next = nullptr;
	prev = nullptr;
}

List::List() {	
	frontDummy = new Node(-1); // set front sent to node(-1)
	backDummy = new Node(-1); // we cab access 
	frontDummy->next = backDummy;
   backDummy->prev = frontDummy;
	frontDummy->prev = nullptr;
	backDummy->next = nullptr;
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	pos_cursor = 0;
	num_elements = 0;
}

List::List(const List& L) { // List() is built-in constructor function por eso, we can
	frontDummy = new Node(-1); // set front sent to node(-1)
   backDummy = new Node(-1); // we cab access
   frontDummy->next = backDummy;
   backDummy->prev = frontDummy;
   frontDummy->prev = nullptr;
   backDummy->next = nullptr;
   beforeCursor = frontDummy;
   afterCursor = backDummy;
   pos_cursor = 0;
   num_elements = 0;
	
	Node* N = (L.frontDummy)->next;
	
	while ( N != L.backDummy ) {
		this->insertAfter(N->data); //  "this" is a pointer to the implicitly contructed new List
		this->moveNext();
		N = N->next;
	}
}

List::~List() { // "delete" calls this destructor then deallocates object so no need to do it inside
	clear();
	delete frontDummy;
	delete backDummy;
}

// Access functions --------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const{ // ohhh the reason for const is that this is an "access" function
	return(num_elements);  // we dont wanna change the object/instance its referring to
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const{
	if (length() <= 0) {
		throw std::length_error("List Error: Calling front() on an empty list.");
	}

	return(frontDummy->next->data);
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const{
	if (length() <= 0) {
      throw std::length_error("List Error: Calling back() on an empty list.");
   }
	return(backDummy->prev->data);
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const { // in this context, "this" is the same thing
	if (length() < 0) {
      throw std::length_error("List Error: Calling position() on an empty list.");
   }
	if (pos_cursor < 0) {
      throw std::length_error("List Error: Calling position() with when position is less than 0");
   }
	return pos_cursor;
	
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const {
	if ( position() >= length() ) { // if we try to peekNext when pos is on last element
      throw std::length_error("List Error: Calling peekNext() at the end of the list.");
   }
	return afterCursor->data;

}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const {
	if ( position() <= 0 ) { // if we try to peekPrev when pos is on first element
      throw std::length_error("List Error: Calling peekPrev() at the beginning of the list.");
 	}
	return beforeCursor->data;
}

// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear() {
	this->moveBack();
	while ( this->length() != 0 ) {
		this->eraseBefore();
	}
	return;
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront() {
	afterCursor = frontDummy->next;
	beforeCursor = frontDummy;
	pos_cursor = 0;
} 

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack() {
	afterCursor = backDummy;
	beforeCursor = backDummy->prev;
	pos_cursor = length();
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over.
// pre: position()<length()
ListElement List::moveNext() {
	if ( position() >= length() ) {
     throw std::length_error("List Error: Calling moveNext() at the end of the list.");
   }

	Node* newBefore = afterCursor;
	Node* newAfter = afterCursor->next;
	afterCursor = newAfter;
	beforeCursor = newBefore;
	pos_cursor += 1;

	return beforeCursor->data;

}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over.
// pre: position()>0
ListElement List::movePrev() {
	if ( position() <= 0 ) { // if we try to peekPrev when pos is on first element
      throw std::length_error("List Error: Calling movePrev() at the beginning of the list.");
   }
	Node* newBefore = beforeCursor->prev;
	Node* newAfter = beforeCursor;
	afterCursor = newAfter;
	beforeCursor = newBefore;
	pos_cursor -= 1;
	
	return afterCursor->data;
} 

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x) {
	Node* between = new Node(x);

   between->prev = beforeCursor;
   between->next = afterCursor;

   afterCursor->prev = between;
   beforeCursor->next = between;
   num_elements += 1;

	afterCursor = beforeCursor->next;
	return;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x) {
	Node* between = new Node(x);

   between->prev = beforeCursor;
   between->next = afterCursor;

   afterCursor->prev = between;
   beforeCursor->next = between;
   num_elements += 1;

	beforeCursor = afterCursor->prev;
	pos_cursor += 1;
	return;
} 

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x) {
	if (position() >= length()) {
      throw std::length_error("List: setAfter(): position() == length().");
   }
	afterCursor->data = x;
	return;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x) {
	if (position() <= 0) {
      throw std::length_error("List: setBefore(): at position 0.");
   }
	beforeCursor->data = x;
	return;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter() {
	if (position() >= length()) {
      throw std::length_error("List: eraseBefore(): position() == length().");
   }
		
	if (afterCursor == frontDummy || afterCursor == backDummy) {
      std::cout << "houston we have a problem\n";
   }	
	
   Node* newAfter = afterCursor->next;
   delete afterCursor;

   beforeCursor->next = newAfter;
   newAfter->prev = beforeCursor;
   afterCursor = newAfter;
   num_elements -= 1;

   return;


}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore() {
	if (position() <= 0) {
		throw std::length_error("List: eraseBefore(): at position 0.");
	}
	
	if (beforeCursor == frontDummy || beforeCursor == backDummy) {
		std::cout << "houston we have a problem\n";
	}
	
	Node* newBefore = beforeCursor->prev;
	delete beforeCursor;

	afterCursor->prev = newBefore;
	newBefore->next = afterCursor;
	beforeCursor = newBefore;
	pos_cursor -= 1;
	num_elements -= 1;
	
	return;
}


// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then
// returns the final cursor position. If x is not found, places the cursor
// at position length(), and returns -1.
int List::findNext(ListElement x) {
	while ( (length() != position()) ) {
		if (moveNext() == x) {
			return position();
		}
	}
	pos_cursor = length();
	return -1;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor
// at position 0, and returns -1.
int List::findPrev(ListElement x) {
	while ( (position() != 0) ) {
      if (movePrev() == x) {
         return position();
      }
   }
   pos_cursor = 0;
   return -1;
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost
// occurrance of each element, and removing all other occurances. The cursor
// is not moved with respect to the retained elements, i.e. it lies between
// the same two retained elements that it did before cleanup() was called.
void List::cleanup() {
	Node* og_bef = beforeCursor;
	Node* og_aft = afterCursor;
	int og_pos = position();
	for (int i = 0; i < length(); i+=1) {
		this->moveFront();
		for (int j = 0; j < i; j+=1) {
			moveNext();
		}
		ListElement key = moveNext();
		while ( position() != length() ) {
				if (moveNext() == key) {
					if (beforeCursor == og_bef) {
						og_bef = beforeCursor->prev;
					}else if (beforeCursor == og_aft) {
						og_aft = beforeCursor->next;
					}
					if (position() <= og_pos) {
						og_pos -= 1;
					}
					eraseBefore();
				}
		}
	}
	beforeCursor = og_bef;
	afterCursor = og_aft;
	pos_cursor = og_pos;
}

// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const {
	List newList;

	Node* N = (this->frontDummy)->next; // start at beginning of L
	Node* M = (L.frontDummy)->next;
	while( N != this->backDummy ) { // while we havent hit the back
		newList.insertAfter( N->data ); // insert into new list
		newList.moveNext(); // movenext in new list
		N = N->next; // get next node to copy in from L
	}

	while( M != L.backDummy ) { // while we havent hit the back
      newList.insertAfter( M->data ); // insert into new list
      newList.moveNext(); // movenext in new list
      M = M->next; // get next node to copy in from L
   }
	
	newList.moveFront();
	return newList; // returntd::cout << new list
}

// to_string()
// Returns a string representation of this List consisting of a comma
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const {
	List::Node* N = (this->frontDummy)->next;
   std::string s = "(";
	
   while (N != this->backDummy) {
      s += std::to_string(N->data);
      N = N->next;
		if (N != this->backDummy) {
			s += ", ";
		}else{
			s+= ")";
		}
   }
   return s;

}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const {
	return (*this == R);

}


// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ) {
	List::Node* N = (L.frontDummy)->next;
	int i = 0;
   while (N != L.backDummy) {
		if ( i == L.position() ) {
			stream << " |*" << i << "*| ";
		}else{
			stream << " |" << i << "| ";
		}
		i += 1;
      stream << N->data;
      N = N->next;
   }
	if ( i == L.position() ) { 
		stream << " |*" << i << "*| ";
	}else{
		stream << " |" << i << "| ";
	}
	
	stream << "\n";
	return stream;
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ) {
	if (A.length() != B.length()) {
		return 0;
	}
	
	List::Node* Na = (A.frontDummy)->next;
	List::Node* Nb = (B.frontDummy)->next;
	while (Na != A.backDummy) { // only need to iterate over one of them.
		if (Na->data != Nb->data) {
			return 0;
		}
		Na = Na->next;
		Nb = Nb->next;
	}
	return 1;
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ) {
	this->clear(); // clear the assignee
	this->moveFront();
	Node *N = (L.frontDummy)->next; // start at the front of the assigner

	while (N != L.backDummy) { // iterate over the assigner
		
		this->insertAfter(N->data); // insert into assignee
		this->moveNext(); // iterate over assignee
		N = N->next;	// iterate over assigner
	}
	return *this;
}




