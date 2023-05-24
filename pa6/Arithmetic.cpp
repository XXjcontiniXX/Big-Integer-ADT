//-----------------------------------------------------------------------------
// FileIO.cpp
// Illustrates file input-output commands and text processing using the
// string functions find_first_of(), find_first_not_of() and substr().
// 
// compile:
//
//      g++ -std=c++17 -Wall -o FileIO FileIO.cpp
//
//-----------------------------------------------------------------------------
#include<iostream>
#include<fstream>
#include<string>
#include"BigInteger.h"

using namespace std;

#define MAX_LEN 10000

int main(int argc, char * argv[]){

   int line_count;
   ifstream in;
   ofstream out;
   string line;

   // check command line for correct number of arguments
   if( argc != 3 ){
      cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
      return(EXIT_FAILURE);
   }

   // open files for reading and writing 
   in.open(argv[1]);
   if( !in.is_open() ){
      cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      return(EXIT_FAILURE);
   }

   out.open(argv[2]);
   if( !out.is_open() ){
      cerr << "Unable to open file " << argv[2] << " for writing" << endl;
      return(EXIT_FAILURE);
   }

   // read each line of input file, then count and print tokens 
   line_count = 0;

	BigInteger A = BigInteger();
	BigInteger B = BigInteger();

   while( getline(in, line) )  {
      line_count++;
		
		if (line_count == 2) {
			continue;
		}
		if (line_count == 1) {
			A = BigInteger(line);
		}	
		if (line_count == 3) {
			B = BigInteger(line);
		}
			
   }

	out << A.to_string();
	out << endl << endl;
	out << B.to_string();
	out << endl << endl;	
	
	out << (A + B).to_string();
	out << endl << endl;
	out << (A - B).to_string();
	out << endl << endl;
	out << (A - A).to_string();
	out << endl << endl;
	out << (((A + A) + A) - (B + B)).to_string();
	out << endl << endl;
	out << (A*B).to_string();
	out << endl << endl;
	out << (A*A).to_string();
	out << endl << endl;
	out << (B*B).to_string();
	out << endl << endl;
	BigInteger A4 = BigInteger((( A * A ) * ( A * A)));
	A = A4;	
	BigInteger B5 = BigInteger((( B * B ) * ( B * B)) * B);
	B = B5;
	

	for (int i = 1; i < 9; i += 1) {
		A4 += A;
	}
	for (int i = 1; i < 16; i += 1) {
      B5 += B;
   }
	
	out << (B5 + A4).to_string();
	out << endl;


   // close files 
   in.close();
   out.close();

   return(EXIT_SUCCESS);
}

