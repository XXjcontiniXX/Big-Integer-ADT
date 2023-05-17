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
	for (int i = s.size()-1, j = 0; i >= 0; i -= 1, j += 1) { // could be an incorrect for loop
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
	
		}else if (i == 0){
	
			if (s[i] == '-') {
				signum = -1;
			}else if (s[i] == '+') {
				signum = 1;
			}
		}else{
			throw std::invalid_argument("BigInteger: Constructor: non-numeric string\n");
		}
	}
	if (element > 0) {
		digits.insertBefore(element);
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
	if ( (this->digits).length() < (N.digits).length() ) { // big
		return -1;
	}

	if ( (this->digits).length() > (N.digits).length() ) {
		return 1;
	}
	
	List thussy = List(this->digits);
	List nussy = List(N.digits);

	
	thussy.moveFront();
	nussy.moveFront();
	
	ListElement haec;
	ListElement en;
	
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


/*
   // Manipulation procedures -------------------------------------------------

   // makeZero()
   // Re-sets this BigInteger to the zero state.
   void makeZero();

   // negate()
   // If this BigInteger is zero, does nothing, otherwise reverses the sign of 
   // this BigInteger positive <--> negative. 
   void negate();


   // BigInteger Arithmetic operations ----------------------------------------

   // add()
   // Returns a BigInteger representing the sum of this and N.
   BigInteger add(const BigInteger& N) const;

   // sub()
   // Returns a BigInteger representing the difference of this and N.
   BigInteger sub(const BigInteger& N) const;

   // mult()
   // Returns a BigInteger representing the product of this and N. 
   BigInteger mult(const BigInteger& N) const;


   // Other Functions ---------------------------------------------------------

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
		stream << N.digits;
		return stream;
	}
	/*
   // operator==()
   // Returns true if and only if A equals B. 
   friend bool operator==( const BigInteger& A, const BigInteger& B );

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

   // operator+()
   // Returns the sum A+B. 
   friend BigInteger operator+( const BigInteger& A, const BigInteger& B );

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
