/*
 * James Contini
 * jcontini
 * pa7
 */
#include<iostream>
#include<fstream>
#include<string>
#include"Dictionary.h"

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

   Dictionary A = Dictionary();

   while( getline(in, line) )  {
		line_count += 1;
		char p = line.back();
		if (p < 97 || p > 122) {
			line.pop_back();
		}

		A.setValue(line, line_count);
	}
	
	out << A.to_string();
	out << endl;
	out << A.pre_string();
	
	
	return 0;
}
