#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H
/**
 * @file DynamicArray.h
 * @author Kevin Pluas (kpluas21@gmail.com)
 * @brief Implementation of variable length arrays in C capable of storing 1 of 4 different data types.
 * @version 0.1
 * @date 2023-04-02
 * 
 * @copyright Copyright (c) 2023
 * 
 *
 * This structure uses mostly void pointers and regular arrays. It handles ints, chars, doubles and floats. Strings are to be implemented soonish...
 * Everything you need should be in this one header file. Simply include it and call the _init function. Make sure to include what type you are gonna use the array for.
 * This was not tested for every outcome, for instance, if one should init an array of chars while labeling it as a float. Its up to YOU to know what you're doing. 
 * 
 * Because this was created using LOTS of void pointers, expect to see and use a lot of casting, again, it should work if you're casting appropriately. 
 * 
 * DynamicArrays are zero-based and are designed with fast insertion in mind. Appending should occur in constant time unless capacity was reached in which case it will 
 * automatically resize and attempt to append the element again.
 * IMPLEMENTED FUNCTIONS
 * _init
 * _append
 * _print
 * _debug_info
 * _delete
 * _resize
 * _find (Needs some work but its kinda functional?)
 * _get
 * 
 * 
 */
//TODO: FUNCTIONS TO BE ADDED
/**
 * 
 * 2) find : Attempts to find the given input, outputting the index if found, -1 otherwise
 * 4) remove : Removes an element from the array , everything will have to be stitched together
 * 5) empty : Removes all elements from the array, reducing the size to 0. MAY NOT change the capacity.
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/**
 * BEGIN TYPEDEF DECLARATIONS 
 * 
 * 
 */

/**
 * @enum DataType
 * @brief Constants used to label the data type of the elements in our dynamic array
 */
typedef enum DataType {
    INT,
    CHAR,
    DOUBLE,
    FLOAT,
    STRING,

}DataType;

/**
 * @struct DynamicArray
 * @brief Our main struct that contains all the data and metainfo about our dynamic array
 * @var DynamicArray::type
 */
typedef struct DynamicArray {
    DataType type;
    size_t size;
    size_t capacity;
    void *data;  
}DynamicArray;
/**
 * END TYPEDEF DECLARATIONS
 */


/**
 * BEGIN FUNCTION DECLARATIONS
 * 
 * 
 */

void DynamicArray_append(DynamicArray *array, void *elem);
void DynamicArray_print(DynamicArray *array);
void DynamicArray_debug_info(DynamicArray *array);
void DynamicArray_delete(DynamicArray *array);
void DynamicArray_remove(DynamicArray *array);

int DynamicArray_find(DynamicArray *array, void *elem);

void DynamicArray_get(DynamicArray *array, size_t index, void *result);

DynamicArray *DynamicArray_init(DataType type, void *data, size_t size);
DynamicArray *DynamicArray_resize(DynamicArray *array);
/**
 * END FUNCTION DECLARATIONS
 */


/**
 * BEGIN FUNCTION DEFINITIONS
 * 
 * 
 */

/**
 * @brief Initializes our dynamic array. This is done by malloc first acquiring the capacity which 
 *        is the initial size of the data multiplied by 2 to give it enough space for expansion.
 * 
 * @param type The data type for our elements
 * @param data The initial data to be store in the array
 * @param size The number of initial elements 
 * @return struct DynamicArray* : A pointer to our DynamicArray struct containing everything we need
 */
