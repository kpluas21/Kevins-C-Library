/**
 * @file LinkC.c
 * @author Kevin Pluas (kpluas21@gmail.com)
 * @brief Implementation of LinkC
 * @version 0.1
 * @date 2023-04-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#include"LinkC.h"

LinkC *LinkC_init(DataType type, void *data) {
    LinkC *list = malloc(sizeof(LinkC));
    if(list == NULL) {
        fprintf(stderr, "Error in function %s: Unable to allocate memory for LinkC\n", __func__);
        return NULL;
    }

    list->type = type;
    LinkCNode *head = malloc(sizeof(LinkCNode));

    if(head == NULL) {
        fprintf(stderr, "Error in function %s: Unable to allocate memory for LinkCNode\n", __func__);
        return NULL;
    }

    
    switch (type) {
    case INT: {
        head->data = (int*)data;
        break;
    }
    case CHAR: {

    }
    case FLOAT: {

    }
    case DOUBLE: {

    }
    case STRING: {

    }
    default:
        break;
    }

    //Init some variables to start us off
    list->head = head; //Since head is our only node, it is both the head and tail
    list->tail = head;
    list->size = 1;

    head->prev = NULL; //Following the rules previously established, both ends are NULL
    head->next = NULL;

    return list;
}
