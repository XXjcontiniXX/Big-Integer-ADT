#include<iostream>
#include<string>
#include"Dictionary.h"

using namespace std;
		
	Dictionary::Node::Node(keyType k, valType v) {
		this->key = k;
		this->val = v;
		this->parent = nullptr;
		this->left = nullptr;
		this->right = nullptr;
	}

   // inOrderString()
   // Appends a string representation of the tree rooted at R to string s. The
   // string appended consists of: "key : value \n" for each key-value pair in
   // tree R, arranged in order by keys.
   void Dictionary::inOrderString(std::string& s, Node* R) const {
		if ( R != nullptr) {
			inOrderString(s, R->left);
			string k = R->key;
			string v = std::to_string(R->val);
			s += k + " : " + v + "\n";
			inOrderString(s, R->right);
		}
	}

   // preOrderString()
   // Appends a string representation of the tree rooted at R to s. The appended
   // string consists of keys only, separated by "\n", with the order determined
   // by a pre-order tree walk.
   void Dictionary::preOrderString(std::string& s, Node* R) const {
		if ( R != nullptr) {
			s += R->key + "\n";
			preOrderString(s, R->left);
      	preOrderString(s, R->right);
		}
	}

   // preOrderCopy()
   // Recursively inserts a deep copy of the subtree rooted at R into this 
   // Dictionary. Recursion terminates at N.
   void Dictionary::preOrderCopy(Node* R, Node* N) {
		if ( R != N ) {
			this->setValue(R->key, R->val);
			preOrderCopy(R->left, N);
			preOrderCopy(R->right, N);
		
		}
	}

   // postOrderDelete()
   // Deletes all Nodes in the subtree rooted at R.
   void Dictionary::postOrderDelete(Node* R) {
		if ( R != nullptr && R != nil) {
         postOrderDelete(R->left);
         postOrderDelete(R->right);
			delete R;
      }
	}

   // search()
   // Searches the subtree rooted at R for a Node with key==k. Returns
   // the address of the Node if it exists, returns nil otherwise.
   Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
   	Node* x = R;
   	while (x != nullptr) {
      	if ( k.compare(x->key) < 0 ) { // use strcmp
         	x = x->left;
      	} else if ( k.compare(x->key) > 0 ) {
         	x = x->right;
			} else { 
				return x;
			}
		}
		return nil;
	}

   // findMin()
   // If the subtree rooted at R is not empty, returns a pointer to the 
   // leftmost Node in that subtree, otherwise returns nil.
   Dictionary::Node* Dictionary::findMin(Node* R) {
		Node * x = nil;
		while (x->left != nullptr) {
      	x = x->left;
		}
   	return x;
	} 

   // findMax()
   // If the subtree rooted at R is not empty, returns a pointer to the 
   // rightmost Node in that subtree, otherwise returns nil.
   Dictionary::Node* Dictionary::findMax(Node* R) {
		Node * x = nil;
      while (x->right != nullptr) {
         x = x->right;
      }
      return x;
	}

   // findNext()
   // If N does not point to the rightmost Node, returns a pointer to the
   // Node after N in an in-order tree walk.  If N points to the rightmost 
   // Node, or is nil, returns nil. 
   Dictionary::Node* Dictionary::findNext(Node* N) {
		if (N != nullptr) {
			if (N->right != nullptr) {
				return N->right;
			}

			Node* x = nullptr;
			Node* y = N;
			while ( y->parent != nullptr) { // 
				x = y->parent;					  // y is child of x
				if (x->left == y) { 			  // if x's left child is y
					return x;					  // return x
				}
				y = x;
			}
		}
		return nullptr;
	}
	

   // findPrev()
   // If N does not point to the leftmost Node, returns a pointer to the
   // Node before N in an in-order tree walk.  If N points to the leftmost 
   // Node, or is nil, returns nil.
   Dictionary::Node* Dictionary::findPrev(Node* N) {
	if (N != nullptr) {
         if (N->left != nullptr) {
            return N->left;
         }

         Node* x = nullptr;
         Node* y = N;
         while ( y->parent != nullptr) { //
            x = y->parent;               // y is child of x
            if (x->right == y) {          // if x's right child is y
               return x;                 // return x
            }
            y = x;
         }
      }
		return nullptr;
   }


   // Class Constructors & Destructors ----------------------------------------
   
   // Creates new Dictionary in the empty state. 
   Dictionary::Dictionary() {
		nil = new Node("0", 0);
		nil->left = root;
		nil->right = root;
		root = nullptr;
		current = nullptr;
		num_pairs = 0;
	}

   // Copy constructor.
   Dictionary::Dictionary(const Dictionary& D) {
		nil = new Node("0", 0);
		nil->left = root;
      nil->right = root;
		root = nullptr;
		current = nullptr;
		this->preOrderCopy(D.root, nullptr);
		num_pairs = D.num_pairs;
	}

   // Destructor
   Dictionary::~Dictionary() {
		postOrderDelete(this->root);
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
			cout << "throw an error\n";
		}
		return (search(this->root, k))->val;	
	}

   // hasCurrent()
   // Returns true if the current iterator is defined, and returns false 
   // otherwise.
   bool Dictionary::hasCurrent() const {
		return this->current == nullptr || this->current == nil ? false : true;
	}

   // currentKey()
   // Returns the current key.
   // Pre: hasCurrent() 
   keyType Dictionary::currentKey() const {
		if ( !hasCurrent() ) {
			cout << "no current throw error\n";
		}
		return current->key;
	}

   // currentVal()
   // Returns a reference to the current value.
   // Pre: hasCurrent()
   valType& Dictionary::currentVal() const {
		if ( !hasCurrent() ) {
         cout << "no current throw an error\n";
      }
      return current->val;
	}


   // Manipulation procedures -------------------------------------------------

   // clear()
   // Resets this Dictionary to the empty state, containing no pairs.
   void Dictionary::clear() {
		postOrderDelete(this->root);
		current = nullptr;
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
			Node* y = nullptr;
         Node* x = this->root;
         while (x != nullptr) {
            y = x;
            if ( k.compare(x->key) < 0 ) {
               x = x->left;
            }else{
               x = x->right;
				}
			}
			Node* z = new Node(k, v);
         z->parent = y;
         if (y == nullptr) {
            this->root = z;    // tree T was empty
				this->root->parent = nil;
				this->num_pairs += 1;
         } else if ( k.compare(y->key) < 0 ) {
				if (y->left == nullptr) { this->num_pairs += 1;}
            y->left = z;
         } else {
				if (y->right == nullptr) { this->num_pairs += 1;}
            y->right = z;
			}
		}
	}

   // remove()
   // Deletes the pair for which key==k. If that pair is current, then current
   // becomes undefined.
   // Pre: contains(k).
   void Dictionary::remove(keyType k) {
		if ( !contains(k) ) {
			cout << "throw a mf error\n";
		}
	
		Node* cur = search(this->root, k);

		if ( cur == current ) {
			delete current;
			current = nullptr;
			return;
		}
		delete cur;
		return;
	}

   // begin()
   // If non-empty, places current iterator at the first (key, value) pair
   // (as defined by the order operator < on keys), otherwise does nothing. 
   void Dictionary::begin() {
		current = nil->right;
	}

   // end()
   // If non-empty, places current iterator at the last (key, value) pair
   // (as defined by the order operator < on keys), otherwise does nothing. 
   void Dictionary::end() {
		current = findMax(this->root);
	}

   // next()
   // If the current iterator is not at the last pair, advances current 
   // to the next pair (as defined by the order operator < on keys). If 
   // the current iterator is at the last pair, makes current undefined.
   // Pre: hasCurrent()
   void Dictionary::next() {
		if ( !hasCurrent() ) {
			cout << "throw error\n";
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
         cout << "throw error\n";
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
		string s;
		this->inOrderString(s, this->root);
		for (unsigned long i = 0; i < s.size(); i += 1) {
			string l;
			l += s[i];
			if ( D.contains( l ) == false) {
				return false;
			}
		}
		return true;
	}

   // Overloaded Operators ----------------------------------------------------
   
   // operator<<()
   // Inserts string representation of Dictionary D into stream, as defined by
   // member function to_string().
   std::ostream& operator<<( std::ostream& stream, Dictionary& D ) {
		string s;
		D.Dictionary::preOrderString(s, D.root);
		
		return stream << s;
		;
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
		this->preOrderCopy(D.root, nullptr);
		this->num_pairs = D.num_pairs;
		this->nil = new Node("0", 0);
		nil->right = root;
		nil->left = root;
		nil->parent = nullptr;
		return *this;
	}



