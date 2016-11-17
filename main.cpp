//===-----------------------------------------------------------------------===//
//
//  Project 1: Big Integer Arithmetic
//  Authors: Michael Aboff, Mauricio Ferrato, Darsh Patel, Edwin Ortiz,
//           Eric Wright
//
//===----------------------------------------------------------------------===//
//
//  main.cpp
//    Main file for the application.
//
//===----------------------------------------------------------------------===//

#include <iostream>
#include "big_int.h"
#include "multiplication.h"
#include "addition.h"
#include "subtraction.h"
#include "division.h"
using namespace std;

int main() {

    BigInt file1 = ReadFromFile("int1");
    BigInt file2 = ReadFromFile("int2");
    BigInt sum = file1 + file2;
    BigInt difference = file1 - file1;
    BigInt prod = file1 * file2;
    BigInt quo = FindQuotient(file2, file1);

    sum.WriteToFile("sum.txt");
    difference.WriteToFile("difference.txt");
    prod.WriteToFile("prod.txt");
    quo.WriteToFile("quo.txt");
}