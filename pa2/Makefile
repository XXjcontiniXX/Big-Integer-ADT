# James Contini
# 1909086
# pa2
#
#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 2
#
# make                  makes FindPath
# make GraphTest        makes GraphTest
# make clean            removes all binaries
# make checkTest        checks GraphTest for memory errors
# make checkFindPath    checks FindPath for memory errors
#------------------------------------------------------------------------------

FindPath : FindPath.o Graph.o List.o
	gcc -std=c17 -Wall -o FindPath FindPath.o Graph.o List.o

GraphTest: GraphTest.o Graph.o List.o
	gcc -std=c17 -Wall -o GraphTest GraphTest.o Graph.o List.o

FindPath.o : FindPath.c Graph.h
	gcc -std=c17 -Wall -c FindPath.c

List.o : List.c List.h
	gcc -std=c17 -Wall -c List.c

Graph.o : Graph.h List.h Graph.c
	gcc -std=c17 -Wall -c Graph.c

GraphTest.o : GraphTest.c Graph.h
	gcc -std=c17 -Wall -c GraphTest.c

clean :
	rm -f Lex GraphTest FindPath FindPath.o Graph.o List.o GraphTest.o

checkTest :
	make GraphTest
	valgrind --leak-check=full ./GraphTest

checkFindPath :
	valgrind --leak-check=full FindPath in3 blah3
