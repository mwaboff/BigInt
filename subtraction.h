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
using namespace std;

void Borrow(vector<int> &s_array, int index);
vector<int> SubtractSmallerFromLarger(BigInt);
const BigInt Subtract(const BigInt, const BigInt); // both bigints must be positive
void UpdateSize(vector<int> &vec);

#endif // SUBTRACTION_H