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
#include<errno.h>

#include"LinkC.h"

LinkC *LinkC_init(size_t data_size, void *data) {
    LinkC *list = malloc(sizeof(LinkC));
    LinkCNode *head = malloc(sizeof(LinkCNode));

    if(list == NULL || head == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    head->data = malloc(data_size);

    if(head->data == NULL) {
        errno = ENOMEM;
        return NULL;
    }
    memcpy(head->data, data, data_size);

    list->data_size = data_size;
    list->alloc_Data = data_size;

    list->head = head;
    list->tail = head;
    head->prev = NULL;
    head->next = NULL;
    
    return list;
}

size_t LinkC_size(LinkC *list) {
    return list->alloc_Data / list->data_size;
}

int LinkC_insert_at_end(LinkC *list, void* data) {
    LinkCNode *current = list->tail;

    LinkCNode *newNode = malloc(sizeof(LinkCNode));
    if(newNode == NULL) {
        errno = ENOMEM;
        return -1;
    }

    newNode->data = malloc(list->data_size);
    if(newNode->data == NULL) {
        free(newNode);
        errno = ENOMEM;
        return -1;
    }
    
    memcpy(newNode->data, data, list->data_size);

    current->next = newNode;
    newNode->prev = current;
    newNode->next = NULL;
    list->tail = newNode;

    list->alloc_Data += list->data_size;
    
    return 0;
}

void *LinkC_get(LinkC *list, size_t indexOfElem) {
    LinkCNode *current = list->head;
    size_t currentIndex = 0;

    while(current != NULL) {
        if(currentIndex == indexOfElem) {
            return current->data;
        }
        currentIndex++;
        current = current->next;
    }
    return NULL;
}

int LinkC_find(LinkC *list, void *data) {
    LinkCNode *current = list->head;
    int index = 0;

    while(current != NULL) {
        if(memcmp(current->data, data, list->data_size) == 0) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;
}

void LinkC_delete(LinkC **list) {
    if(list == NULL || (*list) == NULL) {
        errno = EINVAL;
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

// void LinkC_remove_at_middle(LinkC *list, size_t index) {
//     size_t curr_list_size = LinkC_size(list);
//     if(index >= curr_list_size) {
//         errno = EINVAL;
//         return;
//     }

//     //if beginning or ending index is provided, simply use those dedicated
//     //functions.

//     //REMOVE HEAD
//     else if(index == 0) {
//         LinkC_remove_first(list);
//         return;
//     }
//     //REMOVE TAIL
//     else if(index == curr_list_size - 1) {
//         LinkC_remove_last(list);
//         return;
//     }

//     //Now we remove a node at the middle. There should be a valid node
//     //on both sides of the one to be removed.
//     LinkCNode *traversal_ptr = list->head;

//     //Traverse until we reach right before the node to be removed.
//     for (size_t i = 0; i < index; i++) {
//         traversal_ptr = traversal_ptr->next;
//     }
//     //This node will be the one to be free'd
//     LinkCNode *temp = traversal_ptr->next;

//     temp->prev->next = temp->next;
//     temp->next->prev = temp->prev;
//     free(temp->data);
//     free(temp);

//     list->alloc_Data -= list->data_size;

//     return;
// }

void LinkC_remove_first(LinkC *list) {
    if(list->head == list->tail) {
        //Only one element in the list
        free(list->head->data);
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
        
        
    }
    else {    
        //At least two elements,  head != tail
        LinkCNode *temp = list->head;
        list->head = list->head->next;
        list->head->prev = NULL;
        free(temp->data);
        free(temp);
        
    }

    list->alloc_Data -= list->data_size;
    return;
}

void LinkC_remove_last(LinkC *list) {
    if(list->head == list->tail) {
        //Only one element in the list
        free(list->head->data);
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
    }

    else {
        LinkCNode *temp = list->tail;
        list->tail = list->tail->prev;
        list->tail->next = NULL;
        free(temp->data);
        free(temp);
    }

    list->alloc_Data -= list->data_size;
    return;
}

int LinkC_insert_at_start(LinkC *list, void *data)
{
    LinkCNode *newNode = malloc(sizeof(LinkCNode));
    if(newNode == NULL) {
        errno = ENOMEM;
        return -1;
    }
    
    newNode->data = malloc(list->data_size);
    if(newNode->data == NULL) {
        free(newNode);
        errno = ENOMEM;
        return -1;
    }

    memcpy(newNode->data, data, list->data_size);

    newNode->next = list->head;
    newNode->prev = NULL;

    list->head->prev = newNode;
    list->head = newNode;
    
    list->alloc_Data += list->data_size;
    return 0;
}
