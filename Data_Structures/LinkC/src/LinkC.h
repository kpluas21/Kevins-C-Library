/**
 * @file LinkC.h
 * @author Kevin Pluas (kpluas21@gmail.com)
 * @brief Interface for LinkC, a custom generic doubly-linked list in C
 * @version 0.1
 * @date 2023-04-10
 * 
 * @copyright Copyright (c) 2023
 * 
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
    DataType   type;
    size_t     size;
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
 * @brief Initializes our linked list.
 * 
 * @param type The data type of the elements in the list
 * @param data The first element to be appended to the list
 * @return A pointer to the LinkC struct. 
 */
LinkC *LinkC_init(DataType type, void *data);

/**
 * @brief Appends an element to the end of the linked list. 
 * 
 * @param list 
 * @param data 
 */
void LinkC_append(LinkC *list, void *data);

/**
 * @brief Attempts to search for the given data in the linked list.
 * 
 * @param list Our LinkC pointer
 * @param data The data to search for
 * @return The index where the data can be found, -1 otherwise.
 */
int LinkC_find(LinkC *list, void *data);

/**
 * @brief Frees up all the memory used by our list.
 * 
 * @param list Our linked list. Becomes NULL on completion.
 */
void LinkC_delete(LinkC **list);