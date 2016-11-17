//===-----------------------------------------------------------------------===//
//
//  Project 1: Big Integer Arithmetic
//  Authors: Michael Aboff, Mauricio Ferrato, Darsh Patel, Edwin Ortiz,
//           Eric Wright
//
//===----------------------------------------------------------------------===//
//
//  addition.h
//    Header file for addition.cpp
//
//===----------------------------------------------------------------------===//

#ifndef ADDITION_H
#define ADDITION_H

#include <iostream>
#include "big_int.h"
#include "super_array.h"
using namespace std;

BigInt Add(BigInt input1, BigInt input2);
BigInt AddChunks(vector<int> larger, vector<int> smaller, bool same_size);

#endif // ADDITION_H