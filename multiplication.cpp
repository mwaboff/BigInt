//===-----------------------------------------------------------------------===//
//
//  Project 1: Big Integer Arithmetic
//  Authors: Michael Aboff, Mauricio Ferrato, Darsh Patel, Edwin Ortiz,
//           Eric Wright
//
//===----------------------------------------------------------------------===//
//
//  multiplication.cpp
//    Module for multiplication with BigInt data structures.
//
//===----------------------------------------------------------------------===//

#include <iostream>
#include "big_int.h"
#include "addition.h"
#include "multiplication.h"

// Multiplies a BigInt with an integer.
//
// Parameters:
//   BigInt big_num - The BigInt to multiply.
//   int input - The integer to multiply with the BigInt.
//   int shift_amount - How many zeroes to append to the result, left-shifting the result.
//
// Returns:
//   BigInt - The product of the input BigInt, the integer, and any shifting operation.
//
// Note:
//   Providing a negative number to shift_ammount will not shift the result.
BigInt Multiply(BigInt big_num, int input, int shift_ammount){
    vector<int> answer_so_far; // MEMORY ALLOCATED
    for (int i = 0; i < shift_ammount; i++){
        answer_so_far.push_back(0);
    }
    int carry_over = 0;
    for (int i=0; i< big_num.GetValue().size(); i++){
        int val = big_num.GetValue().at(i);
        val *= input;
        val += carry_over;
        carry_over = val / BigInt::GetBase(); // front digits
        val = val % BigInt::GetBase(); // last base digits

        answer_so_far.push_back(val);
    }
    if (carry_over > 0){
        answer_so_far.push_back(carry_over);
    }
    BigInt answer = BigInt(answer_so_far); // ALLOCATES NEW MEMORY
    return answer;
}

// Multiplies a BigInt with another BigInt.
//
// Parameters:
//   BigInt input1 - The BigInt to multiply.
//   BigInt input2 - The other BigInt to multiply with the BigInt.
//
// Returns:
//   BigInt - The product of both input BigInts.
BigInt Product(BigInt input1, BigInt input2){
    BigInt answer_so_far = BigInt(); // ALLOCATES MEMORY
    BigInt temp = BigInt(); // ALLOCATES MEMORY
    vector<int> first_array = input1.GetValue();
    vector<int> other_array = input2.GetValue();

    // If both BigInts have the same number of chunks,
    if(other_array.size() <= first_array.size()){
        for(int i = 0; i < other_array.size(); ++i){
            temp = Multiply(input1, other_array.at(i), i);
            answer_so_far = Add(answer_so_far, temp);
        }
      return answer_so_far;
      }
      else{
          for(int i = 0; i < first_array.size(); ++i){
              temp = Multiply(input2, first_array.at(i), i);
              answer_so_far = Add(answer_so_far, temp);
     }
     return answer_so_far;

    }
}