DynamicArray* DynamicArray_init(DataType type, void *data, size_t size) {
    struct DynamicArray* da = malloc(sizeof(DynamicArray));

    if(da == NULL) {
        printf("Error: Unable to allocate memory for DynamicArray struct\n");
        return NULL;
    }

    da->size = size;
    da->type = type;
    da->capacity = size * 2;

    switch (type) {
    case INT:
        da->data = malloc(da->capacity * sizeof(int));
        memcpy(da->data, data, size * sizeof(int));
        break;
    case CHAR:
        da->data = malloc(da->capacity * sizeof(char));
        memcpy(da->data, data, size * sizeof(char));
        break;
    case DOUBLE:
        da->data = malloc(da->capacity * sizeof(double));
        memcpy(da->data, data, size * sizeof(double));
        break;
    case FLOAT:
        da->data = malloc(da->capacity * sizeof(float));
        memcpy(da->data, data, size * sizeof(float));
        break;
    default:
        printf("Error: Invalid DataType\n");
        return NULL;
    }
    
    if(da->data == NULL) {
        printf("Error: Unable to allocate memory for DynamicArray:data\n");
        return NULL;
    }

    return da;
}

/**
 * @brief Displays the meta info about our dynamic array such as size, capacity, type, and contents so long as the size does
 * not exceed 1000.
 * 
 * @param array The DynamicArray pointer
 */
void DynamicArray_debug_info(DynamicArray *array) {

    printf("Data type of the elements stored (DataType) : %d\n", array->type);

    printf("Number of elements currently in our array (size) : %zu\n", array->size);
    printf("Max number of elements that can be currently stored (capacity) : %zu\n", array->capacity);
    if(array->size >= 1000) {
        return;
    }
    printf("Elements currently stored (data) : \n");
    DynamicArray_print(array);
}

/// @brief Pretty prints the contents of our array
/// @param array Our dynamic array ptr
void DynamicArray_print(DynamicArray *array) {
    switch (array->type) {
    case INT: {
        int *dest = (int*) array->data;
        printf("[");
        for(size_t i = 0; i < array->size - 1; i++) {
            printf("%d, ", dest[i]);
            
        }
        printf("%d]\n", dest[array->size - 1]);
        return;
    }
    case CHAR: {
        char *dest = (char*) array->data;
        printf("[");
        for (size_t i = 0; i < array->size - 1; i++) {
            printf("%c, ", dest[i]);
        }
        printf("%c]\n", dest[array->size - 1]);
        return;
    }
    case FLOAT: {
        float *dest = (float*) array->data;
        printf("[");
        for (size_t i = 0; i < array->size - 1; i++) {
            printf("%2.3f, ", dest[i]);
        }
        printf("%2.3f]\n", dest[array->size - 1]);
        return;
    }
    case DOUBLE: {
        double *dest = (double*) array->data;
        printf("[");
        for (size_t i = 0; i < array->size - 1; i++) {
            printf("%.6f ", dest[i]);
        }
        printf("%.6f]\n", dest[array->size - 1]);
        return;
    }
    default:
        break;
    }
}

//TODO : This takes a single void pointer as input. Are we able to append JUST one or can we append everything in the pointer?
/**
 * @brief Adds the given element to the end of the array, automatically resizing the array if necessary.
 * 
 * @param array The DynamicArray pointer
 * @param elem The element to be added
 */
void DynamicArray_append(DynamicArray *array, void* elem) {
    if(array->size == array->capacity) {
        array = DynamicArray_resize(array);
        if(array == NULL) {
            return;
        }
        
    }
    switch (array->type) {
    case INT: {
        int *intElem = (int*) elem;
        int *dest = array->data;
        dest[array->size] = intElem[0];
        array->size++;
        break;
    }
    case CHAR: {
        char *charElem = (char*) elem;
        char *dest = array->data;
        dest[array->size] = charElem[0];
        array->size++;
        break;
    }
    case DOUBLE: {
        double *dbElem = (double*) elem;
        double *dest = array->data;
        dest[array->size] = dbElem[0];
        array->size++;
        break;
    }
    case FLOAT: {
        float *fltElem = (float*) elem;
        float *dest = array->data;
        dest[array->size] = fltElem[0];
        array->size++;
        break;
    }
    case STRING:
        break;
    }
    return;
}

