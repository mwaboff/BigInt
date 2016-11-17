//===-----------------------------------------------------------------------===//
//
//  Project 1: Big Integer Arithmetic
//  Authors: Michael Aboff, Mauricio Ferrato, Darsh Patel, Edwin Ortiz,
//           Eric Wright
//
//===----------------------------------------------------------------------===//
//
//  super_array.h
//    Header file for super_array.cpp
//
//===----------------------------------------------------------------------===//

#ifndef SUPER_ARRAY_H
#define SUPER_ARRAY_H

#include <iostream>
#include <stdlib.h>
using namespace std;

class SuperArray {
private:
    // Pointer to allocated memory
    unsigned int* my_data;
    // How much memory is allocated
    int allocated_size;
    // How much memory is in use
    int real_size;


public:
    //Constructors
    // One allocated memory spot, none used
    SuperArray();
    // Allocates memory based on size of input and size of each chunk
    // Allocated memory is equivalent to memory in use
    SuperArray(string input, int size_per_chunk);
    // Allocates however much space you need, but doesn't use any of it
    SuperArray(unsigned int);
    // copy a super array
    SuperArray(const SuperArray&);

    // Deconstructor
    ~SuperArray();

        // Double the size of allocated memory, move all elements to new memory spots
    void Resize();

    // free up the memory
    void Release();

    // append an element to end of memory
    void Push(unsigned int input);

    // get element at index spot
    unsigned int Get(int spot);

    // set element at index spot
    void Set(int spot, int input);

    void SetValue(SuperArray s);

    // How much memory is being used
    unsigned int Length();

    // subtraction helper
    void Borrow(int index);

    // look through a SuperArray and determine how much memory it is actually using
    void UpdateSize();

    void Print();

    void IncreaseReal();

    unsigned int* GetMy_Data();

    unsigned int GetAllocated_Size();

    void Pop();

    void Reverse();


};

#endif  // SUPER_ARRAY_H