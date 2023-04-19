/**
 * @file bstC.h
 * @author Kevin Pluas (kpluas21@gmail.com)
 * @brief Interface for bstC
 * @version 0.1
 * @date 2023-04-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */

typedef struct BstCNode BstCNode;

typedef struct BstCNode {
    BstCNode *parent;
    BstCNode *left_child;
    BstCNode *right_child;
    signed int data;
}BstCNode;

/**
 * @brief Initializes our BST with the root node and a single element to add 
 * to the root node.
 * 
 * @param elem 
 * @return BstCNode* 
 */
BstCNode *BstCNode_init(signed int elem);

/**
 * @brief Inserts a new node into the tree
 * 
 * @param elem The number to add to the new node
 */
void BstCNode_insert(BstCNode *root, signed int elem);

void BstCNode_remove(BstCNode *root, signed int elem);

/**
 * @brief Prints all the elements of the tree in order.
 * 
 * @param node The BstCNode pointer
 */
void BstCNode_print_inOrder(BstCNode *node);

/**
 * @brief Frees up and deletes all nodes associated with the root BstC node.
 * Also renders the intial pointer as NULL
 * 
 * @param root 
 */
void BstCNode_delete(BstCNode **root);

size_t BstCNode_height(BstCNode *node);

/**
 * @brief Returns the minimum value found in this BST
 * 
 * @param root The root node to search through
 * @return signed int 
 */
signed int BstCNode_min(BstCNode *root);

signed int BstCNode_max(BstCNode *root);



