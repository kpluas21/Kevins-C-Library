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
 * @note The nodes are capable of storing ANY type of data with a defined size in bytes.
 * 
 */

#include<stddef.h>

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
 * @brief Inserts a single element at the end of the list.
 * 
 * @param list LinkC pointer to our list
 * @param data Void pointer to our data to be inserted
 */
int LinkC_insert_at_start(LinkC *list, void *data);

/**
 * @brief Inserts a single element at the end of the list
 * 
 * @param list LinkC pointer to our list
 * @param data Void pointer to our data
 */
int LinkC_insert_at_end(LinkC *list, void *data);

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
 * @brief Removes the first node at the head of the list
 * 
 * @param list 
 */
void LinkC_remove_first(LinkC *list);

/**
 * @brief Removes the last node at the tail of the list
 * 
 * @param list 
 */
void LinkC_remove_last(LinkC *list);

/**
 * @brief Traverses through the list and calls a user provided function pointer to print the data.
 * 
 * @param list A pointer to a valid LinkC object
 */
void LinkC_print(LinkC *list, 
                void (*LinkC_print_data) (void *data));

/**
 * @brief Same as LinkC_print but in reverse order.
 * 
 * @param list 
 * @param LinkC_print A function pointer to a print function.
 */
void LinkC_print_reverse(LinkC *list,
                        void (*LinkC_print_data) (void *data));


#endif //LINK_C