/**
 * @file DynamiC.c
 * @author your name (you@domain.com)
 * @brief Implementation of DynamiC
 * @version 0.0.2
 * @date 2023-04-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include"DynamiC.h"

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

DynamiC *DynamiC_init(DataType type, void *data, size_t size) {
    DynamiC *array = malloc(sizeof(DynamiC));

    if(array == NULL) {
        fprintf(stderr, "Error: In function: %s: Unable to allocate memory for DynamiC struct\n", __func__);
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
        printf("Error: Unable to allocate memory for DynamiC:data\n");
        return NULL;
    }

    return array;
}


void DynamiC_debug_info(DynamiC *array) {

    printf("Data type of the elements stored (DataType) : %d\n", array->type);

    printf("Number of elements currently in our array (size) : %zu\n", array->size);
    printf("Max number of elements that can be currently stored (capacity) : %zu\n", array->capacity);
    if(array->size >= 1000) {
        return;
    }
    printf("Elements currently stored (data) : \n");
    DynamiC_print(array);
}


void DynamiC_print(DynamiC *array) {
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


inline void DynamiC_append(DynamiC *array, void* elem) {
    if(array->size == array->capacity) {
        array = DynamiC_resize(array);
        if(array == NULL) {
            return;
        }
        
    }
    switch (array->type) {
    case INT: {
        *((int*)array->data + array->size) = *(int*)elem;
        break;
    }
    case CHAR: {
        *((char*)array->data + array->size) = *(char*)elem;
        break;
    }
    case DOUBLE: {
        *((double*)array->data + array->size) = *(double*)elem;
        break;
    }
    case FLOAT: {
        *((float*)array->data + array->size) = *(float*)elem;
        break;
    }
    case STRING:
        break;
    }
    array->size++;
    return;
}


inline DynamiC* DynamiC_resize(DynamiC *array) {
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
        fprintf(stderr, "Error: In function: %s: Unable to resize DynamiC.data\n", __func__);
        return NULL;
    }

    return array;
}

void DynamiC_delete(DynamiC **array) {
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


size_t DynamiC_find(DynamiC *array, void *elem) {
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
int DynamiC_insert(DynamiC *array, void *elem, size_t index) {
    if(array->size == array->capacity) {
        array = DynamiC_resize(array);
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

void *DynamiC_get(DynamiC *array, size_t index) {
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


inline void DynamiC_sort(DynamiC *array) {
    size_t j;
    switch(array->type) {
    case INT: {
        for (size_t i = 0; i < array->size - 1; i++)
        {
            size_t min = i;
            for (j = i; j < array->size; j++)
            {
                if(DynamiC_cmp(INT, ((int*)array->data + j), ((int*)array->data + min)) < 0) {
                    min = j;
                }
            }
            if(min != i) {
                DynamiC_swap(INT, (int*)array->data + i, (int*)array->data + min);
            }
            
        }
        
        break;
    }
    case CHAR: {
        for (size_t i = 0; i < array->size - 1; i++)
        {
            size_t min = i;
            for (j = i; j < array->size; j++)
            {
                if(DynamiC_cmp(CHAR, ((char*)array->data + j), ((char*)array->data + min)) < 0) {
                    min = j;
                }
            }
            if(min != i) {
                DynamiC_swap(CHAR, (char*)array->data + i, (char*)array->data + min);
            }
            
        }
        
        break;
    }
    case FLOAT: {
        for (size_t i = 0; i < array->size - 1; i++)
        {
            size_t min = i;
            for (j = i; j < array->size; j++)
            {
                if(DynamiC_cmp(FLOAT, ((float*)array->data + j), ((float*)array->data + min)) < 0) {
                    min = j;
                }
            }
            if(min != i) {
                DynamiC_swap(FLOAT, (float*)array->data + i, (float*)array->data + min);
            }
            
        }
        
        break;
    }
    case DOUBLE: {
        for (size_t i = 0; i < array->size - 1; i++)
        {
            size_t min = i;
            for (j = i; j < array->size; j++)
            {
                if(DynamiC_cmp(DOUBLE, ((double*)array->data + j), ((double*)array->data + min)) < 0) {
                    min = j;
                }
            }
            if(min != i) {
                DynamiC_swap(DOUBLE, (double*)array->data + i, (double*)array->data + min);
            }
            
        }
        
        break;
    }
    default:
        break;
    }
}


inline int DynamiC_isEmpty(DynamiC *array) {
    return array->size;
}


void DynamiC_remove(DynamiC *array, size_t index) {

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


void DynamiC_empty(DynamiC *array) {
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

const char *DynamiC_error(ErrorCode error, const char* function) {
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


int DynamiC_cmp(DataType type, void *elem1, void *elem2) {
    //We will have to use epsilons here again
    switch (type) {
    case INT: {
        return *(int*)elem1 - *(int*)elem2;
    }
    case CHAR: {
        return *(char*)elem1 - *(char*)elem2;

    }
    case FLOAT: {
        //Nearly equal as dictated by the epsilon
        if(fabs((*(float*)elem1) - (*(float*)elem2)) < FLTEPSILON) {
            return 0;
        }
        else if(*(float*)elem1 > *(float*)elem2) {
            return 1;
        }
        return -1;
    }
    case DOUBLE: {
        //Nearly equal as dictated by the epsilon
        if(fabs((*(double*)elem1) - (*(double*)elem2)) < DBEPSILON) {
            return 0;
        }
        else if(*(double*)elem1 > *(double*)elem2) {
            return 1;
        }
        return -1;
    }
    default:
        return 0;
    }

    //It should not reach here !!!
    return 0;

}

void DynamiC_swap(DataType type, void *elem1, void *elem2) {
    void *temp = malloc(sizeof(double));

    switch(type) {
    case INT: {
        *(int*)temp = *(int*)elem1;
        *(int*)elem1 = *(int*)elem2;
        *(int*)elem2 = *(int*)temp;
    }
        break;
    case CHAR: {
        *(char*)temp = *(char*)elem1;
        *(char*)elem1 = *(char*)elem2;
        *(char*)elem2 = *(char*)temp;
    }
        break;
    case FLOAT: {
        *(float*)temp = *(float*)elem1;
        *(float*)elem1 = *(float*)elem2;
        *(float*)elem2 = *(float*)temp;
    }
        break;
    case DOUBLE: {
        *(double*)temp = *(double*)elem1;
        *(double*)elem1 = *(double*)elem2;
        *(double*)elem2 = *(double*)temp;
    }
        break;
    default:
        break;
    }
}


/**
 * END FUNCTION DEFINITIONS
 * 
 * 
 */