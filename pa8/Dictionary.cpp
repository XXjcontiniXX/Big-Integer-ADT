/*
James Contini
jcontini
pa8
*/

#include<iostream>
#include<string>
#include"Dictionary.h"

using namespace std;

   // Helper Functions (Optional) ---------------------------------------------
  	Dictionary::Node::Node(keyType k, valType v) {
		this->key = k;
		this->val = v;
		this->color = 0;
		this->parent = nullptr;
		this->left = nullptr;
		this->right = nullptr;
	}

	// inOrderString()
   // Appends a string representation of the tree rooted at R to string s. The
   // string appended consists of: "key : value \n" for each key-value pair in
   // tree R, arranged in order by keys.
   void Dictionary::inOrderString(std::string& s, Node* R) const {
		if ( R != nil && R != nullptr ) {
			inOrderString(s, R->left);
			string k = R->key;
			string v = std::to_string(R->val);
			s += k + " : " + v + "\n";
			inOrderString(s, R->right);
		}
   }

   // preOrderString()
   // Appends a string representation of the tree rooted at R to s. The appended
   // string will consist of keys only, with the order determined by a pre-order
   // tree walk. The keys stored in black Nodes will be appended as "key\n", and
   // the keys stored in red Nodes will be appended as "key (RED)\n". The output 
   // of this function is demonstrated in /Examples/pa8/DictionaryClient-out.  
   void Dictionary::preOrderString(std::string& s, Node* R) const {
		if ( R != nil && R != nullptr ) {
			if (R->color != 1) {
				s += R->key + "\n";
			}else{
				s += R->key + " (RED)" + "\n";
			}
			preOrderString(s, R->left);
			preOrderString(s, R->right);
		}
	   
   }

   // BST_insert()
   // Inserts a copy of the Node *M into this Dictionary. Used by preOrderCopy().
   void Dictionary::BST_insert(Node* M) {
		Node* y = nil;
      Node* x = this->root;
      while (x != nil && x != nullptr) {
			y = x;
         if ( M->key.compare(x->key) < 0 ) {
         	x = x->left;
         }else{
         	x = x->right;
			}
		}
		Node* z = new Node(M->key, M->val);
		z->left = nil;
		z->right = nil;
		z->color = M->color;
		z->parent = y;
      if (y == nil) {
      	this->root = z;    // tree T was empty
			this->root->parent = nil;
			this->num_pairs += 1;
      } else if ( M->key.compare(y->key) < 0 ) {
			if (y->left == nil) { this->num_pairs += 1;}
         	y->left = z;
      } else {
			if (y->right == nil) { this->num_pairs += 1;}
         	y->right = z;
		}
   }

   // preOrderCopy()
   // Recursively inserts a deep copy of the subtree rooted at R into this 
   // Dictionary. Recursion terminates at N.
   void Dictionary::preOrderCopy(Node* R, Node* N) {
		if ( R != N ) {
			this->BST_insert(R);
			preOrderCopy(R->left, N);
			preOrderCopy(R->right, N);
		}
	
   }

   // postOrderDelete()
   // Deletes all Nodes in the subtree rooted at R.
   void Dictionary::postOrderDelete(Node* R) {
	   if ( R != nil && R != nullptr ) {
         postOrderDelete(R->left);
         postOrderDelete(R->right);
		   delete R;
      }
		num_pairs = 0;
	   
   }

   // search()
   // Searches the subtree rooted at R for a Node with key==k. Returns
   // the address of the Node if it exists, returns nil otherwise.
   Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
	   if ( R == nil || R == nullptr) {
			return nil;	
		} else if ( k == R->key ) {
			return R;
		}else if ( k.compare(R->key) < 0 ) {
			return search(R->left, k);
		}else { // k > x.key
			return search(R->right, k);
		}
	   
   }

   // findMin()
   // If the subtree rooted at R is not empty, returns a pointer to the 
   // leftmost Node in that subtree, otherwise returns nil.
   Dictionary::Node* Dictionary::findMin(Node* R) {
		Node* x = R;
		if (x == nil) {
			return nil;
		}
		while (x->left != nil) {
      	x = x->left;
		}
		return x; 
   }

   // findMax()
   // If the subtree rooted at R is not empty, returns a pointer to the 
   // rightmost Node in that subtree, otherwise returns nil.
   Dictionary::Node* Dictionary::findMax(Node* R) {
	   Node* x = R;
      if (x == nil) {
         return nil;
      }
      while (x->right != nil) {
         x = x->right;
      }
      return x;
   }

   // findNext()
   // If N does not point to the rightmost Node, returns a pointer to the
   // Node after N in an in-order tree walk.  If N points to the rightmost 
   // Node, or is nil, returns nil. 
   Dictionary::Node* Dictionary::findNext(Node* N) {
	   	Node* x = N;
		
		if (x == nil || x == nullptr) {
			return nil;
		}
		
		if ( !(x->right == nil) ) {
			return this->findMin(x->right);
		}
		Node* y = x->parent;

		while ( !(y == nil) && y->right == x) { 
			x = y;
			y = y->parent;
		}
		return y;
   }

   // findPrev()
   // If N does not point to the leftmost Node, returns a pointer to the
   // Node before N in an in-order tree walk.  If N points to the leftmost 
   // Node, or is nil, returns nil.
   Dictionary::Node* Dictionary::findPrev(Node* N) {
	  Node* x = N;

      if (x == nil || x == nullptr) {
         return nil;
      }

      if ( !(x->left == nil) ) {
         return this->findMax(x->left);
      }
      Node* y = x->parent;

      while ( !(y == nil) && y->left == x) {
         x = y;
         y = y->parent;
      }
      return y;
	   
	   
   }

   // RBT Helper Functions (Optional) -----------------------------------------
   
   // LeftRotate()
   void Dictionary::LeftRotate(Node* N) {
		// set y
   	Node* y = N->right; 
   
   	// turn y's left subtree into x's right subtree
   	N->right = y->left;
      y->left->parent = N;
   
   	// link y's parent to x
   	y->parent = N->parent; 
   	if (N->parent == nil) {
      	this->root = y;
   	}else if (N == N->parent->left) {
      	N->parent->left = y;
   	}else{ 
      	N->parent->right = y;
   	}
   	// put x on y's left
   	y->left = N;
   	N->parent = y;	
	}

   // RightRotate()
   void Dictionary::RightRotate(Node* N) {
		// set y
   	Node* y = N->left; 
   
   	// turn y's right subtree into x's left subtree
   	N->left = y->right;
      y->right->parent = N;
   
   	// link y's parent to x
   	y->parent = N->parent; 
   	if (N->parent == nil) {
      	this->root = y;
   	} else if (N == N->parent->right) {
      	N->parent->right = y;
   	} else {
      	N->parent->left = y;
   	}
   	// put x on y's right
   	y->right = N;
   	N->parent = y;
	}

   // RB_InsertFixUP()
   void Dictionary::RB_InsertFixUp(Node* N) {
		while (N->parent->color == 1) {
      	if (N->parent == N->parent->parent->left) {
         	Node* y = N->parent->parent->right;
         	if (y->color == 1) {
            	N->parent->color = 0;         	     // case 1
            	y->color = 0;               	      // case 1
            	N->parent->parent->color = 1;         // case 1
            	N = N->parent->parent;		         // case 1
         	} else  {
            	if (N == N->parent->right) {
               	N = N->parent;                     // case 2
               	LeftRotate(N);                 // case 2
					}
            	N->parent->color = 0;              // case 3
            	N->parent->parent->color = 1;         // case 3
            	RightRotate(N->parent->parent);     // case 3
				}
      	} else { 
         	Node* y = N->parent->parent->left;
         	if (y->color == 1) {
            	N->parent->color = 0;              // case 4
            	y->color = 0;                     // case 4
            	N->parent->parent->color = 1;         // case 4
            	N = N->parent->parent;                 // case 4
         	} else {
            	if (N == N->parent->left) {
               	N = N->parent;                     // case 5
               	RightRotate(N);						// case 5
					}                							
            	N->parent->color = 0;              // case 6
            	N->parent->parent->color = 1;         // case 6
            	LeftRotate(N->parent->parent);			// case 6
				}
			}
		}
   	this->root->color = 0;
	}

   // RB_Transplant()
   void Dictionary::RB_Transplant(Node* u, Node* v) {
		if (u->parent == nil) {
			this->root = v;
   	}else if (u == u->parent->left) {
      	u->parent->left = v;
   	}else{ 
      	u->parent->right = v;
		}
     	v->parent = u->parent;
	}

   // RB_DeleteFixUp()
   void Dictionary::RB_DeleteFixUp(Node* N) {
		while (N != this->root && N->color == 0) {
         if (N == N->parent->left) {
            Node* w = N->parent->right;
            if (w->color == 1) {
               w->color = 0;                        // case 1
               N->parent->color = 1;                   // case 1
               LeftRotate(N->parent);                // case 1
               w = N->parent->right;                     // case 1
            }
            if (w->left->color == 0 && w->right->color == 0) {
               w->color = 1;                         // case 2
               N = N->parent;                           // case 2
            }else{
               if (w->right->color == 0) {
                  w->left->color = 0;                // case 3
                  w->color = 1;                       // case 3
                  RightRotate(w);                   // case 3
                  w = N->parent->right;                  // case 3
               }
               w->color = N->parent->color;               // case 4
               N->parent->color = 0;                 // case 4
               w->right->color = 0;                  // case 4
               LeftRotate(N->parent);                // case 4
               N = this->root;                             // case 4
            }
         } else {
            Node* w = N->parent->left;
            if (w->color == 1) {
               w->color = 0;                        // case 5
               N->parent->color = 1;                   // case 5
               RightRotate(N->parent);               // case 5
               w = N->parent->left;                 // case 5
            }
            if (w->right->color == 0 && w->left->color == 0) {
               w->color = 1;                          // case 6
               N = N->parent;                           // case 6
            }else{
               if (w->left->color == 0) {
                  w->right->color = 0;               // case 7
                  w->color = 1;                       // case 7
                  LeftRotate(w);                    // case 7
                  w = N->parent->left;                   // case 7
               }
               w->color = N->parent->color;               // case 8
               N->parent->color = 0;                 // case 8
               w->left->color = 0;                   // case 8
               RightRotate(N->parent);               // case 8
               N = this->root;                             // case 8
            }
			}
		}
   	N->color = 0;	
	}

   // RB_Delete()
   void Dictionary::RB_Delete(Node* N) {
		Node* y = N;
		Node* x = nullptr;
   	int y_original_color = y->color;
   	if (N->left == nil) {
      	x = N->right;
      	RB_Transplant(N, N->right);
   	}else if (N->right == nil) {
      	x = N->left;
      	RB_Transplant(N, N->left);
   	}else{
      	y = findMin(N->right);
      	y_original_color = y->color;
      	x = y->right;
      	if (y->parent == N) {
         	x->parent = y;
      	}else{
         	RB_Transplant(y, y->right);
         	y->right = N->right;
         	y->right->parent = y;
			}
      	RB_Transplant(N, y);
      	y->left = N->left;
      	y->left->parent = y;
      	y->color = N->color;
		}
   	if (y_original_color == 0) {
      	RB_DeleteFixUp(x);
		}
	}



   // Class Constructors & Destructors ----------------------------------------
   
   // Creates new Dictionary in the empty state. 
   Dictionary::Dictionary() {
		nil = new Node("0", 0);
		nil->left = nullptr;
		nil->right = nullptr;
		nil->parent = nullptr;
		root = nullptr;
		current = nil;
		num_pairs = 0;
	}

   // Copy constructor.
   Dictionary::Dictionary(const Dictionary& D) {
		nil = new Node("0", 0);
		nil->left = nullptr;
      nil->right = nullptr;
		nil->parent = nullptr;
		root = nullptr;
		current = nil;
		this->preOrderCopy(D.root, D.nil);
		num_pairs = D.num_pairs;
	}

   // Destructor
   Dictionary::~Dictionary() {
		postOrderDelete(this->root);
		delete nil;
	}


   // Access functions --------------------------------------------------------

   // size()
   // Returns the size of this Dictionary.
   int Dictionary::size() const {
		return num_pairs;
	}

   // contains()
   // Returns true if there exists a pair such that key==k, and returns false
   // otherwise.
   bool Dictionary::contains(keyType k) const {
		return search(this->root, k) == nil ? false : true;
	}

   // getValue()
   // Returns a reference to the value corresponding to key k.
   // Pre: contains(k)
   valType& Dictionary::getValue(keyType k) const {
		if ( !this->contains(k) ) {
			throw std::invalid_argument("Dictionary Error: Calling getValue() when key doesn't exist.");
		}
		return (search(this->root, k))->val;
	}

   // hasCurrent()
   // Returns true if the current iterator is defined, and returns false 
   // otherwise.
   bool Dictionary::hasCurrent() const {
		return this->current == nil ? false : true;
	}

   // currentKey()
   // Returns the current key.
   // Pre: hasCurrent() 
   keyType Dictionary::currentKey() const {
		if ( hasCurrent() == false ) {
			throw std::invalid_argument("Dictionary Error: Calling currentKey() when current doesn't exist.");
		}
		return current->key;
	}

   // currentVal()
   // Returns a reference to the current value.
   // Pre: hasCurrent()
   valType& Dictionary::currentVal() const {
		if ( !hasCurrent() ) {
         throw std::invalid_argument("Dictionary Error: Calling currentVal() when current doesn't exist.");
      }
      return current->val;
	}


   // Manipulation procedures -------------------------------------------------

   // clear()
   // Resets this Dictionary to the empty state, containing no pairs.
   void Dictionary::clear() {
		postOrderDelete(this->root);
		current = nil;
		root = nullptr;
	}

   // setValue()
   // If a pair with key==k exists, overwrites the corresponding value with v, 
   // otherwise inserts the new pair (k, v).
   void Dictionary::setValue(keyType k, valType v) {
		Node* N = search(this->root, k);
		if (N != nil) { 
			N->val = v;
		}else{ 				
			Node* y = nil;
         Node* x = this->root;
         while (x != nil && x != nullptr) {
				y = x;
            if ( k.compare(x->key) < 0 ) {
               x = x->left;
            }else{
               x = x->right;
				}
			}
			Node* z = new Node(k, v);
			z->left = nil;
			z->right = nil;
         z->parent = y;
			z->color = 1;
         if (y == nil) {
            this->root = z;    // tree T was empty
				this->root->parent = nil;
				this->num_pairs += 1;
         } else if ( k.compare(y->key) < 0 ) {
				if (y->left == nil) { this->num_pairs += 1;}
            y->left = z;
         } else {
				if (y->right == nil) { this->num_pairs += 1;}
            y->right = z;
			}
			RB_InsertFixUp(z);
		}	
	}

   // remove()
   // Deletes the pair for which key==k. If that pair is current, then current
   // becomes undefined.
   // Pre: contains(k).
   void Dictionary::remove(keyType k) {
		Node* target = search(this->root, k);
		if ( target == nil ) {
			throw std::invalid_argument("Dictionary Error: Calling remove() when key: " + k + " doesn't exist.");
		}
		if ( target == this->current ) {
			this->RB_Delete(current);
			delete target;
			current = nil;
			num_pairs -= 1;
			return;
		}	
		
		this->RB_Delete(target);
		delete target;
		num_pairs -= 1;
		return;
		
	}

   // begin()
   // If non-empty, places current iterator at the first (key, value) pair
   // (as defined by the order operator < on keys), otherwise does nothing. 
   void Dictionary::begin() {
		if ( this->size() > 0 ) {
			current = findMin(this->root);
		}
	}

   // end()
   // If non-empty, places current iterator at the last (key, value) pair
   // (as defined by the order operator < on keys), otherwise does nothing. 
   void Dictionary::end() {
		if ( this->size() > 0 ) {
         current = findMax(this->root);
      }

	}

   // next()
   // If the current iterator is not at the last pair, advances current 
   // to the next pair (as defined by the order operator < on keys). If 
   // the current iterator is at the last pair, makes current undefined.
   // Pre: hasCurrent()
   void Dictionary::next() {
		if ( !hasCurrent() ) {
			throw std::invalid_argument("Dictionary Error: Calling next() when current doesn't exist.");
		}
		current = findNext(current);
	}

   // prev()
   // If the current iterator is not at the first pair, moves current to  
   // the previous pair (as defined by the order operator < on keys). If 
   // the current iterator is at the first pair, makes current undefined.
   // Pre: hasCurrent()
   void Dictionary::prev() {
	if ( !hasCurrent() ) {
      	throw std::invalid_argument("Dictionary Error: Calling prev() when k doesn't exist.");
		}
      current = findPrev(current);	

	}


   // Other Functions ---------------------------------------------------------

   // to_string()
   // Returns a string representation of this Dictionary. Consecutive (key, value)
   // pairs are separated by a newline "\n" character, and the items key and value 
   // are separated by the sequence space-colon-space " : ". The pairs are arranged 
   // in order, as defined by the order operator <.
   std::string Dictionary::to_string() const {
		string s;
		this->inOrderString(s, this->root);
		return s;
	}

   // pre_string()
   // Returns a string consisting of all keys in this Dictionary. Consecutive
   // keys are separated by newline "\n" characters. The key order is given
   // by a pre-order tree walk.
   std::string Dictionary::pre_string() const {
		string s;
      this->preOrderString(s, this->root);
      return s;	
	}

   // equals()
   // Returns true if and only if this Dictionary contains the same (key, value)
   // pairs as Dictionary D.
   bool Dictionary::equals(const Dictionary& D) const {
		if (D.size() != this->size()) {
			return false;
		}
		
		if ( (D.to_string()).compare(this->to_string()) != 0 ) {	
			return false;
		}
		return true;
	}


   // Overloaded Operators ----------------------------------------------------
   
   // operator<<()
   // Inserts string representation of Dictionary D into stream, as defined by
   // member function to_string().
   std::ostream& operator<<( std::ostream& stream, Dictionary& D ) {
		return stream << D.to_string();
	}

   // operator==()
   // Returns true if and only if Dictionary A equals Dictionary B, as defined
   // by member function equals(). 
   bool operator==( const Dictionary& A, const Dictionary& B ) {
		return A.equals(B);
	}

   // operator=()
   // Overwrites the state of this Dictionary with state of D, and returns a
   // reference to this Dictionary.
   Dictionary& Dictionary::operator=( const Dictionary& D ) {
		this->clear();
		this->preOrderCopy(D.root, D.nil);
		this->num_pairs = D.num_pairs;
		return *this;

	}
