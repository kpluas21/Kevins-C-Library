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

int *generate_unique_ints(void);



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

#endif //_HELPER_FUNCTIONS_H