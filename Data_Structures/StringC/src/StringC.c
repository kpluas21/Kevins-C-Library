/**
 * @file StringC.c
 * @author Kevin Pluas (kpluas21@gmail.com)
 * @brief Implementation of StringC
 * @version 0.1
 * @date 2023-05-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include"StringC.h"
#include<stdlib.h>
#include<stdio.h>

StringC *StringC_init(const char *inital_string) {
    StringC *string = malloc(sizeof(StringC));
    if(!string) {
        fprintf(stderr, "Error: Cannot allocate for StringC\n");
        return NULL;
    }

    

}
