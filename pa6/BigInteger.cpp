//-----------------------------------------------------------------------------
// BigInteger.cpp 
/*
 * James Contini
 * jcontini
 * pa6
 */
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"
#include"List.h"

using namespace std;
// Class Constructors & Destructors ----------------------------------------

const extern int power = 9;

const ListElement base = 1e9;

void normalizeList(List& L);
void scalarMult(List& L, ListElement M);
void shiftList(List& L, int p); 
string lstostr(List& L);
List strtols(string s);

// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger() {
	signum = 0;
	digits = List();
}

// BigInteger()
// Constructor that creates a new BigInteger from the long value x.
BigInteger::BigInteger(long x) { // this doesnt work for base 10 or anything except for 1 billion
	if (x == 0) {
		signum = 0;
	}
	if (x < 0) {
		x = x * -1;
		signum = -1;
	} //////////////////// FIXXXX

	if (x > 0) {
		signum = 1;
	}

	digits = List();
	digits.insertAfter(x);
}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s) {
	
	digits.moveFront();
	ListElement tmp = 0;
	ListElement element = 0;
	signum = 1;
	for (int i = s.size()-1, j = 0; i >= 0; i -= 1, j += 1) { // starting at back
		if ( isdigit(s[i]) ) {
			tmp = s[i] - 48;
			for (int k = 0; k < j % power; k += 1){
				tmp = tmp * 10;
			}
			element += tmp;
			if ( j % power == power - 1) {
				digits.insertBefore(element);
				digits.movePrev();
				element = 0;
			}
	
		}else{
			if ((s[i] == '-' || s[i] == '+') && (i == 0)) { // the signum is taken care of here
				signum = (s[i] == '-') ? -1 : 1;
				break;
			}else{
				throw std::invalid_argument("BigInteger: Constructor: non-numeric string\n");
			}
		}
	}
	
	if (element > 0) {
		digits.insertBefore(element);
	}
	long check = 0;
	digits.moveBack();
	while (check == 0 && digits.position() > 0) {
		check += digits.movePrev();
	}
	
	long leading = 0;
   digits.moveFront();
   while (leading == 0 && digits.position() < digits.length()) {
      leading = digits.moveNext();
		if (leading > 0) {
			break;
		}else{
			digits.eraseBefore();
		}
		
   }
	
	if (check == 0) {
		digits.clear();
		signum = 0;
	}

}
// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N) {
	this->digits = N.digits;
	this->signum = N.signum;
	return;
}

   // Optional Destuctor
   // ~BigInteger()
   // ~BigInteger();


   // Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive, 
