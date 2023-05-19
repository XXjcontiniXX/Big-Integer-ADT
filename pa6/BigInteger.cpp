//-----------------------------------------------------------------------------
// BigInteger.cpp
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"
#include"List.h"

using namespace std;
// Class Constructors & Destructors ----------------------------------------

const int power = 9;

const ListElement base = 10e9;

void normalizeList(List& L);

// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger() {
	signum = 0;
	digits = List();
}

// BigInteger()
// Constructor that creates a new BigInteger from the long value x.
BigInteger::BigInteger(long x) {
	if (x == 0) {
		signum = 0;
	}
	signum = x > 0 ? 1: 0;
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
	
	long radix = 1;
   for (int i = 0; i < power; i += 1){
   	radix = radix * 10;
   }

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
	long radix = 1;
   for (int i = 0; i < power; i += 1){
      radix = radix * 10;
   }

	bool carry = false;
	bool borrow = false;
	ListElement place = 0;

	while (L.position() != 0) {
		if (carry) {
			place = L.movePrev() + 1;
		}
		else if (borrow) {
			place = L.movePrev() - 1;
		}else{
			place = L.movePrev();
		}
		

		if (place >= radix) {
			L.setAfter(place - radix);
			carry = true;
		}else if (place < 0) {
			L.setAfter(place + radix);
         borrow = true;
		}else{
			L.setAfter(place);
			carry = false;
			borrow = false;
		}	
	}
}


// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const {
	List top = List(this->digits);
	List bottom = List(N.digits);
	List tmp;
	
	BigInteger prod = BigInteger();
	BigInteger sum = BigInteger();
	List &s = sum.digits;

	s.moveBack();
	top.moveBack();
	bottom.moveBack();
	
	long radix = 1;
   for (int i = 0; i < power; i += 1){
   	radix = radix * 10;
   }
	
	long remainder = 0;
	long new_remainder = 0;

	ListElement top_num = 0;
	ListElement bottom_num = 0;
	
	long carry = 0;
	while (bottom.position() != 0) { // iterate on the bottom digits // top digits times all the bottom digits
		bottom_num = bottom.movePrev();
		top.moveBack(); // start at the back of top every time
		s.moveBack();  
		
		while (s.position() != bottom.position()) {
			s.movePrev(); // move to the same column in s as it is in bottom 
		}

		while (top.position() != 0) { // iterate the top digits
			top_num = top.movePrev() + carry;
			carry = 0;
			for (long i = 0; i < bottom_num; i += 1 ) {
				new_remainder = (top_num + remainder) % radix;
				if (new_remainder < remainder) {
					carry += 1;
				}
				remainder = remainder + new_remainder;
			}
			//cout << remainder;
			s.insertBefore(remainder);
			s.movePrev();
		}
		cout << sum << "\n";
		prod = prod + sum;
	}
	return prod;	
	
}


// Other Functions ---------------------------------------------------------
/*
// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string to_string();


   // Overriden Operators -----------------------------------------------------
   */
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
	/*
   // operator<()
   // Returns true if and only if A is less than B. 
   friend bool operator<( const BigInteger& A, const BigInteger& B );

   // operator<=()
   // Returns true if and only if A is less than or equal to B. 
   friend bool operator<=( const BigInteger& A, const BigInteger& B );

   // operator>()
   // Returns true if and only if A is greater than B. 
   friend bool operator>( const BigInteger& A, const BigInteger& B );

   // operator>=()
   // Returns true if and only if A is greater than or equal to B. 
   friend bool operator>=( const BigInteger& A, const BigInteger& B );
	*/
   // operator+()
   // Returns the sum A+B. 
   BigInteger operator+( const BigInteger& A, const BigInteger& B ) {
		return A.add(B);
	}
	/*
   // operator+=()
   // Overwrites A with the sum A+B. 
   friend BigInteger operator+=( BigInteger& A, const BigInteger& B );

   // operator-()
   // Returns the difference A-B. 
   friend BigInteger operator-( const BigInteger& A, const BigInteger& B );

   // operator-=()
   // Overwrites A with the difference A-B. 
   friend BigInteger operator-=( BigInteger& A, const BigInteger& B );

   // operator*()
   // Returns the product A*B. 
   friend BigInteger operator*( const BigInteger& A, const BigInteger& B );

   // operator*=()
   // Overwrites A with the product A*B. 
   friend BigInteger operator*=( BigInteger& A, const BigInteger& B );
*/
