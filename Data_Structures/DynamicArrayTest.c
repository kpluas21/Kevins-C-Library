#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include"DynamicArray.h"

int main(int argc, char const *argv[]) {
    int intArray[] = {1, 2, 3, 4, 5};
    char chars[] = {'a', 'b', 'c', 'd', 'e'};

    DynamicArray *vector = DynamicArray_init(INT, intArray, 5);
    assert(vector != NULL);
    assert(vector->size == 5 && vector->capacity == 10);

    DynamicArray *chVector = DynamicArray_init(CHAR, chars, 5);
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
