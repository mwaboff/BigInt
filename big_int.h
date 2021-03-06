//===-----------------------------------------------------------------------===//
//
//  Project 1: Big Integer Arithmetic
//  Authors: Michael Aboff, Mauricio Ferrato, Darsh Patel, Edwin Ortiz,
//           Eric Wright
//
//===----------------------------------------------------------------------===//
//
//  big_int.h
//    Header file for big_int.cpp
//
//===----------------------------------------------------------------------===//

#ifndef BIG_INT_H
#define BIG_INT_H

#include <string>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class BigInt {
private:
    bool positive;
    static int base;
    vector<int> value;

    //Helper functions


public:
    static int chunk_size;
    //Constructors
    bool IsPositive();

    //Makes default BigInt (zero)
    BigInt();
    //Makes BigInt from a string
    BigInt(string numStr);
    // Make BigInt from how much memory you want to allocate
    BigInt(unsigned int);
    BigInt(vector<int>);

    // Deconstructor
    void MakeEmpty();
    ~BigInt();

    //Helper functions
    void Print();
    static int GetBase() { return base; }
    static int GetChunkSize() { return chunk_size; }
    void SetSign(bool positivity); // change positive
    void FlipSign(); // if positive, become negative and vise versa
    void DebugPrint(); // Prints all out relavant info of a BigInt for debugging purposes
    void SetValue(vector<int> new_value);

    vector<int> GetValue(); // returns value

    // Addition
    friend BigInt operator+(const BigInt &bigInt1, const BigInt &bigInt2);
    //BigInt Add(BigInt input2);
    BigInt addChunks(vector<int> larger, vector<int> smaller, bool same_size);

    // Subtraction
    friend BigInt operator-(const BigInt &bigInt1, const BigInt &bigInt2);
    vector<int> SubtractSmallerFromLarger(BigInt);
    //BigInt Subtract(BigInt); // both bigints must be positive

    // Multiplication
    friend BigInt operator*(const BigInt &bigInt1, const BigInt &bigInt2);
    BigInt Shifter(unsigned int);
    //BigInt Multiply(int, int shift_amount);
    // BigInt Product(BigInt input2);

    // Division
    BigInt DivideByTwo();
    unsigned int FactorDifference(BigInt);
    BigInt LargestMultipleUnderOther(BigInt);
    BigInt NextBinaryFinder(BigInt);


    // For testing
    bool Equals(string numStr, bool sign);

    const string ToString();

    friend ostream& operator<<(ostream& os, const BigInt &andy);
    friend istream& operator>>(istream& is,  BigInt &andy);

    BigInt lshift(unsigned int);

    void Push(int val);

    void Set(int index, int val);

    void Reverse();

    void WriteToFile(string filename);
};

// File Reader
BigInt ReadFromFile(std::string fileName);


bool GreaterOrEqual(BigInt, BigInt);
int BigIntCompare(BigInt, BigInt);

void DivideRemainder(BigInt&, BigInt, string&);

double Divide(BigInt, BigInt);

double BigInt_to_Double(BigInt, string);


#endif