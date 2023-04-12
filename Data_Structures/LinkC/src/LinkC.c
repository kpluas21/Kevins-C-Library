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

#define FLOAT_EPSILON 0.001
#define DOUBLE_EPSILON 0.000001

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

void LinkC_append(LinkC *list, void *data) {
    LinkCNode *current = list->tail;
    size_t numBytes;

    //At this point, the next node does not exist.
    LinkCNode *newNode = malloc(sizeof(LinkCNode));
    if(newNode == NULL) {
        fprintf(stderr, "%s Error: Unable to initialize newNode\n", __func__);
        return;
    }

    newNode->data = NULL;

    switch (list->type) {
    case INT: {
        newNode->data = malloc(sizeof(int));
        numBytes = sizeof(int);
        break;
    }
    case CHAR: {
        newNode->data = malloc(sizeof(char));
        numBytes = sizeof(char);
        break;
    }
    case FLOAT: {
        newNode->data = malloc(sizeof(float));
        numBytes = sizeof(float);
        break;
    }
    case DOUBLE: {
        newNode->data = malloc(sizeof(double));
        numBytes = sizeof(double);
        break;
    }
    case STRING: {
        newNode->data = malloc(strlen((char*)data) + 1);
        numBytes = strlen((char*)data) + 1;
        break;
    }
    default:
        break;
    }

    if(newNode->data == NULL) {
        fprintf(stderr, "%s Error: Unable to initialize newNode->data\n", __func__);
        free(newNode);
        return;
    }

    memcpy(newNode->data, data, numBytes);

    list->tail = newNode;
    current->next = newNode;
    newNode->prev = current;
    newNode->next = NULL;
    list->size++;
}


void LinkC_print(LinkC *list) {
    LinkCNode *current = list->head;

    switch (list->type) {
    case INT: {
        while(current != NULL) {
            printf("[%d]", *(int*)current->data);
            printf("->");
            current = current->next;
        }
        puts("|");
        break;
    }
    case CHAR: {
        while(current != NULL) {
            printf("[%c]", *(char*)current->data);
            printf("->");
            current = current->next;
        }
        puts("|");
        break;
    }
    case FLOAT: {
        while(current != NULL) {
            printf("[%2.3f]", *(float*)current->data);
            printf("->");
            current = current->next;
        }
        puts("|");
        break;
    }
    case DOUBLE: {
        while(current != NULL) {
            printf("[%0.6f]", *(double*)current->data);
            printf("->");
            current = current->next;
        }
        puts("|");
        break;
    }
    case STRING: {
        while(current != NULL) {
            printf("[%s]", *(char**)current->data);
            printf("->");
            current = current->next;
        }
        puts("|");
        break;
    }
    default:
        break;
    }

}

int LinkC_find(LinkC *list, void *data) {
    LinkCNode *current = list->head;
    int index = 0;

    switch(list->type) {
    case INT: {
        while(current != NULL) {
            if(*(int*)current->data == *(int*)data) {
                return index;
            }
            current = current->next;
            index++;
        }
        break;
    }
    case CHAR: {
        while(current != NULL) {
            if(*(char*)current->data == *(char*)data) {
                return index;
            }
            current = current->next;
            index++;
        }
        break;
    }
    case FLOAT: {
        while(current != NULL) {
            if(fabs( (*(float*)current->data) - (*(float*)data) ) < FLOAT_EPSILON) {
                return index;
            }
            current = current->next;
            index++;
        }
        break;
    }
    case DOUBLE: {
        while(current != NULL) {
            if(fabs( (*(double*)current->data) - (*(double*)data) ) < DOUBLE_EPSILON) {
                return index;
            }
            current = current->next;
            index++;
        }
        break;
    }
    case STRING: {
        while(current != NULL) {
            if(strcmp(*(char**)current->data, *(char**)data) == 0) {
                return index;
            }
            current = current->next;
            index++;
        }
        break;
    }
    default:
        break;
    }

    return -1;
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
