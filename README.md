//===-----------------------------------------------------------------------===//
//
//  Project 1: Big Integer Arithmetic
//  Authors: Michael Aboff, Mauricio Ferrato, Darsh Patel, Edwin Ortiz,
//           Eric Wright
//
//===----------------------------------------------------------------------===//

This project introduces a BigInt class that lets us read, store, and manipulate
large numbers that would otherwise be too large for C++ to normally handle.


Hello professor,

You may remember that we had a memory leak problem during our presentation. We switched over from our own custom array class to using vectors
instead. Implementing it only took an hour or two, so most of our code was mostly set up to work with it. We kept all of our original files,
but the only files that run when you use the "make" command are main.cpp, big_int.cpp, addition.cpp, subtraction.cpp, multiplication.cpp,
and division.cpp. You'll notice that a lot of the files, like addition_.cpp have an underscore. Those are the old files that have been
replaced with vectors.

To run the program type "make" into the terminal and then "./big_int_world, and that will run anything in main.cpp.