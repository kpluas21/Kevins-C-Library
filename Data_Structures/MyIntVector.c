//My implementation of a dynamic array for integers

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


enum DataType {
    INT,
    CHAR,
    DOUBLE,
    FLOAT,
    STRING,

};

struct DynamicArray {
    enum DataType type;
    size_t size;
    void *data;  
};


struct DynamicArray* DynamicArray_init(enum DataType type, void *data, size_t size) {
    struct DynamicArray* da = malloc(sizeof(struct DynamicArray));

    if(da == NULL) {
        printf("Error: Unable to allocate memory for DynamicArray\n");
        return NULL;
    }

    da->size = size;
    da->type = type;

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
        printf("%ld\n",array->size);
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
