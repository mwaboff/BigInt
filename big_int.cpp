//===-----------------------------------------------------------------------===//
//
//  Project 1: Big Integer Arithmetic
//  Authors: Michael Aboff, Mauricio Ferrato, Darsh Patel, Edwin Ortiz,
//           Eric Wright
//
//===----------------------------------------------------------------------===//
//
//  big_int.cpp
//    Defines the BigInt class.
//
//===----------------------------------------------------------------------===//

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <math.h>
#include "big_int.h"
#include <vector>
#include "subtraction.h"
#include "addition.h"
#include "multiplication.h"
#include "division.h"
using namespace std;

// This is the largest integer that you can handle with 32-bits 2^32 - 1
const unsigned int max = 4294967295;

// Constants that define how we organize the "chunks" that let us break large
// integers into manageable smaller numbers.
// For example, if chunk_size is 4, then each chunk can only be a max of 4 characters
// long. The chunk would operate in base 10000, where the largest number is
// 9999 before flipping back to 0000.
//
// Please refer to the super_array.cpp documentation for more information about
// how the data is broken up into chunks.
int BigInt::chunk_size = 4;
int BigInt::base = pow(10, chunk_size);

// Constructor function when no parameters are passed.
//
// Note:
//   BigInts are positive by default.
//
//   The Value is set to an empty SuperArray by default.
BigInt::BigInt(){ // allocated memory for one integer
    positive = true;
    vector<int> value;
}

// Constructor function when a string is passed.
//
// Parameters:
//   string numStr - numStr must be a string of integers. The string will be
//                   converted to integers as it is converted into a SuperArray.
//
// Note:
//   If numStr contains non-integer characters, unpredictable behavior may occur.
BigInt::BigInt(string numStr){
    if(numStr.at(0) == '-'){
        positive = false;
    } else {
        positive = true;
    }

    int strSize = numStr.size(); // how many digits are we working with

    while (true) {
        if (strSize <= 0) break; // stop when we're out of characters
        if (strSize <= 1 && !positive) break;

        int length = 0; // how many digits are we currently using, will be between 0 and 9
        int num = 0; // the integer we're finding from the string
        int prefix = 1; // this is the base, like 10^0, 10^1, 10^2 et cetera
        for (int i = (strSize - 1); i >= 0 && i >= strSize - chunk_size; --i) { // grab 9 characters, starting from the back
            if (numStr.at(i) < '0' || numStr.at(i) > '9') break;
            num += (numStr.at(i) - '0') * prefix; // convert the char to an int, and move over by a power of 10
            prefix *= 10; // increase the power of 10
            ++length; // how much to take off of size each time, 0 to 9
        }

        value.push_back(num);
        strSize -= length; // remove length of num from overall size
    }
}

BigInt::BigInt(vector<int> vec){
    positive = true;
    value = vec;
}


// Read a string integers from a provided file. The string is converted into a BigInt.
//
// Parameters:
//   string fileName - The name of a file containing a string of integers.
//
// Returns:
//   BigInt - Converts the string of integers into an instance of BigInt.
BigInt ReadFromFile(string fileName){
    BigInt big_int;
    string numStr; // Where the text in the file will be stored.
    ifstream myfile (fileName.c_str()); // Open up the file.

    getline(myfile, numStr); // Getline from file, transfer to numStr.
    myfile.close(); // Close the file, very important to prevent file corruption
                    // and memory leaks.

    big_int = BigInt(numStr);
    return big_int;
}

// Function intended to "reset" data associated with the BigInt instance.
//
// Note:
//   This is not a function that frees the memory allocated to the instance.
void BigInt::MakeEmpty() {
    value.clear();
    positive = true;
   return;
}

// Deconstructor function automatically called when the BigInt instance is deleted.
BigInt::~BigInt() {
}

// "Getter" function that reports whether or not the BigInt is positive or not.
//
// Returns:
//   bool
//     true - Returns true if BigInt is positive.
//     false - Returns false if BigInt is negative.
//
// Note:
//   This function is preferred instead of accessing BigInt::positive directly.
bool BigInt::IsPositive(){
   return positive;
}

