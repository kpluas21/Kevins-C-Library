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
#include<time.h>
#include<stdlib.h>
#include"DynamicArray.h"

double rand_from(double min, double max);

void DynamicArrayTest_print_all_debug(DynamicArray **arrayOfVectors);

void DynamicArrayTest_empty_all(DynamicArray **arrayOfVectors);

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
    float fltArray[5];
    double dbArray[5];

    DynamicArray *vector = DynamicArray_init(INT, intArray, 5);
    assert(vector != NULL);
    assert(vector->size == 5 && vector->capacity == 10);

    DynamicArray *chVector = DynamicArray_init(CHAR, charArray, 5);
    assert(chVector != NULL);
    assert(chVector->size == 5 && chVector->capacity == 10);


    for(int i = 0; i < 5; i++) {
        dbArray[i] = rand_from(-1.0, 1.0);
    }
    DynamicArray *dbVector = DynamicArray_init(DOUBLE, dbArray, 5);
    assert(dbVector != NULL);
    assert(dbVector->size == 5 && dbVector->capacity == 10);

    for(int i = 0; i < 5; i++) {
        fltArray[i] = (float)rand()/(float)(RAND_MAX/10.0);
    }
    DynamicArray *fltVector = DynamicArray_init(FLOAT, fltArray, 5);
    assert(fltVector != NULL);
    assert(fltVector->size == 5 && fltVector->capacity == 10);


    //You COULD call print debug on each vector OR just make a pointer to pointers :)
    DynamicArray **arrayOfVectors = malloc(4 * sizeof(DynamicArray*));
    arrayOfVectors[0] = vector;
    arrayOfVectors[1] = chVector;
    arrayOfVectors[2] = fltVector;
    arrayOfVectors[3] = dbVector;

    DynamicArrayTest_print_all_debug(arrayOfVectors);

    DynamicArrayTest_empty_all(arrayOfVectors);
    
    DynamicArrayTest_print_all_debug(arrayOfVectors);


    //INITIAL STATS


    // //APPENDING TEST
    // //Pointers to hold our values
    // int p, *intPtr = &p;
    // char ch, *chPtr = &ch;
    // float flt, *fltPtr = &flt;
    // double db, *dbPtr = &db;

    // for (int i = 0; i < 101; i++)
    // {
    //     p = i;
    //     if(i < 256) {
    //         ch = i;
    //     }
    //     db = rand_from(-1.0, 1.0);
    //     flt = (float)rand()/(float)(RAND_MAX/10.0);

    //     DynamicArray_append(vector, intPtr);
    //     DynamicArray_append(chVector, chPtr);
    //     DynamicArray_append(dbVector, dbPtr);
    //     DynamicArray_append(fltVector, fltPtr);
    // }

    // //STATS AFTER APPENDS

    
    // p = 0;
    // ch = 'Q';
    // printf("The number 0 was found at index %d in vector.\n", DynamicArray_find(vector, intPtr));
    // printf("The letter q was found at index %d in chVector.\n", DynamicArray_find(chVector, chPtr));
    
    // /*TODO: Unit testing for floating point values in _find
    // *
    // *


    // //Testing the _get functions
    // DynamicArray_get(vector, 15, intPtr);
    // DynamicArray_get(chVector, 15, chPtr);
    // DynamicArray_get(fltVector, 15, fltPtr);
    // DynamicArray_get(dbVector, 15, dbPtr);

    // printf("The element at index 15 of vector is %d.\n", *intPtr);
    // printf("The element at index 15 of chVector is %c.\n", *chPtr);
    // printf("The element at index 15 of fltVector is %.6f.\n", *fltPtr);
    // printf("The element at index 15 of dbVector is %2.6f.\n", *dbPtr);

    // DynamicArray_get(vector, 32, intPtr);

    // //Testing the _remove function
    // DynamicArray_remove(vector, 5);
    // DynamicArray_debug_info(vector);
    // printf("%d\n", *intPtr);

    // for (size_t i = 0; i < vector->size; i++)
    // {
    //     DynamicArray_get(vector, i, intPtr);
    //     DynamicArray_remove(vector, i);
    // }
    
    // flt = 3.363;
    // printf("The float 3.363 was found in index %d of fltVector.\n"
    // , DynamicArray_find(fltVector, fltPtr));

    // db = 0.315226;
    // printf("The double %.6f was found in index %d of dbVector.\n"
    // , db, DynamicArray_find(dbVector, dbPtr));

    printf("All vectors of all types successfully initialized and all tests passed!\n");
    DynamicArray_delete(vector);
    DynamicArray_delete(chVector);
    DynamicArray_delete(dbVector);
    DynamicArray_delete(fltVector);
    free(arrayOfVectors);
    return 0;
}

double rand_from(double min, double max) {
    double range = max - min;
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

void DynamicArrayTest_print_all_debug(DynamicArray **arrayOfVectors) {
    for (size_t i = 0; i < 4; i++) {
        DynamicArray_debug_info(arrayOfVectors[i]);
    }
    
}

void DynamicArrayTest_empty_all(DynamicArray **arrayOfVectors) {
    for (size_t i = 0; i < 4; i++) {
        DynamicArray_empty(arrayOfVectors[i]);
    }
    
}
