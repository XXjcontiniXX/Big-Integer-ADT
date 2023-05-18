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
	List top = List(this->digits);
	List bottom = List(N.digits);
	
	top.moveBack();
	bottom.moveBack();	
	
	
	BigInteger sum = BigInteger();
	
	List &C = sum.digits;
	C.moveBack();
	
	long maxDigit = 1;

	for (int i = 0; i < power; i += 1){
            maxDigit = maxDigit * 10;
   }
	long radix = maxDigit;
	maxDigit = maxDigit - 1;


	ListElement place = 0;
	ListElement top_num = 0;
	ListElement bottom_num = 0;	

	bool carry = false;
	
	while (top.position() > 0 && bottom.position() > 0) {
		top_num = top.movePrev();
		bottom_num = bottom.movePrev();
		top_num  = carry ? top_num + 1 : top_num; // if carry top_num gets another number
		place = top_num + bottom_num; // 

		//top_max = maxDigit - bottom_num // 5 = 9 - 4 in other words: if the bottom is 4, the top must be less than 6 or we must arry
		
		if (place > maxDigit) { // if place is bigger than a digit
			place = place % radix; // reduce it to the radix
			C.insertBefore(place); // place it
			C.movePrev();
			carry = true; // turn carry on
		}else{ // if we dont need to carry
			place = top_num + bottom_num;
			C.insertBefore(place);
			C.movePrev();
			carry = false;
		}	
	}
		
	if (bottom.position() == 0 && top.position() == 0) {
		if (carry) {
			C.insertBefore(long(1));
      	C.movePrev();
		}
		return sum;	
	}
	
		
	while (top.position() > 0) {
		top_num = top.movePrev();
		if (carry) {
			top_num = top_num + 1;
		}
		
		if (top_num > maxDigit) {
			top_num = top_num % radix;
			carry = true;
		}else{
			carry = false;
		}
		C.insertBefore(top_num);      
		C.movePrev();
	}

	
	while (bottom.position() > 0) {
      bottom_num = bottom.movePrev();
      if (carry) {
         bottom_num = bottom_num + 1;
      }

      if (bottom_num > maxDigit) {
         bottom_num = bottom_num % radix;
         carry = true;
      }else{
         carry = false;
      }
      C.insertBefore(bottom_num);
      C.movePrev();
   }
	return sum;

}


// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const {
	List top = List(this->digits);
   List bottom = List(N.digits);

   top.moveBack();
   bottom.moveBack();


   BigInteger diff = BigInteger();

   List &C = diff.digits;
   C.moveBack();

   long maxDigit = 1;

   for (int i = 0; i < power; i += 1){
            maxDigit = maxDigit * 10;
   }
	long radix = maxDigit;
   maxDigit = maxDigit - 1;
	
	

   ListElement place = 0;
   ListElement top_num = 0;
   ListElement bottom_num = 0;

	
	int sp = 0;
	
   while (top.position() > 0 && bottom.position() > 0) {
      top_num = top.movePrev();
      bottom_num = bottom.movePrev();
		
		if (top_num < bottom_num) { // if we need to borrow
			// borrow can't be true (i think) beneath bc 
			if (top.peekPrev() == 0) { // if the number behind is 0 (so we cant borrow)
				sp = top.position(); // remember what position needs to borrow
				
				while(top.movePrev() == 0){ // move backwards until we find a number we can borrow from
					if(top.peekPrev() > 0){  // check after each move if the one behind is not 0 
						break; // once found leave loop
					}
				}
				top.setBefore( (top.peekPrev()) - 1); // decrement that one
				
				while(top.position() != sp) { // coming back to stack pointer
					top.moveNext();
					top.setBefore(radix - 1); // setting them to radix-1 like 9 or 99 or 999 because they were zero and r brwed from now
				}
				top_num = top_num + radix; // now were where we were at the beginning 
				place = top_num - bottom_num;
				C.insertBefore(place);
         	C.movePrev();	
				continue;
			}else{
				top.setBefore(top.peekPrev() - 1);
				top_num = top_num + radix;
				place = top_num - bottom_num;
            C.insertBefore(place);
            C.movePrev();
				continue;
			}
		}else{
			place = top_num - bottom_num;
			C.insertBefore(place);
			C.movePrev();
		}
	}

	/*
   while (top.position() > 0) {
      top_num = top.movePrev();
      if (carry) {
         top_num = top_num + 1;
      }

      if (top_num > maxDigit) {
         top_num = top_num % (maxDigit + 1);
         carry = true;
      }else{
         carry = false;
      }
      C.insertBefore(top_num);
      C.movePrev();
   }
	
	while (bottom.position() > 0) {
      bottom_num = bottom.movePrev();
      if (carry) {
         bottom_num = bottom_num + 1;
      }

      if (bottom_num > maxDigit) {
         bottom_num = bottom_num % (maxDigit + 1);
         carry = true;
      }else{
         carry = false;
      }
      C.insertBefore(bottom_num);
      C.movePrev();
   }
	*/
   return diff;
	
}
/*
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
