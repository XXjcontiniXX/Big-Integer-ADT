# Makefile for pa4
# jaja

Sparse: Sparse.o Matrix.o List.o
	gcc -std=c17 -Wall -o Sparse Sparse.o List.o Matrix.o

Sparse.o: Sparse.c Matrix.h
	gcc -std=c17 -Wall -c Sparse.c

MatrixTest: MatrixTest.o List.o Matrix.o
	gcc -std=c17 -Wall -o MatrixTest MatrixTest.o List.o Matrix.o

Matrix.o: Matrix.c Matrix.h
	gcc -std=c17 -Wall -c Matrix.c

MatrixList.o: MatrixTest.c Matrix.h
	gcc -std=c17 -Wall -c MatrixTest.c
	
ListTest: ListTest.o List.o
	gcc -std=c17 -Wall -o ListTest ListTest.o List.o

ListTest.o: ListTest.c List.h
	gcc -std=c17 -Wall -c ListTest.c

List.o: List.c List.h
	gcc -std=c17 -Wall -c List.c

clean: 
	rm -r -f *.o 

checkTest :
	make MatrixTest
	valgrind --leak-check=full ./MatrixTest
