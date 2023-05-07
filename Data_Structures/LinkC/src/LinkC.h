#ifndef LINKC_H
#define LINKC_H
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
 * @brief ErrorCodes used for debugging errors that occur while using LinkC
 * 
 */
typedef enum ErrorCode {
    E_SUCCESS = 0,
    E_OUT_OF_MEMORY,
    E_INVALID_ARGUMENT, 
    E_INVALID_DATATYPE,
    E_OUT_OF_BOUNDS_INDEX,
    E_UNKNOWN_ERROR,
    E_ERROR_COUNT, //Dummy error, used to determine how many valid codes there are

}ErrorCode;

static const char* const ERROR_STRINGS[] = {
    "E_SUCCESS",
    "E_OUT_OF_MEMORY",
    "E_INVALID_ARGUMENT",
    "E_INVALID_DATATYPE",
    "E_OUT_OF_BOUNDS_INDEX",
    "E_UNKNOWN_ERROR",
};

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
 * @brief The main object that users will use to interact with the linked list.
 * 
 * @var LinkC::data_size
 * The size, in bytes, each element is.
 * 
 * @var LinkC::alloc_data
 * The amount of bytes used by the elements overall. Used for determining the amount of elements.
 * 
 * @var LinkC::head
 * A pointer to the head, or the first element, of the linked list.
 * 
 * @var LinkC::tail
 * A pointer to the tail, or the last element, of the linked list.
 */
typedef struct LinkC {
    size_t     data_size;
    size_t     alloc_Data;   
    LinkCNode *head;
    LinkCNode *tail;
}LinkC;

/**
 * @struct LinkCNode
 * @brief The nodes that make up our linked list. These are considered the actual "elements" of the linked list.
 * 
 * @var LinkCNode::prev
 * A pointer to the previous node in the linked list
 * 
 * @var LinkCNode::next
 * A pointer to the next node in the linked list
 * 
 * @var LinkCNode::data
 * A pointer to the actual data contained in the node.
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
 * @param data_size The size, in bytes, of each elements.
 * @param data A pointer to our initial data.
 * @return LinkC* 
 */
LinkC *LinkC_init(size_t data_size, void *data);

/**
 * @brief Returns the number of elements in the array
 * 
 * @param list LinkC pointer to our list
 * @return Number of elements as size_t
 */
size_t LinkC_size(LinkC *list);

/**
 * @brief Inserts a single element at the end of the list
 * 
 * @param list LinkC pointer to our list
 * @param data Void pointer to our data
 */
void LinkC_insert_at_end(LinkC *list, void *data);

/**
 * @brief Retrieves the data at the index specified
 * 
 * @param list LinkC pointer to our list
 * @param indexOfElem Index to search for our data
 * @return Void pointer to our result
 */
void *LinkC_get(LinkC *list, size_t indexOfElem);

/**
 * @brief Attempts to find the specified data in our list. 
 * 
 * @param list LinkC pointer to our list
 * @param data Void pointer to the item we want to find
 * @return The index where the item is located, -1 otherwise.
 */
int LinkC_find(LinkC *list, void *data);

/**
 * @brief Frees up all memory used by our list and their respective pointers
 * 
 * @param list LinkC pointer to our list
 */
void LinkC_delete(LinkC **list);


/**
 * @brief Removes a single node from the middle of the list at the 
 * specified index
 * 
 * @param list The linked list
 * @param index The index of the element to be removed
 */
void LinkC_remove_at_middle(LinkC *list, size_t index);

/**
 * @brief Removes the first node at the head of the list
 * 
 * @param list 
 */
void LinkC_remove_head(LinkC *list);

/**
 * @brief Removes the last node at the tail of the list
 * 
 * @param list 
 */
void LinkC_remove_tail(LinkC *list);

/**
 * @brief Inserts a single element at the end of the list.
 * 
 * @param list LinkC pointer to our list
 * @param data Void pointer to our data to be inserted
 */
void LinkC_insert_at_start(LinkC *list, void *data);

/**
 * @brief Inserts a single element at the specified index. 
 * 
 * @param list LinkC pointer to our list
 * @param data Void pointer to our data to be inserted
 * @param index The index where the data is to be inserted
 */
void LinkC_insert_at_index(LinkC *list, void *data, size_t index);

/**
 * @brief Displays an error message
 * 
 * @param code The type of error encountered
 * @return A string detailing the error encountered.
 */
void LinkC_error_report(ErrorCode code);

#endif //LINK_C