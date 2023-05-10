#include<iostream>
#include<fstream>
#include<string>
#include "List.h"
#include <cstring>
#include <stdlib.h>

using namespace std;

#define MAX_LEN 300

void shuffle(List& D);

int main(int argc, char * argv[]){
   // check command line for correct number of arguments
   if( argc != 2 ){
      cerr << "Usage: " << argv[0] << " <number of cards>" << endl;
      return(EXIT_FAILURE);
   }
	
	if ( atoi(argv[1]) <= 0 ) {
		cerr << "Shuffle Error: The argument must be a positive integer." << endl;
		return(EXIT_FAILURE);
	}
	
	int shuffle_num = atoi(argv[1]);
	int shuffle_attempts = 0; 
	string s = "               ";
	
	List* deck = new List();
	deck->moveBack();
	cout << "deck size       shuffle count\n";
	cout << "------------------------------\n";
	for (int i = 0; i < shuffle_num; i += 1) {
		deck->moveBack();
		deck->insertAfter(i);
		List og_deck = *deck;
	
		shuffle_attempts = 0;		

		do { // while the og deck doesnt equal new deck
			shuffle_attempts += 1;
			shuffle(*deck);
		} while ( !deck->equals(og_deck) );
		
		
		string s = ""; 
		s += std::to_string(i);
		while (s.size() < 16) { // 
			s += " ";
		}	
		s += std::to_string(shuffle_attempts) + "\n";
		cout << s;
	}
	
	delete deck;
	
   return(EXIT_SUCCESS);
}



void shuffle(List& D) {
   int size = D.length();
   ListElement key;
   for (int i = 0; i < size/2; i += 1) {
      D.moveFront();
      key = D.moveNext();
      D.eraseBefore();
      while (D.position() < size/2 + i) { // so position() will have hit the size/2 when loop is over
         D.moveNext();
         if (D.position() == size/2 + i) {
            D.insertBefore(key);
         }
      }
   }
}














