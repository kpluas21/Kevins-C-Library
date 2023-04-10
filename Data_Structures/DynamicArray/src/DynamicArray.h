#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H
/**
 * @file DynamicArray.h
 * @author Kevin Pluas (kpluas21@gmail.com)
 * @brief Specification of DynamicArray
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
 * 
 */
//TODO: FUNCTIONS TO BE ADDED
/** * 
 * 1) remove : Removes an element from the array , everything will have to be stitched together
 */

#include<stddef.h>


/**
 * @enum DataType
 * @brief Constants used to label the data type of the elements in our dynamic array
 */
typedef enum DataType {
    INT,
    CHAR,
    FLOAT,
    DOUBLE,
    STRING,

}DataType;

typedef enum ErrorCode {
    SUCCESS = 0, 
    OUT_OF_MEMORY,
    INVALID_ARGUMENT, 
    INVALID_DATATYPE,
    OUT_OF_BOUNDS_INDEX,
    UNKNOWN_ERROR,

}ErrorCode;

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
 * @brief Initializes our dynamic array. Returns NULL if unsuccessful. 
 * @param type The data type for our elements
 * @param data The initial data to be stored in the array
 * @param size The number of initial elements 
 * @return DynamicArray* : A pointer to a DynamicArray struct.
 */
DynamicArray *DynamicArray_init(DataType type, void *data, size_t size);

//TODO : This takes a single void pointer as input. Are we able to append JUST one or can we append everything in the pointer?
/**
 * @brief Appends the given element to the end of the array, automatically resizing the array if necessary.
 * 
 * @param array The DynamicArray pointer
 * @param elem The element to be added
 */
void DynamicArray_append(DynamicArray *array, void *elem);

/**
 * @brief Prints out the contents of the DynamicArray to stdout
 * 
 * @param array The DynamicArray pointer
 */
void DynamicArray_print(DynamicArray *array);

/**
 * @brief Displays the meta info about our dynamic array such as size, capacity, type, and contents so long as the size does
 * not exceed 1000.
 * 
 * @param array The DynamicArray pointer
 */
void DynamicArray_debug_info(DynamicArray *array);

/**
 * @brief Frees up all memory used by the array including the struct itself.
 * Pass a reference to the DynamicArray pointer, that way everything will be 
 * NULL'd safely.
 * @param array A pointer to a DynamicArray pointer
 */
void DynamicArray_delete(DynamicArray **array);

/**
 * @brief Removes from the array a single element. Reduces the size of the array by 1 and 
 * closes the gap by shifting every element over by 1. The capacity remains unchanged after
 * this operation.
 * 
 * @param array The DynamicArray pointer
 * @param index The index of the element
 */
void DynamicArray_remove(DynamicArray *array, size_t index);
/**
 * @brief Clears out the entire array, reducing the size to 0. Does not change the 
 * capacity in any way.
 * 
 * @param array The DynamicArray pointer
 */
void DynamicArray_empty(DynamicArray *array);

/**
 * @brief Compares two elements in the array. Mostly used by other 
 * functions in this library
 * 
 * @param type The datatype of the elements
 * @param elem1 The first element
 * @param elem2 The second element
 * @return int 0 if elements are equal, <0 if x is less than y, 
 *         >0 if x is greater than y;
 */
int DynamicArray_cmp(DataType type, void *elem1, void *elem2);

/**
 * @brief Swaps the contents of two elements.
 * 
 * @param type The data type of the elements
 * @param elem1 The first element
 * @param elem2 The second element
 */
void DynamicArray_swap(DataType type, void *elem1, void *elem2);

/**
 * @brief Retrieves the element at the specified index.
 * 
 * @param array The DynamicArray pointer
 * @param index Index of the element
 * @return void* A void pointer that points to the result of this function call.
 */
void *DynamicArray_get(DynamicArray *array, size_t index);

/**
 * @brief Attempts to sort the contents of the array in either ascending or descending order depending on
 * the mode provided. Uses selection sort.
 * 
 * @param array The DynamicArray pointer
 * @param mode 1 : Descending, anything else if ascending.
 */
void DynamicArray_sort(DynamicArray *array);

/**
 * @brief Returns 0 if the array is empty. Otherwise, returns a nonzero value.
 * 
 * @param array The DynamicArray pointer
 * @return int 0 if empty, otherwise the size of the array.
 */
int DynamicArray_isEmpty(DynamicArray *array);

/**
 * @brief Inserts an element at the chosen index. This effectively shifts all 
 * existing elements over. Automatically reallocates memory if needed.
 * If index equals size, it will basically act as _append() would. 
 * 
 * @param array The DynamicArray pointer
 * @param elem The element to be inserted
 * @param index The location where the element is to be inserted
 * @return int Returns 0 if successful, <0 if error encountered.
 */
int DynamicArray_insert(DynamicArray *array, void *elem, size_t index);

/**
 * @brief Linearly searches through the array to find the given input, returning the index if found, 
 * -1 otherwise
 * Caution must be used when comparing floating-point values because of general imprecision. Use 
 * an epsilon for some "good enough" results. You may need to change the epsilon to suit your needs.
 * @note Epsilon Values :
 * Float : 0.001
 * Double: 0.000001
 * 
 * @param array The DynamicArray pointer
 * @param ptr A void pointer pointing to the data needing to be searched for.
 * @return int The index where the element is located at.
 */
size_t DynamicArray_find(DynamicArray *array, void *elem);

/**
 * @brief Attempts to resize the array by doubling the current capacity and realloc'ing 
 * the pointer
 * 
 * @param array The DynamicArray pointer
 * @return DynamicArray* A pointer to the struct with the newly realloc'd data pointer. 
 */
DynamicArray *DynamicArray_resize(DynamicArray *array);


/**
 * @brief Outputs error messages
 * 
 * @param error The ErrorCode int
 * @return const char* A string detailing the error and where it occured
 */
const char* DynamicArray_error(ErrorCode error, const char* function);


#endif //DYNAMIC_ARRAY_H