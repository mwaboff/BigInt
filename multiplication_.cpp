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
#include "super_array.h"
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
    SuperArray answer_so_far = SuperArray(); // MEMORY ALLOCATED
    for (int i = 0; i < shift_ammount; i++){
        answer_so_far.Push(0);
    }
    int carry_over = 0;
    for (int i=0; i< big_num.GetValue().Length(); i++){
        int val = big_num.GetValue().Get(i);
        val *= input;
        val += carry_over;
        carry_over = val / BigInt::GetBase(); // front digits
        val = val % BigInt::GetBase(); // last base digits

        answer_so_far.Push(val);
    }
    if (carry_over > 0){
        answer_so_far.Push(carry_over);
    }
    BigInt answer = BigInt(answer_so_far); // ALLOCATES NEW MEMORY
    answer_so_far.Release();
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
    answer_so_far.MakeEmpty();
    BigInt temp = BigInt(); // ALLOCATES MEMORY
    temp.MakeEmpty(); // FREE
    SuperArray first_array = input1.GetValue();
    SuperArray other_array = input2.GetValue();

    // If both BigInts have the same number of chunks,
    if(other_array.Length() <= first_array.Length()){
        for(int i = 0; i < other_array.Length(); ++i){
            temp = Multiply(input1, other_array.Get(i), i);
            temp = Add(answer_so_far, temp);
            answer_so_far.MakeEmpty();

            answer_so_far = temp;

            temp.MakeEmpty();
        }
        temp.MakeEmpty();
      answer_so_far.GetSuperArray()->UpdateSize();
      return answer_so_far;
      }
      else{
          for(int i = 0; i < first_array.Length(); ++i){
              temp = Multiply(input2, first_array.Get(i), i);
              temp = Add(answer_so_far, temp);
              answer_so_far.MakeEmpty();

              answer_so_far = temp;

              temp.MakeEmpty(); // free up temp as often as possible
     }
     temp.MakeEmpty(); // Free up temp
     answer_so_far.GetSuperArray()->UpdateSize();
     return answer_so_far;

    }
}