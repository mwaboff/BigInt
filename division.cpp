//===-----------------------------------------------------------------------===//
//
//  Project 1: Big Integer Arithmetic
//  Authors: Michael Aboff, Mauricio Ferrato, Darsh Patel, Edwin Ortiz,
//           Eric Wright
//
//===----------------------------------------------------------------------===//
//
//  division.cpp
//    Module for division of BigInt data structures.
//
//===----------------------------------------------------------------------===//

#include <iostream>
#include <string>
#include <sstream>
#include "addition.h"
#include "subtraction.h"
#include "multiplication.h"
#include "big_int.h"
#include "super_array.h"
#include <algorithm>
using namespace std;

    /*
     * I feel the need to apologize for this function. We can't figure out why this
     * works and we've spent literally 3 hours on this one bug. That no longer
     * seems to be a problem. God forgive us.
     */

BigInt DivideByTwo(BigInt a){
    int remain = 0; // how much is carried over
    unsigned int apple; // where the value from the array is stored
    unsigned int sol; // where apple / 2 is stored
    bool skip_first = false; // will only be true if the last element of array is 1
    vector<int> array = a.GetValue();
    unsigned int allocate_space = array.size();
    if(array.at(array.size() - 1) == 1){ // if last element is 1
        skip_first = true;
    }

    vector<int> new_num; // make a new super array, we know how much space we need
    for (int i = array.size() - 1; i >= 0; i--){
        if (remain){
            apple = array.at(i) + BigInt::GetBase();
        } else {
            apple = array.at(i);
        }

        remain = apple % 2; // will either be a 0 or a 1
        sol = apple / 2; // the value we are storing

        if(i >= 0 && !skip_first){ // skip if first value was a 1
            new_num.push_back(sol);
        }
    skip_first = false; // only ever skip the first one
    }
    reverse(new_num.begin(), new_num.end());
    BigInt returnBigInt = BigInt(new_num);

    return returnBigInt;
}

unsigned int FactorDifference(BigInt first, BigInt other) {
    unsigned int our_data_len = first.GetValue().size();
    unsigned int other_data_len = other.GetValue().size();
    unsigned int our_first_chunk_len = to_string(first.GetValue().at(our_data_len - 1)).length();
    unsigned int other_first_chunk_len = to_string(other.GetValue().at(other_data_len - 1)).length();
    unsigned int our_scale = (our_data_len * BigInt::chunk_size) + our_first_chunk_len;
    unsigned int other_scale = (other_data_len * BigInt::chunk_size) + other_first_chunk_len;
    if(other_scale > our_scale) {
        return other_scale - our_scale;
    } else {
        return our_scale - other_scale;
    }
}

BigInt NextBinaryFinder(BigInt lower_bound, BigInt upper_bound) {
    // Call this on the lower bound only pls when transfering this to the division file
    // change it to NextBinaryFinder(BigInt lower_bound, BigInt upper_bound);
    BigInt range = Subtract(upper_bound, lower_bound);
    BigInt half_range = DivideByTwo(range);
    BigInt new_coeff = Add(lower_bound, half_range);
    return new_coeff;
}

BigInt FindQuotient(BigInt smaller, BigInt other) {
    BigInt one = BigInt("1");
    BigInt zero = BigInt("0");

    if(BigIntCompare(smaller, other) == 1) {
        return zero;
    }

    unsigned int factor_diff = FactorDifference(smaller, other);


    BigInt lower_coeff = BigInt("0");
    BigInt upper_coeff = BigInt("1");

    for(int i = 0; i < factor_diff + 1; i++) {
        upper_coeff = Multiply(upper_coeff, 10, 0);
    }

    BigInt coeff = NextBinaryFinder(lower_coeff, upper_coeff);

    BigInt diff_of_coeffs = Subtract(upper_coeff, lower_coeff);

    int iterations = 0;

    /*cout << "lower_coeff = " << lower_coeff << endl;
    cout << "upper_coeff = " << upper_coeff << endl;
    cout << "coeff =       " << coeff << endl;*/

    while(BigIntCompare(diff_of_coeffs, one)) {
        iterations++;
        BigInt curr_val = Product(smaller, coeff);
        switch(BigIntCompare(curr_val, other)) {
            case 0:
                return coeff;
                break;
            case 1:
                upper_coeff = coeff;
                coeff = NextBinaryFinder(lower_coeff, upper_coeff);
                break;
            case -1:
                lower_coeff = coeff;
                coeff = NextBinaryFinder(lower_coeff, upper_coeff);
                break;
        }

        /*cout << "lower_coeff = " << lower_coeff.ToString() << endl;
        cout << "upper_coeff = " << upper_coeff.ToString() << endl;
        cout << "coeff =       " << coeff.ToString() << endl;*/
        BigInt diff_of_coeffs = Subtract(upper_coeff, lower_coeff);
        //cout << coeff << endl;
        if(BigIntCompare(diff_of_coeffs, one) < 1) {
            return coeff;
        }
        //cin.ignore();
    }
    return coeff;
}

void DivideRemainder(BigInt &remaining, BigInt b, string &decimal){
    remaining = Multiply(remaining, BigInt::GetBase(), 0);
    BigInt quotient = FindQuotient(b, remaining);
    remaining = Subtract(remaining, Product(b, quotient));
    string temp = quotient.ToString();
    int zeros = BigInt::chunk_size - temp.length();
    for (int i = 0; i < zeros; i++){
        decimal += '0';
    }
    decimal += temp;

}


double Divider(BigInt a, BigInt b){
    BigInt big_int_zero = BigInt("0");
    string decimal = "";
    BigInt remaining;
    BigInt quotient = FindQuotient(b, a);
    remaining = Subtract(a, Product(b, quotient));
   // quotient.DebugPrint();

    //remaining.DebugPrint();

    while (0 != BigIntCompare(remaining, big_int_zero) && (decimal.length() <= 16)){

        DivideRemainder(remaining, b, decimal);
       // remaining.DebugPrint();
    }
    return BigInt_to_Double(quotient, decimal);
}

double Divide(BigInt a, BigInt b){
    double answer;
    bool ap = a.IsPositive();
    bool bp = b.IsPositive();

    if (ap && bp){
        answer = Divider(a, b);
        return answer;
    } else if (!ap && !bp){
        answer = Divider(a, b);
        return answer;
    } else {
        answer = Divider(a, b);
        answer *= -1;
        return answer;
    }
}

double BigInt_to_Double(BigInt whole_num, string matissa){
    string characteristic = "";
    string fraction = "";
    double result;

    // Converts BigInt to string (whole number)
    characteristic += whole_num.ToString();

    // Combines whole number and decimal together
    fraction += characteristic + "." + matissa;
/*
    // Converts string fraction to double
    istringstream i(fraction);
    if(!(i >> result)) return 0;
    */
    return stold(fraction);


    return result;
}