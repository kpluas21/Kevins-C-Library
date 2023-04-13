/**
 * @file LinkC.h
 * @author Kevin Pluas (kpluas21@gmail.com)
 * @brief Interface for LinkC, a custom generic doubly-linked list in C
 * @version 0.1
 * @date 2023-04-10
 * 
 * @copyright Copyright (c) 2023
 * 
 * 
 * @note The nodes are capable of storing ANY types of data, however I wanted to keep
 * it simple and only allow one type for the entire list. 
 */

#include<stddef.h>

/**
 * @enum DataType
 * @brief Constants used to label the data type of the elements in our linked list
 */
typedef enum DataType {
    INT,
    CHAR,
    FLOAT,
    DOUBLE,
    STRING,

}DataType;

//Forward declaration
typedef struct LinkCNode LinkCNode;

/**
 * @struct LinkC
 * @brief The main struct that contains essential information about our linked list
 * @param type The data type of the elements
 * @param size The number of elements in our list
 * @param head A pointer to the first node in the list
 * @param tail A pointer to the last node in the list
 * 
 */
typedef struct LinkC {
    size_t     dataSize;
    size_t     alloc_Data;   
    LinkCNode *head;
    LinkCNode *tail;
}LinkC;

/**
 * @struct LinkCNode
 * @brief The nodes that make up our linked list.
 * @param prev A pointer to the previous node in the list. NULL if the head node.
 * @param next A pointer to the next node in the list. NULL if the tail node.
 * @param data A pointer to the data contained in this node.
 * 
 */
typedef struct LinkCNode {
    LinkCNode *prev;
    LinkCNode *next;
    void      *data;
}LinkCNode;


/**
 * @brief 
 * 
 * @param dataSize 
 * @param data 
 * @return LinkC* 
 */
LinkC *LinkC_init(size_t dataSize, void *data);


size_t LinkC_size(LinkC *list);

void LinkC_append(LinkC *list, void *data);

void *LinkC_get(LinkC *list, int indexOfElem);

int LinkC_find(LinkC *list, void *data);

void LinkC_delete(LinkC **list);

void LinkC_insert_at_index(LinkC *list, void *data, int index);
