/**
 * @file DynamicArray.c
 * @author your name (you@domain.com)
 * @brief Implementation of DynamicArray
 * @version 0.1
 * @date 2023-04-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include"DynamicArray.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

/**
 * @brief Initializes our dynamic array. This is done by malloc first acquiring the capacity which 
 *        is the initial size of the data multiplied by 2 to give it enough space for expansion.
 * 
 * @param type The data type for our elements
 * @param data The initial data to be stored in the array
 * @param size The number of initial elements 
 * @return DynamicArray* : A pointer to our DynamicArray struct containing everything we need
 */
int DynamicArray_init(DynamicArray *array, DataType type, void *data, size_t size) {
    array = malloc(sizeof(DynamicArray));

    if(array == NULL) {
        printf("Error: Unable to allocate memory for DynamicArray struct\n");
        return -1;
    }

    array->size = size;
    array->type = type;
    array->capacity = size * 2;

    switch (type) {
    case INT:
        array->data = malloc(array->capacity * sizeof(int));
        memcpy(array->data, data, size * sizeof(int));
        break;
    case CHAR:
        array->data = malloc(array->capacity * sizeof(char));
        memcpy(array->data, data, size * sizeof(char));
        break;
    case DOUBLE:
        array->data = malloc(array->capacity * sizeof(double));
        memcpy(array->data, data, size * sizeof(double));
        break;
    case FLOAT:
        array->data = malloc(array->capacity * sizeof(float));
        memcpy(array->data, data, size * sizeof(float));
        break;
    default:
        printf("Error: Invalid DataType\n");
        return -1;
    }
    
    if(array->data == NULL) {
        printf("Error: Unable to allocate memory for DynamicArray:data\n");
        return -1;
    }

    return 0;
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
    //Empty array
    if(array->size == 0) {
        puts("[ ]\n");
        return;
    }
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
        dest[array->size] = *intElem;
        array->size++;
        break;
    }
    case CHAR: {
        char *charElem = (char*) elem;
        char *dest = array->data;
        dest[array->size] = *charElem;
        array->size++;
        break;
    }
    case DOUBLE: {
        double *dbElem = (double*) elem;
        double *dest = array->data;
        dest[array->size] = *dbElem;
        array->size++;
        break;
    }
    case FLOAT: {
        float *fltElem = (float*) elem;
        float *dest = array->data;
        dest[array->size] = *fltElem;
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
 * Caution must be used when comparing floating-point values because of general imprecision. Use 
 * an episilon for some "good enough" results. You may need to change the epsilon to suit your needs.
 * @note Epsilon Values :
 * Float : 0.001
 * Double: 0.000001
 * 
 * @param array The DynamicArray pointer
 * @param ptr A void pointer pointing to the data needing to be searched for.
 * @return int The index where the element is located at.
 */
size_t DynamicArray_find(DynamicArray *array, void *elem) {
    float fltEpsilon = 0.001;
    double dbEpsilon = 0.000001;

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
    case FLOAT: {
        float *dest = array->data;
        float *elemToFind = (float*) elem;
        for (size_t i = 0; i < array->size; i++) {
            //DEBUG: Print the elements of the comparison
            // printf("%.6f =? %.6f\n", dest[i], *elemToFind);
            if(fabs(dest[i] - *elemToFind) < fltEpsilon) {
                return i;
            }
        }
        break;
    }
    case DOUBLE: {
        double *dest = array->data;
        double *elemToFind = (double*) elem;
        for (size_t i = 0; i < array->size; i++) {
            if(fabs(dest[i] - *elemToFind) < dbEpsilon) {
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
 * @brief Attempts to sort the contents of the array in either ascending or descending order depending on
 * the mode provided.
 * 
 * @param array The DynamicArray pointer
 * @param mode 1 : Descending, anything else if ascending.
 */
// inline void DynamicArray_sort(DynamicArray *array, int mode) {
//     //TODO: Implement merge sort here somehow...
// }

/**
 * @brief Returns 0 if the array is empty. 1 otherwise.
 * 
 * @param array The DynamicArray pointer
 * @return int 0 if empty, 1 otherwise.
 */
inline int DynamicArray_isEmpty(DynamicArray *array) {
    if(array->size == 0) {
        return 0;
    }
    return 1;
}

/**
 * @brief Removes from the array a single element. Reduces the size of the array by 1 and 
 * closes the gap by shifting every element over by 1. The capacity remains unchanged after
 * this operation.
 * 
 * @param array The DynamicArray pointer
 * @param index The index of the element
 */
void DynamicArray_remove(DynamicArray *array, size_t index) {
    //TODO: I don't think this is working as intended? If you iterate through
    //the entire array, calling this function on each elem, you'll effectively cut it 
    //in half. It takes away every other elem. 
    if(index >= array->size) {
        printf("Error: Invalid index provided : %zu\n", index);
        return;
    }
    switch (array->type) {
    case INT: {
        int *dest = array->data;
        for (size_t i = index; i < array->size - 1; i++) {
            dest[i] = dest[i + 1];
        }
        array->size--;
        return;
    }
    case CHAR: {
        char *dest = array->data;
        for (size_t i = index; i < array->size - 1; i++) {
            dest[i] = dest[i + 1];
        }
        array->size--;
        return;
    }
    case FLOAT: {
        float *dest = array->data;
        for (size_t i = index; i < array->size - 1; i++) {
            dest[i] = dest[i + 1];
        }
        array->size--;
        return;
    }
    case DOUBLE: {
        double *dest = array->data;
        for (size_t i = index; i < array->size - 1; i++) {
            dest[i] = dest[i + 1];
        }
        array->size--;
        return;
    }
    default:
        return;
    }
}

/**
 * @brief Clears out the entire array, reducing the size to 0. Does not change the 
 * capacity in any way.
 * 
 * @param array The DynamicArray pointer
 */
void DynamicArray_empty(DynamicArray *array) {
    free(array->data);

    switch (array->type) {
    case INT: { 
        array->data = calloc(array->capacity, sizeof(int));
        break;
    }
    case CHAR: {
        array->data = calloc(array->capacity, sizeof(char));
        break;
    }
    case FLOAT: {
        array->data = calloc(array->capacity, sizeof(float)); 
        break;
    }
    case DOUBLE: {
        array->data = calloc(array->capacity, sizeof(double));
        break;
    }
    
    default:
        break;
    }
    array->size = 0;
    return;

}
/**
 * END FUNCTION DEFINITIONS
 * 
 * 
 */