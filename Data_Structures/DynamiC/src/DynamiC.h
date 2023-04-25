#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H
/**
 * @file DynamiC.h
 * @author Kevin Pluas (kpluas21@gmail.com)
 * @brief Specification of DynamiC
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
 * DynamiCs are zero-based and are designed with fast insertion in mind. Appending should occur in constant time unless capacity was reached in which case it will 
 * automatically resize and attempt to append the element again.
 * 
 */
//TODO: FUNCTIONS TO BE ADDED
/** * 
 * 1) remove : Removes an element from the array , everything will have to be stitched together
 */

#include<stddef.h>
/**
 * @brief Global epsilons to be used when comparing floating-point values. If you need to change
 * how precise the comparisons should be, change it here.
 * Used in the following functions
 * _find()
 * _cmp()
 * 
 */
#define FLTEPSILON 0.001
#define DBEPSILON 0.000001

#define min(a, b) \
    ({ __typeof__ (a) _a = (a); \
        __typeof__ (b) _b = (b); \
        _a < _b ? _a : _b; })

typedef enum ErrorCode {
    SUCCESS = 0, 
    OUT_OF_MEMORY,
    INVALID_ARGUMENT, 
    INVALID_DATATYPE,
    OUT_OF_BOUNDS_INDEX,
    UNKNOWN_ERROR,

}ErrorCode;

/**
 * @struct DynamiC
 * @brief Our main struct that contains all the data and metainfo about our dynamic array
 * @param data_size How large, in bytes, each element is
 * @param capacity Current max size of the array
 * @param alloc_data Amount of data currently allocated with actual data, in bytes
 * @param data The void pointer to our actual data
 */
typedef struct DynamiC {
    size_t   data_size;
    size_t   capacity;
    size_t   alloc_data;
    void    *data;
}DynamiC;

/**
 * @brief Initializes our dynamic array
 * 
 * @param data The void pointer to our initial data.
 * @param data_size The size, in bytes, each element is.
 * @param num_elems The number of elements in our initial array/pointer
 * @return DynamiC* A pointer to your newly created dynamic array. 
 */
DynamiC *DynamiC_init(void *data, size_t data_size, size_t num_elems);

/**
 * @brief Returns the number of elements currently in the array.
 * 
 * @param array Our DynamiC pointer
 * @return size_t The number of elements
 */
size_t DynamiC_size(DynamiC *array);

/**
 * @brief Appends the given element to the end of the array, 
 * automatically resizing the array if necessary.
 * 
 * @param array The DynamiC pointer
 * @param elem The element to be added
 */
void DynamiC_append(DynamiC *array, void *elem);

// /**
//  * @brief Displays the meta info about our dynamic array such as size, capacity, type, and contents so long as the size does
//  * not exceed 1000.
//  * 
//  * @param array The DynamiC pointer
//  */
// void DynamiC_debug_info(DynamiC *array);

/**
 * @brief Frees up all memory used by the array including the struct itself.
 * Pass a reference to the DynamiC pointer, that way everything will be 
 * NULL'd safely.
 * @param array A pointer to a DynamiC pointer
 */
void DynamiC_delete(DynamiC **array);

/**
 * @brief Removes from the array a single element. Reduces the size of the array by 1 and 
 * closes the gap by shifting every element over by 1. The capacity remains unchanged after
 * this operation.
 * 
 * @param array The DynamiC pointer
 * @param index The index of the element
 */
void DynamiC_remove(DynamiC *array, size_t index);
/**
 * @brief Clears out the entire array, reducing the size to 0. Does not change the 
 * capacity in any way.
 * 
 * @param array The DynamiC pointer
 */
void DynamiC_empty(DynamiC *array);

// /**
//  * @brief Compares two elements in the array.
//  * 
//  * @param elem1 The first element
//  * @param elem2 The second element
//  * @return int 0 if elements are equal, <0 if x is less than y, 
//  *         >0 if x is greater than y;
//  */
// int DynamiC_cmp(void *elem1, void *elem2);

// /**
//  * @brief Swaps the contents of two elements.
//  * 
//  * @param type The data type of the elements
//  * @param elem1 The first element
//  * @param elem2 The second element
//  */
// void DynamiC_swap(DataType type, void *elem1, void *elem2);

/**
 * @brief Retrieves the element at the specified index.
 * 
 * @param array The DynamiC pointer
 * @param index Index of the element
 * @return void* A void pointer that points to the result of this function call.
 */
void *DynamiC_get(DynamiC *array, size_t index);

// /**
//  * @brief Attempts to sort the contents of the array in either ascending or descending order depending on
//  * the mode provided. Uses selection sort.
//  * 
//  * @param array The DynamiC pointer
//  * @param mode 1 : Descending, anything else if ascending.
//  */
// void DynamiC_sort(DynamiC *array);

// /**
//  * @brief Returns 0 if the array is empty. Otherwise, returns a nonzero value.
//  * 
//  * @param array The DynamiC pointer
//  * @return int 0 if empty, otherwise the size of the array.
//  */
// int DynamiC_isEmpty(DynamiC *array);

/**
 * @brief Inserts an element at the chosen index. This effectively shifts all 
 * existing elements over. Automatically reallocates memory if needed.
 * If index equals size, it will basically act as _append() would. 
 * 
 * @param array The DynamiC pointer
 * @param elem The element to be inserted
 * @param index The location where the element is to be inserted
 * @return int Returns 0 if successful, <0 if error encountered.
 */
int DynamiC_insert(DynamiC *array, void *elem, size_t index);



/**
 * @brief Attempts to linearly search through the array for the given data. Because of 
 * the generic nature of the array, a comparator function must be provided for this 
 * function to work with any data types. 
 * 
 * @param array The DynamiC pointer
 * @param data The data to search for 
 * @param DynamiC_cmp A pointer to a comparator function
 * @return size_t The index where the data is located.
 */
size_t DynamiC_find(DynamiC *array, void *data, 
                    int (*DynamiC_cmp) (const void *elem1, const void *elem2));

/**
 * @brief Attempts to resize the array by doubling the current capacity and realloc'ing 
 * the pointer
 * 
 * @param array The DynamiC pointer
 * @return DynamiC* A pointer to the struct with the newly realloc'd data pointer. 
 */
void DynamiC_resize(DynamiC *array);


// /**
//  * @brief Outputs error messages
//  * 
//  * @param error The ErrorCode int
//  * @return const char* A string detailing the error and where it occured
//  */
// const char* DynamiC_error(ErrorCode error, const char* function);


#endif //DYNAMIC_ARRAY_H