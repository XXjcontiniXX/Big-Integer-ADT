# James Contini
# jcontini
# pa3
#
#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 3
#
# make                  makes FindPath
# make GraphTest        makes GraphTest
# make clean            removes all binaries
# make checkTest        checks GraphTest for memory errors
# make checkFindComponents    checks FindPath for memory errors
#------------------------------------------------------------------------------

FindComponents: FindComponents.o Graph.o List.o
	gcc -std=c17 -Wall -o FindComponents FindComponents.o Graph.o List.o

GraphTest: GraphTest.o Graph.o List.o
	gcc -std=c17 -Wall -o GraphTest GraphTest.o Graph.o List.o

FindComponents.o : FindComponents.c Graph.h
	gcc -std=c17 -Wall -c FindComponents.c

List.o : List.c List.h
	gcc -std=c17 -Wall -c List.c

Graph.o : Graph.h List.h Graph.c
	gcc -std=c17 -Wall -c Graph.c

GraphTest.o : GraphTest.c Graph.h
	gcc -std=c17 -Wall -c GraphTest.c

clean :
	rm -f Lex GraphTest FindComponents FindComponents.o Graph.o List.o GraphTest.o

checkTest :
	make GraphTest
	valgrind --leak-check=full ./GraphTest

checkFindComponents :
	valgrind --leak-check=full ./FindComponents in3 blah3
