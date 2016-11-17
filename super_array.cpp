//===-----------------------------------------------------------------------===//
//
//  Project 1: Big Integer Arithmetic
//  Authors: Michael Aboff, Mauricio Ferrato, Darsh Patel, Edwin Ortiz,
//           Eric Wright
//
//===----------------------------------------------------------------------===//
//
//  super_array.cpp
//    Defines the SuperArray class.
//
//  Note:
//    The large number stored in the SuperArray is broken up into "chunks"
//    of a size defined in BigInt (BigInt::chunk_size). These strict chunks let
//    the BigInt class better manage the base of each element in the array.
//
//    The chunks are stored in a backwards format where what some users may
//    find counter-intuitive. This is done to make comparisons and arithmetic
//    between BigInts a little easier to write and conceptualize.
//
//    Example of "backwards chunk" format:
//      SuperArray(123456789, 4) => [6789, 2345, 1]
//
//===----------------------------------------------------------------------===//

#include <iostream>
#include "super_array.h"
#include "big_int.h"
#include <stdlib.h>
using namespace std;

// Allocates a larger space for the SuperArray and transfers the old data to it.
//
// Note:
//   This function should only be used when necessary as it doubles the amount of
//   allocated space every time it is called.
void SuperArray::Resize(){
    int orig = allocated_size;
    if (allocated_size == 0){
        allocated_size = 1;
    } else {
        allocated_size *= 2;
    }
    unsigned int* temp_array = (unsigned int *) malloc(sizeof(unsigned int) * allocated_size);
    for(int i = 0; i < real_size; i++){
        temp_array[i] = my_data[i];
    }
    cout << "Memory freed from resize" << endl;
    for (int i = 0; i < orig; i++){
        cout << static_cast<void*>(&my_data[i]) << endl;
    }
    free(my_data);
    my_data = temp_array;
    return;
}

// Constructor function when no parameters are passed.
//
// Note:
//   Enough space for one unsigned int is created by default.
SuperArray::SuperArray(){ // intialize with a value of 0 and one int allocated
    my_data = (unsigned int*) malloc(sizeof(unsigned int));
    allocated_size = 1;
    real_size = 0;

    cout << "SuperArray with no arguments created" << endl;
    cout << static_cast<void*>(&my_data[0]) << endl;
}

// Constructor function when a string and chunk size is passed.
//
// Parameters:
//   string input - input must be a string of integers. The string will be
//                   converted to integers as it is converted into a SuperArray.
//   int size_per_chunk - How many digits are in each "chunk".
//
// Note:
//   If input contains non-integer characters, unpredictable behavior may occur.
//   Because of this, make sure that it is not passed a negative symbol.
SuperArray::SuperArray(string input, int size_per_chunk){

    real_size = input.length() / size_per_chunk; // how much memory we are going to use
    if(input.length() % size_per_chunk > 0){
        real_size++; // allocate an extra piece of memory if needed
    }

    allocated_size = real_size; // allocate only as much size as will be used
    my_data = (unsigned int*) malloc(sizeof(unsigned int) * allocated_size); // allocate

    int strSize = input.size(); // how many digits are we working with
    int counter = 0; // how we will loop through allocated memory

    while (true) {
        if (strSize <= 0) break; // stop when we're out of characters

        int length = 0; // how many digits are we currently using, will be between 0 and 9
        int num = 0; // the integer we're finding from the string
        int prefix = 1; // this is the base, like 10^0, 10^1, 10^2 et cetera
        for (int i = (strSize - 1); i >= 0 && i >= strSize - size_per_chunk; --i) { // grab 9 characters, starting from the back
            num += (input[i] - '0') * prefix; // convert the char to an int, and move over by a power of 10
            prefix *= 10; // increase the power of 10
            ++length; // how much to take off of size each time, 0 to 9
        }

        my_data[counter] = num; // set spot in memory to num
        counter++; // move over a spot in memory
        strSize -= length; // remove length of num from overall size
    }

    for (int i = 0; i < allocated_size; i++){
        cout << static_cast<void*>(&my_data[i]) << endl;
    }

}

//Constructor that takes in another superArray and makes a copy of it with the same allocated space and values
SuperArray:: SuperArray(const SuperArray& super_array){
    free(my_data);
    my_data = (unsigned int *) malloc(sizeof(unsigned int) * super_array.real_size);
    allocated_size = super_array.real_size;
    real_size = 0;
    for (int i = 0; i < super_array.real_size; i++){
        Push(super_array.my_data[i]);
    }
}

