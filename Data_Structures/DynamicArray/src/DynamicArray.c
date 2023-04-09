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
        fprintf(stderr, "Error: In function: %s: Unable to allocate memory for DynamicArray struct\n", __func__);
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
        *((int*)array->size + array->size) = *(int*)elem;
        break;
    }
    case CHAR: {
        *((char*)array->size + array->size) = *(char*)elem;
        break;
    }
    case DOUBLE: {
        *((double*)array->size + array->size) = *(double*)elem;
        break;
    }
    case FLOAT: {
        *((float*)array->size + array->size) = *(float*)elem;
        break;
    }
    case STRING:
        break;
    }
    array->size++;
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
        fprintf(stderr, "Error: In function: %s: Unable to resize DynamicArray.data\n", __func__);
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
        for (size_t i = 0; i < array->size; i++) {
            if( *((int*)array->data + i) == *(int*)elem) {
                return i;
            }
        }
        break;
    }
    case CHAR: {
        for (size_t i = 0; i < array->size; i++) {
            if( *((char*)array->data + i) == *(char*)elem) {
                return i;
            }
        }
        break;
    }
    case FLOAT: {
        for (size_t i = 0; i < array->size; i++) {
            if(fabs((*(float*)array->data + i) - (*(float*)elem)) < FLTEPSILON) {
                return i;
            }
        }
        
        break;
    }
    case DOUBLE: {
        for (size_t i = 0; i < array->size; i++) {
            if(fabs((*(double*)array->data + i) - (*(double*)elem)) < DBEPSILON) {
                return i;
            }
        }
        break;
    }
    default:
        //TODO:DATATYPE ERROR HERE
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
        printf("Error: In function %s : Index %zu out of bounds\nArray Size = %zu\nArray Capacity = %zu\n",
         __func__, index, array->size, array->capacity);
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
        fprintf(stderr, "Error: In function: %s: Out-of-bounds index provided : %zu\n", __func__, index);
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
    //TODO: This acts funky when calling it more than a single time in a row
    //Probably needs a complete do over
    if(index >= array->size) {
        fprintf(stderr, "Error: In function: %s: Invalid index provided : %zu\n", __func__, index);
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

const char *DynamicArray_error(ErrorCode error, const char* function) {
    char *errorMsg = malloc(256);

    switch (error) {
    case SUCCESS:
        break;
    case OUT_OF_MEMORY:
        snprintf(errorMsg, 256, "%s Error: Unable to allocate memory.\n", function);
        break;
    case INVALID_ARGUMENT:
        snprintf(errorMsg, 256, "%s Error: Invalid argument provided.\n", function);
        break;
    case INVALID_DATATYPE:
        snprintf(errorMsg, 256, "%s Error: Invalid DataType provided.\n", function);
        break;
    case OUT_OF_BOUNDS_INDEX:
        snprintf(errorMsg, 256, "%s Error: Index provided is out of bounds of the array.\n", function);
        break;
    default:
        snprintf(errorMsg, 256, "%s Error: Unknown Error encountered!\n", function);
        break;
    }

    return errorMsg;
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