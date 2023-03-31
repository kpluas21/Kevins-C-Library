//My implementation of a dynamic array for several data types. This data structure works similarly to std::vector in C++. 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

typedef union {
    int i;
    char c;
    float f;
    double d;
}Data;

/**
 * @enum DataType
 * @brief Constants used to label the data type of the elements in our dynamic array
 */
enum DataType {
    INT,
    CHAR,
    DOUBLE,
    FLOAT,
    STRING,

};

/**
 * @struct DynamicArray
 * @brief Our main struct that contains all the data and metainfo about our dynamic array
 * @var DynamicArray::type
 */
struct DynamicArray {
    enum DataType type;
    size_t size;
    size_t capacity;
    Data *data;  
};

/**
 * @brief Initializes our dynamic array
 * 
 * @param type The data type for our elements
 * @param data The initial data to be store in the array
 * @param size The number of initial elements 
 * @return struct DynamicArray* : A pointer to our DynamicArray struct containing everything we need
 */
struct DynamicArray* DynamicArray_init(enum DataType type, void *data, size_t size) {
    struct DynamicArray* da = malloc(sizeof(struct DynamicArray));

    if(da == NULL) {
        printf("Error: Unable to allocate memory for DynamicArray\n");
        return NULL;
    }

    da->size = size;
    da->type = type;
    da->capacity = size * 2;

    switch (type) {
    case INT:
        da->data = malloc(size * sizeof(int));
        memcpy(da->data, data, size * sizeof(int));
        break;
    case CHAR:
        da->data = malloc(size * sizeof(char));
        memcpy(da->data, data, size * sizeof(char));
        break;
    case DOUBLE:
        da->data = malloc(size * sizeof(double));
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

/// @brief Pretty prints the contents of our array
/// @param array Our dynamic array ptr
void DymanicArray_print(struct DynamicArray *array) {
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


void DynamicArray_append(struct DynamicArray *array, Data elem) {
    switch (array->type) {
    case INT:{

        //Look 1 past the last element of the array 
        if(array->data[array->size] == NULL) {
            //resize

        }
        else{
            array->data[array->size] = elem;
        }
        break;
    }    
    default:
        break;
    }
    return;
}

void DynamicArray_resize(struct DynamicArray *array) {

}


int main(int argc, char const *argv[]) {
    int data[] = {1, 2, 3, 4, 5};
    char chars[] = {'a', 'b', 'c', 'd', 'e'};

    struct DynamicArray *vector = DynamicArray_init(INT, data, 5);
    struct DynamicArray *chVector = DynamicArray_init(CHAR, chars, 5);

      
    
    DymanicArray_print(vector);
    DymanicArray_print(chVector);


    free(chVector);
    free(vector);
    return 0;
}
