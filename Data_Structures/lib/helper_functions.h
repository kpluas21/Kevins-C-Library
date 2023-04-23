#ifndef _HELPER_FUNCTIONS_H
#define _HELPER_FUNCTIONS_H

/**
 * @file helper_functions.h
 * @author Kevin Pluas (kpluas21@gmail.com)
 * @brief Includes useful functions mainly used by the unit tests
 * @version 0.1
 * @date 2023-04-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int *generate_unique_ints(void);

char **get_array_of_strings(void);

void free_array_of_strings(char **array, size_t num_of_elements);

int *generate_unique_ints(void) {
    int *vector = (int*)malloc(sizeof(int) * 1000);
    for(int i = 0; i < 1000; i++) {
        vector[i] = i;
    }

    int j; int temp;
    for(int i = 0; i < 1000 - 2; i++) {
        j = rand() % (1000 - i) + i;
        temp = vector[i];
        vector[i] = vector[j];
        vector[j] = temp;
    }   
    return vector;
}

char **get_array_of_strings(void) {
    FILE *file = fopen("test_strings.txt", "r");

    if(file == NULL) {
        printf("Error: File could not be opened for testing!\n");
        return NULL;
    }
    char *line = (char*) malloc(sizeof(char) * 256);

    char **lineArray = (char**) malloc(sizeof(char*) * 100);

    for(int i = 0; fgets(line, 256, file) ; i++) {
        lineArray[i] = malloc(256);
        // printf("Size of line : %zu\n", sizeof(line));
        line[strcspn(line, "\n")] = 0;
        strcpy(lineArray[i], line);
    }
    free(line);

    fclose(file);
    return lineArray;
}

/**
 * @brief Frees up all memory associated with a pointer to pointers
 * 
 * @param array 
 */
void free_array_of_strings(char **array, size_t num_of_elements) {
    for (size_t i = 0; i < num_of_elements; i++)
    {
        free(array[i]);
    }

    free(array);
    
}

#endif //_HELPER_FUNCTIONS_H