// negative or 0, respectively.
int BigInteger::sign() const {
	return signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const { // they genuinely want me to make a copy wow
	if ((*this).sign() == 0 && N.sign() == 0) {
		return 0;
	}	
	
	if ((*this).sign() > N.sign() ) {
		return 1;
	}
	
	if (N.sign() > (*this).sign()) {
		return -1;
	}

	if ( (this->digits).length() < (N.digits).length()) {
		if (this->sign() == -1 && N.sign() == -1) {
			return 1;
		}      
		return -1;
   }

   if ( (this->digits).length() > (N.digits).length() ) {
      if (this->sign() == -1 && N.sign() == -1) {
         return -1;
      }
		return 1;
   }
	
	List thussy = List(this->digits);
   List nussy = List(N.digits);


   thussy.moveFront();
   nussy.moveFront();

   ListElement haec;
   ListElement en;


	if (N.sign() == -1 && (*this).sign() == -1) {
		while ( thussy.position() != thussy.length() ) { // while we not at the end
      	haec = thussy.moveNext();
      	en = nussy.moveNext();
      	if (haec == en) {
         	continue;
      	}
      	return haec > en ? -1 : 1;
   	}

   	return 0;
	
	}

	while ( thussy.position() != thussy.length() ) { // while we not at the end
		haec = thussy.moveNext();
		en = nussy.moveNext();
		if (haec == en) {
			continue;
		}
	
		return haec > en ? 1 : -1;
	}
	
	return 0;
}



// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero() {
	(this->digits).clear();
	signum = 0;
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate() {
	signum = signum * -1;
}


// BigInteger Arithmetic operations ----------------------------------------

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const {
	bool negate = false;
	
	if (this->sign() == -1 && N.sign() == -1) {
		negate = true;
	}else if(this->sign() == -1 && N.sign() == 1) {
		BigInteger bottom = BigInteger(*this);
		bottom.negate();
		return N.sub(bottom);
	}else if(this->sign() == 1 && N.sign() == -1) {
		BigInteger bottom = BigInteger(N);
      bottom.negate();
		
      return this->sub(bottom);
	}
	
	List top = List(this->digits);
	List bottom = List(N.digits);
	
	top.moveBack();
	bottom.moveBack();	
	
	
	BigInteger sum = BigInteger();
	if (this->sign() == 0 && N.sign() == 0 ) {
      return sum;
   }	


	List &C = sum.digits;
	C.moveBack();
	
	ListElement top_num = 0;
	ListElement bottom_num = 0;
	
	if (this == std::addressof(N)) {
		while(top.position() > 0) {
			sum.signum = 1;
			top_num = top.movePrev();
			C.insertBefore(top_num + top_num);
			C.movePrev();
		}
		normalizeList(C);
		if (negate) {
			sum.negate();
		}
		return sum;
	}

   while (top.position() > 0 && bottom.position() > 0) {
		sum.signum = 1;
		top_num = top.movePrev();
      bottom_num = bottom.movePrev();
		C.insertBefore(top_num + bottom_num); // place it
      C.movePrev();
	}
		
	while (top.position() > 0) {
		top_num = top.movePrev();
		C.insertBefore(top_num); // place it
      C.movePrev();		
	}

	
	while (bottom.position() > 0) {
		bottom_num = bottom.movePrev();
		C.insertBefore(bottom_num); // place it
      C.movePrev();
   }
	//cout << "C add: before normalizing: " << C;
	normalizeList(C);
	//cout << "C add: after normalizinf: " << C;
	if (negate) {
		sum.negate();
		return sum;
	}
	return sum;
}


// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const {

	bool reverse = false;
	BigInteger top_int = BigInteger(*this);
	BigInteger bottom_int = BigInteger(N);
	BigInteger diff = BigInteger();
	BigInteger tmp;



	/// MAKE CASES For when teyre the same number.


	if (this->sign() == 0 && N.sign() == 0 ) {
      return diff;
   }
		

	if(this->sign() == -1 && N.sign() == -1) { // if top and bottom negative, the top is the antagoniser, the negative.
      tmp = BigInteger(top_int);
      top_int = bottom_int;
      bottom_int = tmp;
      if ( top_int.compare(bottom_int) == 1) { // but if the bottom is smaller we gave to flip it around again and then reverse the sign
			tmp = BigInteger(top_int);
			top_int = bottom_int;
			bottom_int = tmp;
			reverse = true;
		} // if the bottom is greater were fine
   }else if (this->sign() == 1 && N.sign() == -1) {
		bottom_int.negate();
		diff = top_int.add(bottom_int);
		return diff;
	}else if (this->sign() == -1 && N.sign() == 1) {
		top_int.negate();
		diff = top_int.add(bottom_int);
		diff.negate();
		return diff;
	}else{ // (this->sign() == 1 && N.sign() == 1) // if normal we gotta compare bottom n top
		if ( top_int.compare(bottom_int) == -1) { // but if the bottom is smaller we gave to flip it around again and then reverse the sign
         tmp = BigInteger(top_int);
         top_int = bottom_int;
         bottom_int = tmp;
         reverse = true;
      }	
	}
	
	List top = List(top_int.digits);
   List bottom = List(bottom_int.digits);
	
   top.moveBack();
   bottom.moveBack();

   List &C = diff.digits;
   C.moveBack();
	
   ListElement top_num = 0;
   ListElement bottom_num = 0;
	
	
	while (top.position() > 0 && bottom.position() > 0) {
		diff.signum = 1;
      top_num = top.movePrev();
      bottom_num = bottom.movePrev();
		if (top.position() == 0 && top_num - bottom_num == 0) { break; }
		C.insertBefore(top_num - bottom_num); // place it
      C.movePrev();
   }

	while (top.position() > 0) {
      top_num = top.movePrev();
      C.insertBefore(top_num); // no need to normalize
   	C.movePrev();
   }
	//cout << "sub C: before normalizing: " << C;
	normalizeList(C);
	//cout << "sub C: after normalizing: " << C;


	long check = 0;
   (diff.digits).moveBack();
   while (check == 0 && (diff.digits).position() > 0) {
      check += (diff.digits).movePrev();
   }

   if (check == 0) {
      (diff.digits).clear();
      diff.signum = 0;
   }


	if (reverse) {
		diff.signum = -1;
		return diff;
	}else{
		return diff;	
	}
}

