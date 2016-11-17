//===-----------------------------------------------------------------------===//
//
//  Project 1: Big Integer Arithmetic
//  Authors: Michael Aboff, Mauricio Ferrato, Darsh Patel, Edwin Ortiz,
//           Eric Wright
//
//===----------------------------------------------------------------------===//
//
//  addition.cpp
//    Module for addition with BigInt data structures
//
//===----------------------------------------------------------------------===//

#include <iostream>
#include "big_int.h"
#include "super_array.h"
#include "addition.h"
using namespace std;

// Build the resulting BigInt after. Should only be called by Add().
//
// Parameters:
//   SuperArray larger - The larger of the two inputs.
//   SuperArray smaller - The smaller of the two inputs.
//   bool same_size - A boolean passed to cut down the work necessary in this
//                    function.
//
// Returns:
//   BigInt - A BigInt that contains the sum of the larger and smaller arrays.
//
// Note:
//   The order of the parameters is important because in order to add the two
//   SuperArrays of different "chunk" length, we need to add the extra chunks of
//   the larger directly to the resulting BigInt's SuperArray without running
//   into an out-of-bounds error with the smaller SuperArray.


BigInt AddChunks(SuperArray larger, SuperArray smaller, bool same_size) {
    cout << "Result array created" << endl;
    SuperArray result = SuperArray(); // SUPER ARRAY CREATED
    int carry = 0;
    for(int i = 0; i < smaller.Length(); i++) {
        unsigned int temp_num = smaller.Get(i) + larger.Get(i);

        if(carry) {
            temp_num += carry;
            carry = 0;
        }

        if(temp_num >= BigInt::GetBase()) {
            carry = 1;
            temp_num = temp_num % BigInt::GetBase();
        }
        cout << "Result pushed" << endl;
        result.Push(temp_num);
    }

    if(!same_size) {
        for(int i = smaller.Length(); i < larger.Length(); i++) {
            unsigned int temp_num = larger.Get(i);

            if(carry) {
                temp_num += carry;
                carry = 0;
            }

            if(temp_num >= BigInt::GetBase()) {
                carry = 1;
                temp_num = temp_num % BigInt::GetBase();
            }
            cout << "Result pushed" << endl;
            result.Push(temp_num);
        }
    }

    if(carry > 0) {
        result.Push(carry);
    }
    cout << "BigInt result_bigint created" << endl;
    BigInt result_bigint = BigInt(result); // BIG INT CREATED
    cout << "Result array released" << endl;
    result.Release(); // FREE ORIGINAL

    return result_bigint;
}

// Add two BigInt data structures together. Calls AddChunks() to build the result.
//
// Parameters:
//   BigInt num_1 - First BigInt to add.
//   BigInt num_2 - Second BigInt to add.
//
// Returns:
//   BigInt - Built by the AddChunks() function.
BigInt Add(BigInt num_1, BigInt num_2){
    SuperArray num_1_array = num_1.GetValue(); // No new memory allocated
    SuperArray num_2_array = num_2.GetValue(); // No new memory allocated

    if(num_2_array.Length() == num_1_array.Length()){
        return AddChunks(num_2_array, num_1_array, true);
    }else if(num_2_array.Length() > num_1_array.Length()){
        return AddChunks(num_2_array, num_1_array, false);
    } else {
        return AddChunks(num_1_array, num_2_array, false);
    }
}