/**
 * @brief Attempts to resize the array by doubling the current capacity and realloc'ing 
 * the pointer
 * 
 * @param array The DynamicArray pointer
 * @return DynamicArray* A pointer to the struct with the newly realloc'd data pointer. 
 */
DynamicArray* DynamicArray_resize(DynamicArray *array) {
    array->capacity *= 2; //Double the capacity;

    switch (array->type) {
    case INT:
        array->data = realloc(array->data, array->capacity * sizeof(int));
        break;
    case CHAR:
        array->data = realloc(array->data, array->capacity * sizeof(char));
        break;
    case DOUBLE:
        array->data = realloc(array->data, array->capacity * sizeof(double));
        break;
    case FLOAT:
        array->data = realloc(array->data, array->capacity * sizeof(float));
        break;
    case STRING:
        break;
    }

    if(array->data == NULL) {
        printf("Error: Unable to resize DynamicArray.data\n");
        return NULL;
    }

    return array;
}

/**
 * @brief Frees up all memory used by the array including the struct itself. This should be used 
 * instead of simply freeing the struct as the latter will cause memory leaks
 * 
 * @param array The DynamicArray pointer
 */
void DynamicArray_delete(DynamicArray *array) {
    free(array->data);
    free(array);
}

/**
 * @brief Linearly searches through the array to find the given input, returning the index if found, 
 * -1 otherwise
 * 
 * @param array The DynamicArray pointer
 * @param ptr A void pointer pointing to the data needing to be searched for.
 * @return int The index where the element is located at.
 */
int DynamicArray_find(DynamicArray *array, void *elem) {
    switch(array->type) {
    case INT: {
        int *dest = array->data;
        int *elemToFind = (int*) elem;
        for (size_t i = 0; i < array->size; i++) {
            if(dest[i] == *elemToFind) {
                return i;
            }
        }
        break;
        
    }
    case CHAR: {
        char *dest = array->data;
        char *elemToFind = (char*) elem;
        for (size_t i = 0; i < array->size; i++) {
            if(dest[i] == *elemToFind) {
                return i;
            }
        }
        break;
    }
    //TODO: Regular comparisons between floating point values won't work! 
    //I'll need to implement an episilon. 
    case FLOAT: {
        float *dest = array->data;
        float *elemToFind = (float*) elem;
        for (size_t i = 0; i < array->size; i++) {
            if(dest[i] == *elemToFind) {
                return i;
            }
        }
        break;
    }
    case DOUBLE: {
        double *dest = array->data;
        double *elemToFind = (double*) elem;
        for (size_t i = 0; i < array->size; i++) {
            if(dest[i] == *elemToFind) {
                return i;
            }
        }
        break;
    }
    default:
        break;
    }
    return -1;
}

/**
 * @brief Returns the element specified by the provided index. SHOULD run in O(1) time. You must
 * provide a pointer to store the result of get. 
 * 
 * @param array The DynamicArray pointer
 * @param index 
 * @param result A reference pointer to store our result. 
 * @return Nothing. However, result will either contain the element requested or be NULL if 
 * an invalid index was provided.
 */
void DynamicArray_get(DynamicArray *array, size_t index, void *result) {
    if(index >= array->size) {
        printf("Error: Out-of-bounds index provided : %zu\n", index);
        result = NULL;
        return;
    }
    switch (array->type) {
    case INT: {
        int *dest = array->data;
        *(int*)result = dest[index];
        return;
    }
    case CHAR: {
        char *dest = array->data;
        *(char*)result = dest[index];
        return;
    }
    case FLOAT: {
        float *dest = array->data;
        *(float*)result = dest[index];
        return;
    }
    case DOUBLE: {
        double *dest = array->data;
        *(double*)result = dest[index];
        return;
    }
    default:
        return;
    }
}
/**
 * END FUNCTION DEFINITIONS
 * 
 * 
 */

#endif //DYNAMIC_ARRAY_H