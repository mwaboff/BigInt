//===-----------------------------------------------------------------------===//
//
//  Project 1: Big Integer Arithmetic
//  Authors: Michael Aboff, Mauricio Ferrato, Darsh Patel, Edwin Ortiz,
//           Eric Wright
//
//===----------------------------------------------------------------------===//
//
//  subtraction.h
//    Header file for subtraction.cpp
//
//===----------------------------------------------------------------------===//

#ifndef SUBTRACTION_H
#define SUBTRACTION_H

#include <iostream>
#include "big_int.h"
#include "super_array.h"
using namespace std;

SuperArray Borrow(SuperArray &s_array, int index);
SuperArray SubtractSmallerFromLarger(BigInt);
const BigInt Subtract(const BigInt, const BigInt); // both bigints must be positive

#endif // SUBTRACTION_H