/**
 * @file DynamicArray.c
 * @author your name (you@domain.com)
 * @brief Implementation of DynamicArray
 * @version 0.0.2
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
 * @brief Global epsilons to be used when comparing floating-point values. If you need to change
 * how precise the comparisons should be, change it here.
 * Used in the following functions
 * _find()
 * _cmp()
 * 
 */
#define FLTEPSILON 0.001
#define DBEPSILON 0.000001

DynamicArray *DynamicArray_init(DataType type, void *data, size_t size) {
    DynamicArray *array = malloc(sizeof(DynamicArray));

    if(array == NULL) {
        printf("Error: Unable to allocate memory for DynamicArray struct\n");
        return NULL;
    }

    array->size = size;
    array->type = type;
    array->capacity = (size == 0) ? 1 : size * 2;

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
        return NULL;
    }
    
    if(array->data == NULL) {
        printf("Error: Unable to allocate memory for DynamicArray:data\n");
        return NULL;
    }

    return array;
}


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


inline void DynamicArray_append(DynamicArray *array, void* elem) {
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


inline DynamicArray* DynamicArray_resize(DynamicArray *array) {
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


void DynamicArray_delete(DynamicArray **array) {
    if(array == NULL || *array == NULL) {
        return;
    }
    if((*array)->data != NULL) {
        free((*array)->data);
        (*array)->data = NULL;
    }
    free(*array);
    (*array) = NULL;

}


size_t DynamicArray_find(DynamicArray *array, void *elem) {
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
            if(fabs(dest[i] - *elemToFind) < FLTEPSILON) {
                return i;
            }
        }
        break;
    }
    case DOUBLE: {
        double *dest = array->data;
        double *elemToFind = (double*) elem;
        for (size_t i = 0; i < array->size; i++) {
            if(fabs(dest[i] - *elemToFind) < DBEPSILON) {
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

//There are three scenarios when inserting
//1) At the beginning of the array
//2) At the middle
//3) At the end
int DynamicArray_insert(DynamicArray *array, void *elem, size_t index) {
    if(array->size == array->capacity) {
        array = DynamicArray_resize(array);
    }
    if(index >= array->capacity || index > array->size) {
        printf("Error: Index %zu out of bounds\nArray Size = %zu\nArray Capacity = %zu\n",
         index, array->size, array->capacity);
         return -1;
    }

    if(array == NULL) {
        printf("Error: Unable to insert element\n");
        return -1;
    }

    switch(array->type) {
    case INT: {
        if(index == array->size) {
            *((int*)array->data + index) = *(int*)elem;
            break;
        }
        for (size_t i = array->size; i > index; i--) {
            *((int*)array->data + i) = *((int*)array->data + i - 1);
        }
        *((int*)array->data + index) = *(int*)elem;
        break;
    }
    case CHAR: {
        if(index == array->size) {
            *((char*)array->data + index) = *(char*)elem;
            break;
        }
        for (size_t i = array->size; i > index; i--) {
            *((char*)array->data + i) = *((char*)array->data + i - 1);
        }
        *((char*)array->data + index) = *(char*)elem;
        break;
    }
    case FLOAT: {
        if(index == array->size) {
            *((float*)array->data + index) = *(float*)elem;
            break;
        }
        for (size_t i = array->size; i > index; i--) {
            *((float*)array->data + i) = *((float*)array->data + i - 1);
        }
        *((float*)array->data + index) = *(float*)elem;
        break;
    }
    case DOUBLE: {
        if(index == array->size) {
            *((double*)array->data + index) = *(double*)elem;
            break;
        }
        for (size_t i = array->size; i > index; i--) {
            *((double*)array->data + i) = *((double*)array->data + i - 1);
        }
        *((double*)array->data + index) = *(double*)elem;
        break;
    }
    default:
        break;
    }

    array->size++;
    return 0;
}

void *DynamicArray_get(DynamicArray *array, size_t index) {
    if(index >= array->size) {
        printf("Error: Out-of-bounds index provided : %zu\n", index);
        return NULL;
    }

    void *result = NULL;

    switch (array->type) {
    case INT: {
        result = ((int*)array->data + index);
        break;
    }
    case CHAR: {
        result = ((char*)array->data + index);
        break;
    }
    case FLOAT: {
        result = ((float*)array->data + index);
        break;
    }
    case DOUBLE: {
        result = ((double*)array->data + index);
        break;
    }
    default:
        return NULL;
    }

    return result;
}


// inline void DynamicArray_sort(DynamicArray *array, int mode) {
//     //TODO: IMPLEMENT THIS
// }


inline int DynamicArray_isEmpty(DynamicArray *array) {
    return array->size;
}


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

// int DynamicArray_cmp(DataType type, void *elem1, void *elem2) {
//     //We will have to use epsilons here again
//     switch (type) {
//     case INT: {
//         int *l = (int*) elem1;
//         int *r = (int*) elem2;

//         return *l - *r;
//     }
//     case CHAR: {
//         char *l = (char*) elem1;
//         char *r = (char*) elem2;

//         return *l - *r;
//     }
//     case FLOAT: {
//         float *l = (float*) elem1;
//         float *r = (float*) elem2;

//         //Nearly equal
//         if(fabs(*l - *r) < FLTEPSILON) {
//             return 0;
//         }

//         else if(*l > *r) {
//             return 1;
//         }
//         //
//         return -1;
//     }
//     case DOUBLE: {
//         double *l = (double*) elem1;
//         double *r = (double*) elem2;
//         break;
//         //Nearly equal
//         if(fabs(*l - *r) < DBEPSILON) {
//             return 0;
//         }

//         else if(*l > *r) {
//             return 1;
//         }
//         //
//         return -1;
//     }
//     default:
//         return 0;
//     }

//     //It should not reach here !!!
//     return 0;

// }

// void DynamicArray_swap(DataType type, void *elem1, void *elem2) {
//     switch(type) {
//     case INT: {
//         int *l, *r, *temp;
        
//     }
//         break;
//     case CHAR:
//         break;
//     case FLOAT:
//         break;
//     case DOUBLE:
//         break;
//     default:
//         break;
//     }
// }


/**
 * END FUNCTION DEFINITIONS
 * 
 * 
 */