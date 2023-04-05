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
 * 2) insert : Attempts to insert an element at the given index, shifting all other elements over, resizing the array if necessary
 * 3) sort : Sorts the elements of the array either in ascending or descending order. 
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

void DynamicArray_append(DynamicArray *array, void *elem);
void DynamicArray_print(DynamicArray *array);
void DynamicArray_debug_info(DynamicArray *array);
void DynamicArray_delete(DynamicArray *array);
void DynamicArray_remove(DynamicArray *array, size_t index);
void DynamicArray_empty(DynamicArray *array);
void DynamicArray_get(DynamicArray *array, size_t index, void *result);
void DynamicArray_sort(DynamicArray *array, int mode);

int DynamicArray_init(DynamicArray *array, DataType type, void *data, size_t size);
int DynamicArray_isEmpty(DynamicArray *array);

size_t DynamicArray_find(DynamicArray *array, void *elem);

DynamicArray *DynamicArray_resize(DynamicArray *array);


#endif //DYNAMIC_ARRAY_H