//===-----------------------------------------------------------------------===//
//
//  Project 1: Big Integer Arithmetic
//  Authors: Michael Aboff, Mauricio Ferrato, Darsh Patel, Edwin Ortiz,
//           Eric Wright
//
//===----------------------------------------------------------------------===//
//
//  division.h
//    Header file for division.cpp
//
//===----------------------------------------------------------------------===//

#ifndef DIVISION_H
#define DIVISION_H

#include <iostream>
#include <string>
#include "addition.h"
#include "subtraction.h"
#include "multiplication.h"
#include "big_int.h"
#include "super_array.h"
using namespace std;

BigInt DivideByTwo(BigInt a);

BigInt FindQuotient(BigInt a, BigInt b);

BigInt FindQuotient(BigInt a, BigInt b, BigInt &r);

void DivideRemainder(BigInt &remaining, BigInt b, string &decimal);

double Divider(BigInt a, BigInt b);

double BigInt_to_Double(BigInt whole_num, string matissa);

double Divide(BigInt a, BigInt b);

BigInt FindMidPoint(BigInt upper, BigInt lower);

BigInt NextBinaryFinder(BigInt lower_bound, BigInt upper_bound);

unsigned int FactorDifference(BigInt first, BigInt other);



#endif