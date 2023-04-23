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
typedef struct BstC BstC;


typedef struct BstC {
    size_t size;
    BstCNode *root;
}BstC;

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
 * @return BstC* Our main BST struct 
 */
BstC *BstCNode_init(void);

/**
 * @brief Inserts a new node into the tree
 * 
 * @param elem The number to add to the new node
 */
void BstCNode_insert(BstC *tree, signed int elem);

// /**
//  * @brief Removes a specified node from the BST
//  * 
//  * @param root The root node to search through
//  * @param elem The element to search for deletion
//  */
// void BstCNode_remove(BstC *tree, signed int elem);

/**
 * @brief Prints all the elements of the tree in order.
 * 
 * @param node The BstCNode pointer
 */
void BstCNode_print_inOrder(BstC *node);

/**
 * @brief Frees up and deletes all nodes associated with the root BstC node.
 * Also renders the intial pointer as NULL
 * 
 * @param root 
 */
void BstCNode_delete(BstC **tree);

/**
 * @brief Returns the max height of the tree
 * 
 * @param node 
 * @return size_t 
 */
size_t BstCNode_height(BstC *node);

/**
 * @brief Returns the minimum value found in this BST
 * 
 * @param root The root node to search through
 * @return signed int 
 */
signed int BstCNode_min(BstC *root);

/**
 * @brief Returns the maximum value found in this BST
 * 
 * @param root The root node to search through
 * @return signed int 
 */
signed int BstCNode_max(BstC *root);


/**
 * @brief Returns the node whose key matches the one provided by the user
 * 
 * @param tree 
 * @param key 
 * @return BstCNode* 
 */
BstCNode *BstC_search(BstC *tree, signed int key);