// normalizeList() 
// Performs carries from right to left (least to most significant  
// digits), then returns the sign of the resulting integer. Used  
// by add(), sub() and mult(). 
void normalizeList(List& L) {
	L.moveBack();
	int carry = false;
	bool borrow = false;
	ListElement place = 0;

	while (L.position() > 0) {
		if (carry) {
			place = L.movePrev() + 1;
		}
		else if (borrow) {
			place = L.movePrev() - 1;
		}else{
			place = L.movePrev();
		}
		

		if (place >= base) {
			L.setAfter(place - base);
			carry = true;
		}else if (place < 0) {
			L.setAfter(place + base);
         borrow = true;
		}else{
			L.setAfter(place);
			carry = false;
			borrow = false;
		}	
	}
	if (carry) { // Could be wrong fixes, issue with carry at the end.
		L.insertBefore(1);
	}

}



int compareList(List A, List B) { // returns 1 if A > B, 0 A == B, -1 A < B.
	
	int A_length = A.length();
	int B_length = B.length();
	A.moveFront();	

	if (A_length > B_length) {
		return 1;
	}
	if (A_length < B_length) {
		return -1;
	}
	
	ListElement A_val = 0;
	ListElement B_val = 0;
	
	while (A.position() != A.length()) {
		A_val = A.moveNext();
		B_val = B.moveNext();	
	
		if (A_val > B_val) {
			return 1;
		}
		if (A_val < B_val) {
			return -1;
		}
	}
	return 0;
}


void sumList(List& S, List A, List B) {
   S.moveBack();
   A.moveBack();
   B.moveBack();
	ListElement top_num = 0;
	ListElement bottom_num = 0;

	while (A.position() > 0 && B.position() > 0) {
      //s.signum = 1; rain check on this
      top_num = A.movePrev();
      bottom_num = B.movePrev();
      S.insertBefore(top_num + bottom_num); // place it
      S.movePrev();
   }

   while (A.position() > 0) {
      top_num = A.movePrev();
      S.insertBefore(top_num); // place it
      S.movePrev();
   }

   while (B.position() > 0) {
      bottom_num = B.movePrev();
      S.insertBefore(bottom_num); // place it
      S.movePrev();
   }
	normalizeList(S);
}


void subList(List& S, List A, List B) {
	List diff = List(); 
	diff.moveBack();
	A.moveBack();
	B.moveBack();
	ListElement top_num = 0;
	ListElement bottom_num = 0;

	while (A.position() > 0 && B.position() > 0) {
      top_num = A.movePrev();
      bottom_num = B.movePrev();
      if (A.position() == 0 && top_num - bottom_num == 0) { break; }
      diff.insertBefore(top_num - bottom_num); // place it
      diff.movePrev();
   }

   while (A.position() > 0) {
      top_num = A.movePrev();
      diff.insertBefore(top_num); // no need to normalize
      diff.movePrev();
   }
	normalizeList(diff);
	S = List(diff);
}

void combineList(List& S, List A, List B, int sgn) {
	

	S.clear();
	

	S.moveBack();
	A.moveBack();
	B.moveBack();
	
	if (sgn == 1) {
   	sumList(S, A, B);
		//S.moveBack();
		//cout << "peekPrev(): " << S.peekPrev() << " Base: "  << base << "\n";
   	//if (S.peekPrev() > base) {
      //	cout << "error\n";
   	//}	
	}else if (sgn == -1) {
	
		int opt = compareList(A, B);
		if (opt == 1) {
			subList(S, A, B); // A - B makes sense
		}
		if (opt == -1) {
			subList(S, B, A); // since B has is larger itll do B - A
		}
		if (opt == 0) {
			S = List(); // return empty List
		}
		
	}else{
		S = A; //(////) // if B is zero we just have A
	}

}



void scalarMult(List& L, ListElement m) {
	if (m == 0) {
		L.clear();
		return;
	}
	
	List M = List();
	M.insertBefore(m);

	L.moveBack();	

	List prod = List();
	List sum = List();
	List sig_raw;
	while (L.position() > 0) { // for each ListElement digit
		string digit = std::to_string( L.movePrev() );
		sum.clear();
		for (int i = digit.size() - 1; i >= 0; i -= 1) { // for each char in a ListElement digit
			sig_raw.clear();
			
			if (digit[i] - '0' == 0) {
				continue;
			}
			for(long j = 0; j < digit[i] - '0'; j += 1) { // for the length of a char
				combineList(sig_raw, sig_raw, M, 1); // add M to itself i.e. M * chara
			}
			
			
			if (i == 8) {
				combineList(sum, sum, sig_raw, 1);
				continue;
			}
			
			string sig = lstostr(sig_raw);
         for (int j = 0; j < (int)(digit.size()) - i - 1; j += 1) { // add 0s to it
            sig = sig + '0';
         }
         combineList(sum, sum, strtols(sig), 1); // sum = sum + sig_raw
		}
		shiftList(sum, L.length() - L.position() - 1);
		combineList(prod, prod, sum, 1);
	}
	L = prod;
}



