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
    SuperArray array = a.GetValue();
    unsigned int allocate_space = array.Length();
    if(array.Get(array.Length() - 1) == 1){ // if last element is 1
        skip_first = true;
    }

    SuperArray new_num = SuperArray(allocate_space); // make a new super array, we know how much space we need
    for (int i = array.Length() - 1; i >= 0; i--){
        if (remain){
            apple = array.Get(i) + BigInt::GetBase();
        } else {
            apple = array.Get(i);
        }

        remain = apple % 2; // will either be a 0 or a 1
        sol = apple / 2; // the value we are storing

        if(i >= 0 && !skip_first){ // skip if first value was a 1
            new_num.Set(i, sol); // set new_num at i to apple / 2
            new_num.IncreaseReal(); // increase real size by 1
        }
    skip_first = false; // only ever skip the first one
    }
}


BigInt FindQuotient(BigInt a, BigInt b){
    BigInt counts = BigInt("0");
    BigInt first = BigInt();
    BigInt second = BigInt();
    SuperArray first_a = SuperArray(a.GetValue());
    SuperArray second_a = SuperArray(b.GetValue());
    first.SetValue(first_a);
    second.SetValue(second_a);
    BigInt one = BigInt("1");
    if (BigIntCompare(a, b) == 0){
        return one;
    } else if (BigIntCompare(a, b) == -1){
        return counts;
    }

    counts = one;

     while(BigIntCompare(second, first) == -1){
        counts = Multiply(counts, 2, 0);
        second = Multiply(second, 2, 0);
    }

    while (BigIntCompare(second, first) == 1){
        second = Subtract(second, b);
        counts = Subtract(counts, one);
    }

    return counts;
}

BigInt FindQuotient(BigInt a, BigInt b, BigInt &r){
    BigInt counts = BigInt("0");
    BigInt first = BigInt();
    BigInt second = BigInt();
    SuperArray first_a = SuperArray(a.GetValue());
    SuperArray second_a = SuperArray(b.GetValue());
    first.SetValue(first_a);
    second.SetValue(second_a);
    BigInt one = BigInt("1");
    if (BigIntCompare(a, b) == 0){
        return one;
    } else if (BigIntCompare(a, b) == -1){
        return counts;
    }

    counts = one;

     while(BigIntCompare(second, first) == -1){
        counts = Multiply(counts, 2, 0);
        second = Multiply(second, 2, 0);
    }

    while (BigIntCompare(second, first) == 1){
        second = Subtract(second, b);
        counts = Subtract(counts, one);
    }

    r = a - second;

    return counts;
}


void DivideRemainder(BigInt &remaining, BigInt b, string &decimal){
    remaining = Multiply(remaining, BigInt::GetBase(), 0);
    BigInt quotient = FindQuotient(remaining, b);
    remaining = Subtract(remaining, Product(b, quotient));
    decimal += quotient.ToString();

}


double Divider(BigInt a, BigInt b){
    BigInt big_int_zero = BigInt("0");
    string decimal = "";
    BigInt remaining;
    BigInt quotient = FindQuotient(a, b, remaining);
   // quotient.DebugPrint();

    //remaining.DebugPrint();

    while (0 != BigIntCompare(remaining, big_int_zero) && !(decimal.length() >= 16)){

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