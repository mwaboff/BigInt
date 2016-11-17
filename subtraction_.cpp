//===-----------------------------------------------------------------------===//
//
//  Project 1: Big Integer Arithmetic
//  Authors: Michael Aboff, Mauricio Ferrato, Darsh Patel, Edwin Ortiz,
//           Eric Wright
//
//===----------------------------------------------------------------------===//
//
//  subtraction.cpp
//    Module for subtraction with BigInt data structures.
//
//===----------------------------------------------------------------------===//

#include <iostream>
#include "big_int.h"
#include "super_array.h"
#include "subtraction.h"
using namespace std;

// A helper function made to carry 1 from a larger "chunk" in the BigInt to assist
// with subtraction to prevent individual chunk subtraction from resulting in
// negative numbers. Removes one from the next chunk and adds it multiplied by
// the base to the current chunk.
//
// Parameters:
//   SuperArray &s_array - The SuperArray we are working with.
//   int index - The index of the chunk that needs to bring 1 down from its superior.
SuperArray Borrow(SuperArray s_array, int index){
    // cout << "entering borrow" << endl;
    // cout << "before" << endl;
    // s_array.Print();
    // Check there is something to take in the next chunk. Otherwise we recursively
    // "borrow" from each next chunk until we can.
    if (s_array.Get(index + 1) > 0){
        s_array.Set(index, s_array.Get(index) + BigInt::GetBase());
        s_array.Set(index + 1, s_array.Get(index + 1) - 1);
    } else {
        Borrow(s_array, index + 1);
        s_array.Set(index, s_array.Get(index) + BigInt::GetBase());
        s_array.Set(index + 1, s_array.Get(index + 1) - 1);
    }
}

// Subtract a larger BigInt from the smaller one.
//
// Parameters:
//   BigInt larger - The larger BigInt to subtract from.
//   BigInt smaller - The BigInt to subtract from the larger one.
//
// Returns:
//   SuperArray - A SuperArray containing the difference.
//
// Note:
//   This function requires the BigInt b is smaller than BigInt a.
SuperArray SubtractSmallerFromLarger(BigInt larger, BigInt smaller){
    // Using SuperArrays because they are easier to manipulate.
    SuperArray largerone = larger.GetValue(); // No new memory allocated
    SuperArray smallerone = smaller.GetValue(); // No new memory allocated
    SuperArray larger_array = SuperArray(largerone); // ALLOCATES NEW MEMORY
    SuperArray smaller_array = SuperArray(smallerone); // ALLOCATES NEW MEMORY

    // result_array will need just as much memory as the larger SuperArray
    SuperArray result_array = SuperArray(larger_array.Length()); // ALLOCATES NEW MEMORY, WIL BE RETURNED

    int i = 0;
    for(; i < smaller_array.Length(); i++){
        if (larger_array.Get(i) < smaller_array.Get(i)){
            // a - b would result in a negative, we will borrow to avoid this issue.
            Borrow(larger_array, i);
            result_array.Set(i, larger_array.Get(i) - smaller_array.Get(i));
            result_array.IncreaseReal();
        } else { // if a >= b you do not have to borrow
            result_array.Set(i, larger_array.Get(i) - smaller_array.Get(i));
            result_array.IncreaseReal();
        }
    }

    // We haven't accounted for everything in larger_array.
    // Loop through the rest of larger_array, and add it to the result.
    for(; i < larger_array.Length(); i++){
        result_array.Set(i, larger_array.Get(i));
        result_array.IncreaseReal();
    }

    larger_array.Release(); // MEMORY UNALLOCATED
    smaller_array.Release(); // MEMORY UNALLOCATED

    result_array.UpdateSize(); // RESULT RETURNED
    return result_array;
}

// Subtract a larger BigInt from the smaller one.
//
// Parameters:
//   BigInt int_1 - A positive BigInt.
//   BigInt int_2 - Another positive BigInt.
//
// Returns:
//   SuperArray - A SuperArray containing the difference.
//
// Note:
//   For now, both bigints must be positive.
const BigInt Subtract(const BigInt int_1, const BigInt int_2){

    BigInt result = BigInt(); // ALLOCATES ONE INT OF MEMORY
    result.MakeEmpty(); // FREES THAT MEMORY

    // If int_1 is greater than int_2, the result will be positive. Otherwise,
    // it will be negative. We set the result's positivity flag to reflect this
    // and call the subtraction method providing the inputs in the necessary order.
    if(GreaterOrEqual(int_1, int_2)){
        result.SetSign(true);
        result.SetValue(SubtractSmallerFromLarger(int_1, int_2));
    } else {
        result.SetSign(false);
        result.SetValue(SubtractSmallerFromLarger(int_2, int_1));
    }

    return result; // Result will have new memory allocated
}