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
        head->data = malloc(sizeof(int));
        memcpy(head->data, data, sizeof(int));
        break;
    }
    case CHAR: {
        head->data = malloc(sizeof(char));
        memcpy(head->data, data, sizeof(char));
        break;
    }
    case FLOAT: {
        head->data = malloc(sizeof(float));
        memcpy(head->data, data, sizeof(float));
        break;
    }
    case DOUBLE: {
        head->data = malloc(sizeof(double));
        memcpy(head->data, data, sizeof(double));
        break;
    }
    case STRING: {
        //Grab length of data which SHOULD be a word here
        head->data = malloc(strlen((char*)data) + 1);
        strcpy(head->data, (char*)data);
        break;
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

// void LinkC_append(LinkC *list, void *data) {

// }

//
void LinkC_print(LinkC *list) {
    LinkCNode *current = list->head;

    switch (list->type) {
    case INT: {

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

}

void LinkC_delete(LinkC **list) {
    if(list == NULL || (*list) == NULL) {
        return; //Prevents double free's
    }
    
    LinkCNode *current = (*list)->head;
    LinkCNode *next;

    while (current != NULL) {
        next = current->next;
        free(current->data);
        free(current);
        current = next;
    }

    free(*list);
    (*list) = NULL;
    
}