List strtols(string s) {
	List L = List();
	L.moveFront();
	int tmp = 0;
	int element = 0;
	for (int i = s.size()-1, j = 0; i >= 0; i -= 1, j += 1) { // starting at back
      tmp = s[i] - 48;
      for (int k = 0; k < j % power; k += 1){
         tmp = tmp * 10;
      }
      element += tmp;
      if ( j % power == power - 1) {
         L.insertBefore(element);
         L.movePrev();
         element = 0;
      }
	}

   if (element > 0) {
      L.insertBefore(element);
   }	
	return L;
}

string lstostr(List& L) {
	string s;
   string ss;
   long digit = 0;
   L.moveBack();
   while (L.position() > 0) {
      digit = L.movePrev();
      s = std::to_string(digit);
      ss = s + ss;
      for (int i = 0; i < power - int(s.size()); i += 1) {
        	if (L.position() == 0) {
				break;
			}
			ss = "0" + ss;
      }
   }
   return ss;
}


void shiftList(List& L, int p) {
	L.moveBack();
	
	for (int i = 0; i < p; i += 1) {
		L.insertAfter(0);
		L.moveNext();
	}
}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const {
	BigInteger prod = BigInteger();
	
	BigInteger top_int = BigInteger(*this);
	BigInteger bottom_int = BigInteger(N);
	List top;

	bool neg = false;
	
	if (N.sign() == -1 && this->sign() == 1) {
		neg = true;
	}
	
	if (N.sign() == 1 && this->sign() == -1) {
		neg = true;
	}
	
	prod.signum = 1;
	

	List &p = prod.digits;
	
	List bottom = List(bottom_int.digits);
	
	bottom.moveBack();
	ListElement bottom_num = 0;	
	
	while (bottom.position() > 0) {
		//cout << "how fast\n";
		top = List(top_int.digits); // cache OG top
		bottom_num = bottom.movePrev(); // get ur multiplier
		scalarMult(top, bottom_num); // multiple the top bottom times || then save in top
		//cout << "new top: " << top << "\n";
		//cout << "bottom length: " << bottom.length() << " minus bottom position: " << bottom.position() << " plus: " << 1 << "\n";
		//cout << "so total is: " << bottom.length() - bottom.position() - 1 << "\n";
		shiftList(top, bottom.length() - bottom.position() - 1); // shift top 
		combineList(p, p, top, 1);	//this does the addition
	}
	
	if (neg) {
		prod.signum = -1;
	}

	long check = 0;
   (prod.digits).moveBack();
   while (check == 0 && (prod.digits).position() > 0) {
      check += (prod.digits).movePrev();
   }

   if (check == 0) {
      (prod.digits).clear();
      prod.signum = 0;
   }
	
	return prod;
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string() {
	if (this->signum == 0) {
		return "0";
	}

	string s;
	string ss;
	long digit = 0;
	List A = List(this->digits);	
	A.moveBack();
	while (A.position() > 0) {
		digit = A.movePrev();
		s = std::to_string(digit);
		ss = s + ss;
		//cout << power - s.size() << "\n";
		if (A.position() == 0) {
			if (this->signum == -1) {
				ss = '-' + ss;
			}
			break;
		}
		for (int i = 0; i < power - int(s.size()); i += 1) {
			ss = "0" + ss;
		}
	}
	return ss;
}


// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ) {
	if (N.signum != 0){
		stream << (N.signum == 1 ? '+' : '-') << " ";
	}
		stream << N.digits;
		return stream;
}
	
// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ) {
	return A.compare(B) == 0 ? true : false;	
}
	
// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ) {
	return A.compare(B) == -1 ? true : false;
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ) {
	return A.compare(B) <= 0 ? true : false;
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ) {
	return A.compare(B) == 1 ? true : false;
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ) {
	return A.compare(B) >= 0 ? true : false;
}
	
// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ) {
	return A.add(B);
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ) {
	BigInteger A_tmp = BigInteger(A);
	A = A_tmp + B;
	return A;
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ) {
   return A.sub(B);
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ) {
	BigInteger A_tmp = BigInteger(A);
   A = A_tmp - B;
   return A;
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ) {
	return A.mult(B);
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ) {
	BigInteger A_tmp = BigInteger(A);
   A = A_tmp * B;
   return A;
}