// Sets the BigInt instance's positivity to a user specified input.
//
// Parameters:
//   bool positivity - Set to true if BigInt should be positive.
//                     Set to false if BigInt should be negative.
void BigInt::SetSign(bool positivity){
    this->positive = positivity;
    return;
}

// Changes the BigInt instance's positivity to the opposite of its current value.
void BigInt::FlipSign(){
    if (IsPositive()){
        SetSign(false);
    } else {
        SetSign(true);
    }
    return;
}

// Set the value of the BigInt instance (stored in a SuperArray) to a provided SuperArray.
//
// Parameters:
//   SuperArray new_value - A SuperArray datastructure.
void BigInt::SetValue(vector<int> new_value){
    value = new_value;
    return;
}

// Print the value of BigInt stored in the SuperArray.
//
// Note:
//   SuperArray stores its "chunks" in a backwards manner. Please refer to the
//   documentation in super_array.cpp for more information about the structure.
void BigInt::Print(){
    string result;
    if(!this->IsPositive()) {
        cout << "-";
    }

    // The following section is designed to ensure that the correct amount of zeros
    // are present when outputing the value of each "chunk".

    // This "chunk" is actually the first few digits of the number. We do not
    // want preceeding zeros to be displayed so we skip the zero-ensuring process.
    cout << value.at(value.size() - 1);

    int zeros_to_add = 0;
    for(int i = value.size() - 2; i >= 0; i--) {

        // Convert the integer to a string so we can take advantage of length()
        // and string concatonation to ensure the correct display of zeros.
        result = to_string(value.at(i));
        zeros_to_add = (chunk_size - result.length());
        for(int j = 0; j < zeros_to_add; j++){
            cout << "0";
        }
        cout << result;
    }
    cout << endl;
    return;
}

// Returns a pointer to super array, so it can be changed.
//
// Returns:
//   SuperArray - The SuperArray storing the value of the BigInt.
vector<int> BigInt::GetValue(){
    return value;
}

// Override the + operator.
//
// Notes:
//   Please refer to these sites for more information on overriding operators:
//     http://www.learncpp.com/cpp-tutorial/91-introduction-to-operator-overloading/
//     http://faculty.cs.niu.edu/~mcmahon/CS241/Notes/arithmetic.html
BigInt operator+(const BigInt &bigInt1, const BigInt &bigInt2)
{
    BigInt returnInt;
    if(bigInt1.positive && bigInt2.positive){
        returnInt = Add(bigInt1, bigInt2);
        return returnInt;
    } else if (bigInt1.positive && !bigInt2.positive){
        returnInt = Subtract(bigInt1, bigInt2);
        return returnInt;
    } else if (!bigInt1.positive && bigInt2.positive){
        returnInt = Subtract(bigInt1, bigInt2);
        returnInt.FlipSign();
        return returnInt;
    } else {
        returnInt = Add(bigInt1, bigInt2);
        returnInt.SetSign(false);
        return returnInt;
    }
}

// Override the - operator.
//
// Notes:
//   Please refer to these sites for more information on overriding operators:
//     http://www.learncpp.com/cpp-tutorial/91-introduction-to-operator-overloading/
//     http://faculty.cs.niu.edu/~mcmahon/CS241/Notes/arithmetic.html
BigInt operator-(const BigInt &bigInt1, const BigInt &bigInt2){
    BigInt returnInt;
    if (bigInt1.positive && bigInt2.positive){
        returnInt = Subtract(bigInt1, bigInt2);
        return returnInt;
    } else if (!(bigInt1.positive) && bigInt2.positive){
        returnInt = Add(bigInt1, bigInt2);
        returnInt.FlipSign();
        return returnInt;
    } else if (bigInt1.positive && !(bigInt2.positive)){
        returnInt = Add(bigInt1, bigInt2);
        return returnInt;
    } else {
        returnInt = Subtract(bigInt1, bigInt2);
        returnInt.FlipSign();
        return returnInt;
    }
}

