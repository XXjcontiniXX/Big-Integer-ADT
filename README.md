James Contini / jcontini / pa6
## USAGE: `./Arithmetic <in file> <out file>`

### List.h
 List.h is a C++ header which prototypes all of List.cpp's public functions and types for the List ADT.
### List.cpp
 List.cpp is a C++ source file which contains the public and private List ADT functions.
### ListTest.cpp
 ListTest.cpp is a C++ file which contains the test cases for the List ADT.
### BigIntegerTest.cpp
 BigInteger.cpp is a C++ file which contains the test cases for the BigInteger ADT.
### BigInteger.cpp
 BigInteger.cpp is a C++ which contains all public and private BigInteger ADT functions.
### BigInteger.h
 BigInteger.h is a C++ header which prototypes all of BigInteger.cpp's public functions and types for the BigInteger ADT.
### Arithmetic.cpp
 Arithmetic.cpp is the main program file. Arithmetic.cpp handles all FileIO and uses the BigInteger ADT's client functions to demonstrate the BigInteger ADT.
### README.md
 This file contains a description of the repository and of each file.
### Makefile
 Makefile builds the Arithmetic.cpp executable and has the capability to clean the working directory of executables and .o files.

# Developer notes:
 BigInteger ADT is functionally effective in all operations from `-1 x 10^1000 to 1 x 10^1000` after which point calculation becomes too slow to be useful.
 With the algorithm implented, the most I could improve the runtime was about `12%` from the orignal working code. This was completed by exiting `List strtols(string s)` before trivial zeroes are prepended.
 If I had instead taken advantage of modular arithmetic and floor division in my normalize, I probably could have made a faster ADT. 
