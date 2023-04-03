/**
 * @file DynamicArrayTest.c
 * @author Kevin Pluas (kpluas21@gmail.com)
 * @brief Program used to test the functions of DynamicArray.h
 * @version 0.1
 * @date 2023-04-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include"DynamicArray.h"
/**
 * @brief Our main test function.
 * I'll try to split testing into several parts. Each part will involve the four different data types : int, char, double & float.
 * 1)Initialization
 * 2)Appending
 * 3)Printing
 * 4)Finding
 * 5)Getting
 * 6)Removing
 * 7)Resizing
 * 
 */
int main(void) {
    int intArray[] = {1, 2, 3, 4, 5};
    char charArray[] = {'a', 'b', 'c', 'd', 'e'};

    DynamicArray *vector = DynamicArray_init(INT, intArray, 5);
    assert(vector != NULL);
    assert(vector->size == 5 && vector->capacity == 10);

    DynamicArray *chVector = DynamicArray_init(CHAR, charArray, 5);
    assert(chVector != NULL);
    assert(chVector->size == 5 && chVector->capacity == 10);


    //TEST
    //Appending numbers until 1000.
    int p, *intPtr = &p;
    for (int i = 6; i < 100000001; i++) {
        p = i;
        DynamicArray_append(vector, intPtr);
    }    
    DynamicArray_debug_info(vector);


    DynamicArray_delete(vector);
    DynamicArray_delete(chVector);
    return 0;
}
