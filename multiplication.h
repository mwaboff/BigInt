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

#ifndef MULTIPLICATION_H
#define MULTIPLICATION_H

#include <iostream>
#include "big_int.h"
#include "addition.h"

BigInt Multiply(BigInt big_int, int, int shift_amount);
BigInt Product(BigInt input1, BigInt input2);

#endif // MULTIPLICATION_H