// Constructor function when an int is passed. This function makes an empty SuperArray
// with a defined amount of allocated space. This is most often used when we want to insert
// chunks in a non-left-to-right order.
//
// Parameters:
//   unsigned int space_needed - How many chunks to allocate to the SuperArray.
SuperArray::SuperArray(unsigned int space_needed){
    my_data = (unsigned int*) malloc(sizeof(unsigned int) * space_needed);
    allocated_size = space_needed;
    real_size = 0;
}

// Deconstructor function automatically called when the SuperArray instance is deleted.
SuperArray::~SuperArray(){
    /*
    if (my_data)
    {
    	free(my_data); // Freeing memory
    	my_data = NULL;
    }
    */
}

// Append an element to SuperArray.
//
// Parameters:
//  unsigned int input - integer to add to the array.
//
// Note:
//   This function does not enforce chunk sizes. The caller is expected to do this.
void SuperArray::Push(unsigned int input){
    if(real_size == allocated_size){
        // We are out of space, double the allocated space.
        this->Resize();
    }

    my_data[real_size] = input;
    real_size++;
    return;
}

// "Getter" function to return a specific element.
//
// Parameters:
//   int spot - The index to grab from.
//
// Returns:
//   unsigned int - The chunk at the provided index.
//
// Note:
//   There is no error handling. Be careful to only pass a value within the size
//   of the SuperArray.
unsigned int SuperArray::Get(int spot){
    return my_data[spot]; // grab an element at index spot
}

// Deleter function to free the data associated with this SuperArray.
void SuperArray::Release(){
    for (int i = 0; i < allocated_size; i++){
        cout << static_cast<void*>(&my_data[i]) << endl;
    }
    free(my_data);
    allocated_size = 0;
    real_size = 0;
    return;
}

// Returns how many chunks are in the SuperArray.
//
// Returns:
//   unsigned int - How many elements are being used.
//
// Note:
//   This function only returns how many chunks are being used, not just allocated.
unsigned int SuperArray::Length(){
    return real_size;
}


// A helper function made to carry 1 from a larger "chunk" in the BigInt to assist
// with subtraction to prevent individual chunk subtraction from resulting in
// negative numbers. Removes one from the next chunk and adds it multiplied by
// the base to the current chunk.
//
// Parameters:
//   SuperArray &s_array - The SuperArray we are working with.
//   int index - The index of the chunk that needs to bring 1 down from its superior.
void SuperArray::Borrow(int index){
    if (my_data[index + 1] > 0){
        my_data[index] += BigInt::GetBase();
        my_data[index + 1] -= 1;
    } else { // if the next memory spot is 0, have to borrow again
        Borrow(index + 1);
        my_data[index] += BigInt::GetBase();
        my_data[index + 1] -= 1;
    }
}

// Inserts an integer at a given location.
//
// Parameters:
//   int spot - The index to replace.
//   int input - The integer to replace the data with.
//
// Note:
//   This function does not enforce chunk sizes. The caller is expected to do this.
void SuperArray::Set(int spot, int input){
    this->my_data[spot] = input;
}

// Loops through all of the allocated memory, and determine how much of it is actually being used.
void SuperArray::UpdateSize(){
    int actual = 0; // this number will be updated everytime we move to another memory spot
    int withoutZero = 0; // this number will be set to actual only when a non-zero is encountered
    // just because the later memory slots have a value of zero doesn't mean they're being used

    for (int i = 0; i < allocated_size; i++){ // loop through all of the allocated memory
        if (Get(i) != 0){
            actual++;
            withoutZero = actual;
        } else {
            actual++;
        }
    }

    real_size = withoutZero;
}

// increase real_size by one
void SuperArray::IncreaseReal(){
    real_size++;
    return;
}

// Getter function to provide data to other classes.
//
// Returns:
//   unsigned int* - Pointer to the SuperArray's array.
unsigned int* SuperArray::GetMy_Data(){
    return my_data;
}

// Getter function reporting how much space was allocated.
//
// Returns:
//   unsigned int - How much space is allocated to the instance of SuperArray.
unsigned int SuperArray::GetAllocated_Size(){
    return allocated_size;
}

// Remove the last element of a super array by setting it to zero and decreasing real size
// That spot in memory will still be allocated
void SuperArray::Pop(){
    my_data[Length() - 1] = 0;
    real_size--;
}


// Reverse the order of a super array, real size and allocated size stays the same
void SuperArray::Reverse(){
    int i = 0;
    int j = this->Length() - 1;

    int temp;

    for (; i < (this->Length() / 2); i++){
        temp = Get(j);
        Set(j, Get(i));
        Set(i, temp);
        j--;
    }
    return;
}