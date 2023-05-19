
BigIntegerTest: BigIntegerTest.o BigInteger.o List.o
	g++ -std=c++17 -Wall -o BigIntegerTest BigIntegerTest.o BigInteger.o List.o

BigIntegerTest.o: BigIntegerTest.cpp BigInteger.h
	g++ -std=c++17 -Wall -c BigIntegerTest.cpp

List.o: List.cpp List.h
	g++ -std=c++17 -Wall -c List.cpp

BigInteger.o: BigInteger.cpp List.h BigInteger.h
	g++ -std=c++17 -Wall -c BigInteger.cpp