// Override the * operator.
//
// Notes:
//   Please refer to these sites for more information on overriding operators:
//     http://www.learncpp.com/cpp-tutorial/91-introduction-to-operator-overloading/
//     http://faculty.cs.niu.edu/~mcmahon/CS241/Notes/arithmetic.html
BigInt operator*(const BigInt &bigInt1, const BigInt &bigInt2){
    BigInt returnInt;
    if (bigInt1.positive && bigInt2.positive){
        returnInt = Product(bigInt1, bigInt2);

    } else if (!bigInt1.positive && !bigInt2.positive){
        returnInt = Product(bigInt1, bigInt2);

    } else {
        returnInt = Product(bigInt1, bigInt2);
        returnInt.FlipSign();
    }
    return returnInt;
}

bool GreaterOrEqual(BigInt b1, BigInt b2){

    if (b1.GetValue().size() > b2.GetValue().size()){
        return true;
    } else if (b1.GetValue().size() < b2.GetValue().size()){
        return false;
    } else{
        for(int i = b1.GetValue().size() - 1; i >= 0; i--){
            if (b1.GetValue().at(i) > b2.GetValue().at(i)){
                return true;
            } else if (b1.GetValue().at(i) < b2.GetValue().at(i)){
                return false;
            }
        }
        return true;
    }
}

// Compares the values of two BigInts.
//
// Parameters:
//   BigInt b1 - The first BigInt.
//   BigInt b2 - The second BigInt to test.
//
// Returns:
//   int
//     1 - b1 is GREATER than b2.
//     0 - b1 is EQUAL to b2.
//     -1 - b1 is LESS than b2.
int BigIntCompare(BigInt b1, BigInt b2){

    if (b1.GetValue().size() > b2.GetValue().size()){
        return 1;
    } else if (b1.GetValue().size() < b2.GetValue().size()){
        return -1;
    } else{
        for(int i = b1.GetValue().size() - 1; i >= 0; i--){
            if (b1.GetValue().at(i) > b2.GetValue().at(i)){
                return 1;
            } else if (b1.GetValue().at(i) < b2.GetValue().at(i)){
                return -1;
            }
        }
        return 0;
    }

}

const string BigInt::ToString(){
    string returnStr = ""; // intialize an empty string
    unsigned int first_val = value.at(value.size() - 1); // grab last element
    returnStr += to_string(first_val); // ad the first value, as a string, to returnStr

    for (int i = value.size() - 2; i >= 0; i--){ // loop through backwards, skip first element
        int num = value.at(i); // grab val at i
        string temp = to_string(num); // convert it to a string
        int zeros = chunk_size - temp.length(); // find the difference between chunk_size and length
        for (int i = 0; i < zeros; i++){ // add 0's for that difference
            returnStr += '0';
        }
        returnStr += temp; // append temp value with zeros

    }
    return returnStr; // return
}

ostream& operator<<(ostream& os, const BigInt &andy){

    string returnStr = ""; // intialize an empty string
    if (!andy.positive){
        returnStr += '-';
    }
    unsigned int first_val = andy.value.at(andy.value.size() - 1); // grab last element
    returnStr += to_string(first_val); // ad the first andy.value, as a string, to returnStr

    for (int i = andy.value.size() - 2; i >= 0; i--){ // loop through backwards, skip first element
        int num = andy.value.at(i); // grab val at i
        string temp = to_string(num); // convert it to a string
        int zeros = andy.chunk_size - temp.length(); // find the difference between chunk_size and length
        for (int i = 0; i < zeros; i++){ // add 0's for that difference
            returnStr += '0';
        }
        returnStr += temp; // append temp value with zeros

    }
    os << returnStr;
    return os;
}

istream& operator>>(istream& is, BigInt &andy){

    string novac;
    is >> novac;
    andy = BigInt(novac);

    return is;
}

void BigInt::Push(int val){
    value.push_back(val);
    return;
}

void BigInt::Set(int index, int val){
    value[index] = val;
    return;
}

void BigInt::WriteToFile(string filename){
    ofstream myfile;
    myfile.open (filename);
    myfile << *this;
    myfile.close();
    return;
}