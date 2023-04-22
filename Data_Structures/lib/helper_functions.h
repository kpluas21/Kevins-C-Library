#ifndef _HELPER_FUNCTIONS_H
#define _HELPER_FUNCTIONS_H
/**
 * @file helper_functions.h
 * @author your name (you@domain.com)
 * @brief Includes useful functions mainly used by the unit tests
 * @version 0.1
 * @date 2023-04-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include<assert.h>
#include<stdlib.h>
#include<stdio.h>

int *generate_unique_ints(void);

char **get_array_of_strings(void);



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

inline char **get_array_of_strings(void) {
    FILE *file = fopen("test_strings.txt", "r");

    if(file == NULL) {
        printf("Error: File could not be opened for testing!\n");
        return NULL;
    }
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        //printf("%s", line);
        
    }

    fclose(file);
    return NULL;
    
}

#endif //_HELPER_FUNCTIONS_H