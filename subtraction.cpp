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
#include "subtraction.h"
using namespace std;

void UpdateSize(vector<int> &vec){
    if ((vec.at(vec.size() - 1) == 0) && vec.size() > 1){
        vec.pop_back();
        UpdateSize(vec);
    } else {
        return;
    }
}

// A helper function made to carry 1 from a larger "chunk" in the BigInt to assist
// with subtraction to prevent individual chunk subtraction from resulting in
// negative numbers. Removes one from the next chunk and adds it multiplied by
// the base to the current chunk.
//
// Parameters:
//   vector<int> &s_array - The vector<int> we are working with.
//   int index - The index of the chunk that needs to bring 1 down from its superior.
void Borrow(vector<int> &s_array, int index){
    // cout << "entering borrow" << endl;
    // cout << "before" << endl;
    // s_array.Print();
    // Check there is something to take in the next chunk. Otherwise we recursively
    // "borrow" from each next chunk until we can.
    if (s_array.at(index + 1) > 0){
        s_array[index] = s_array.at(index) + BigInt::GetBase();
        s_array[index + 1] = s_array.at(index + 1) - 1;
    } else {
        Borrow(s_array, index + 1);
         s_array[index] = s_array.at(index) + BigInt::GetBase();
        s_array[index + 1] = s_array.at(index + 1) - 1;
    }
    if (s_array.at(s_array.size() - 1) == 0){
        s_array.pop_back();
    }
    return;
}

// Subtract a larger BigInt from the smaller one.
//
// Parameters:
//   BigInt larger - The larger BigInt to subtract from.
//   BigInt smaller - The BigInt to subtract from the larger one.
//
// Returns:
//   vector<int> - A vector<int> containing the difference.
//
// Note:
//   This function requires the BigInt b is smaller than BigInt a.
vector<int> SubtractSmallerFromLarger(BigInt larger, BigInt smaller){
    // Using vector<int>s because they are easier to manipulate.
    vector<int> larger_array = larger.GetValue(); // No new memory allocated
    vector<int> smaller_array = smaller.GetValue(); // No new memory allocated

    // result_array will need just as much memory as the larger vector<int>
    vector<int> result_array; // ALLOCATES NEW MEMORY, WIL BE RETURNED

    int i = 0;
    for(; i < smaller_array.size(); i++){
        if (larger_array.at(i) < smaller_array.at(i)){
            // a - b would result in a negative, we will borrow to avoid this issue.
            Borrow(larger_array, i);
            result_array.push_back(larger_array.at(i) - smaller_array.at(i));
        } else { // if a >= b you do not have to borrow
            result_array.push_back(larger_array.at(i) - smaller_array.at(i));
        }
    }

    // We haven't accounted for everything in larger_array.
    // Loop through the rest of larger_array, and add it to the result.
    for(; i < larger_array.size(); i++){
        result_array.push_back(larger_array.at(i));
    }

    UpdateSize(result_array);
    return result_array;
}

// Subtract a larger BigInt from the smaller one.
//
// Parameters:
//   BigInt int_1 - A positive BigInt.
//   BigInt int_2 - Another positive BigInt.
//
// Returns:
//   vector<int> - A vector<int> containing the difference.
//
// Note:
//   For now, both bigints must be positive.
const BigInt Subtract(const BigInt int_1, const BigInt int_2){

    BigInt result = BigInt(); // ALLOCATES ONE INT OF MEMORY

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