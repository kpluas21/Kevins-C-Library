//My implementation of a dynamic array for several data types. This data structure works similarly to std::vector in C++. 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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

void DynamicArray_append(DynamicArray *array, void *elem);
void DynamicArray_print(DynamicArray *array);
void DynamicArray_debug_info(DynamicArray *array);
DynamicArray *DynamicArray_init(DataType type, void *data, size_t size);
DynamicArray *DynamicArray_resize(DynamicArray *array);


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
 * @brief Displays the meta info about our dynamic array
 * 
 * @param array 
 */
void DynamicArray_debug_info(DynamicArray *array) {
    printf("Data type of the elements stored (DataType) : %d\n", array->type);
    printf("Number of elements currently in our array (size) : %ld\n", array->size);
    printf("Max number of elements that can be currently stored (capacity) : %ld\n", array->capacity);
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
        for(int i = 0; i < array->size - 1; i++) {
            printf("%d, ", dest[i]);
            
        }
        printf("%d]\n", dest[array->size - 1]);
        return;
    }
    case CHAR: {
        char *dest = (char*) array->data;
        printf("[");
        for (int i = 0; i < array->size - 1; i++) {
            printf("%c, ", dest[i]);
        }
        printf("%c]\n", dest[array->size - 1]);
        return;
    }
    default:
        break;
    }
}

//TODO: FUNCTIONS TO BE ADDED
/**
 * 1) appends : Adds an element to the end of the array, resizing if necessary 
 * 2) find : Attempts to find the given input, outputting the index if found, -1 otherwise
 * 3) get : Returns the element given the index as input. 
 * 4) remove : Removes an element from the array , everything will have to be stitched together
 * 5) resize : Resizes the array, increasing or decreasing the amount of memory assigned to the void pointer
 */


/**
 * @brief Adds the given element to the end of the array, automatically resizing the array if necessary.
 * 
 * @param array The dynamic array
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
        break;
    case DOUBLE:
        break;
    case FLOAT:
        break;
    case STRING:
        break;
    }
    return;
}


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
