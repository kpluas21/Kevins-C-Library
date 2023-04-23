/**
 * @file bstC.c
 * @author Kevin Pluas (kpluas21@gmail.com)
 * @brief Implementation of bstC
 * @version 0.1
 * @date 2023-04-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"bstC.h"


BstC *BstC_init(void) {
    BstC *tree = malloc(sizeof(BstC));

    if(tree == NULL) {
        printf("Error: Could not allocate memory for head\n");
        return NULL;
    }
    tree->root = NULL;
    tree->size = 0;
    return tree;
}

void BstC_insert(BstC *tree, signed int elem) {
    BstCNode *y = NULL;
    BstCNode *x = tree->root;

//Creating a new node for insertion
    BstCNode *newNode = malloc(sizeof(BstCNode));
    if(newNode == NULL) {
        fprintf(stderr, "Error: Unable to initialize new node\n");
        return;
    }
    newNode->data = elem;
    newNode->left_child = NULL;
    newNode->right_child = NULL;
//new node operations end here

    while (x != NULL) {
        y = x;
        if(newNode->data < x->data) {
            x = x->left_child;
        }
        else {
            x = x->right_child;
        }
    }
    newNode->parent = y;

    if(y == NULL) {
        tree->root = newNode; //tree was empty 
    }
    else if(newNode->data < y->data) {
        y->left_child = newNode;
    }
    else {
        y->right_child = newNode;
    }

    tree->size++;
    return;
}

static void BstCNode_print_inOrder_helper(BstCNode*);

void BstC_print_inOrder(BstC *tree)
{
    BstCNode_print_inOrder_helper(tree->root);
    printf("\n");
}

static void BstCNode_print_inOrder_helper(BstCNode *node) {
    if(node == NULL) {
        return;
    }
    BstCNode_print_inOrder_helper(node->left_child);
    printf("%d ", node->data);
    BstCNode_print_inOrder_helper(node->right_child);
}

static size_t max_two_values (size_t x, size_t y) {
    if(x > y) {
        return x;
    }
    else return y;
}

static void BstCNode_delete_helper(BstCNode *node) {
    if(node == NULL) {
        return;
    }

    BstCNode_delete_helper(node->left_child);
    BstCNode_delete_helper(node->right_child);
    free(node);
    node = NULL;
}

void BstC_delete(BstC **tree) {
    if(tree == NULL || (*tree) == NULL) {
        return;
    }
    BstCNode_delete_helper((*tree)->root);

    free(*tree);
    (*tree) = NULL;
    tree = NULL;
}

static size_t BstCNode_height_helper(BstCNode*);

size_t BstC_height(BstC *tree) {
    return BstCNode_height_helper(tree->root);
}


static size_t BstCNode_height_helper(BstCNode *node)
{
    if(node == NULL) {
        return 0;
    }
    size_t left_tree_height = BstCNode_height_helper(node->left_child);
    size_t right_tree_height = BstCNode_height_helper(node->right_child);

    #ifdef DEBUG
        printf("left height: %zu\n", left_tree_height);
        printf("right height: %zu\n", right_tree_height);
    #endif
    
    return max_two_values(left_tree_height, right_tree_height) + 1;
}

signed int BstC_min(BstC *tree) {
    BstCNode *node = tree->root;
    while(node->left_child != NULL) {
        node = node->left_child;
    }
    return node->data;
}
signed int BstC_max(BstC *tree) {
    BstCNode *node = tree->root;
    while(node->right_child != NULL) {
        node = node->right_child;
    }
    return node->data;
}

// static void BstC_transplant(BstC *tree, BstCNode*, BstCNode*);


// //Helper function: Replaces one subtree as a child of its parent with 
// //another subtree
// static void BstC_transplant(BstC *tree, BstCNode *u, BstCNode *v) {
//     if(u->parent == NULL) {
//         tree->root = v;
//     }
//     else if(u == u->parent->left_child) {
//         u->parent->left_child = v;
//     }
//     else {
//         u->parent->right_child = v;
//     }
//     if(v != NULL) {
//         v->parent = u->parent;
//     }
// }


static BstCNode *BstC_search_helper(BstCNode *node, signed int key);

BstCNode *BstC_search(BstC *tree, signed int key) {
    return BstC_search_helper(tree->root, key);
}

static BstCNode *BstC_search_helper(BstCNode *node, signed int key) {
    if(node == NULL || key == node->data) {
        return node;
    }
    if(key < node->data) {
        return BstC_search_helper(node->left_child, key);
    }
    else {
        return BstC_search_helper(node->right_child, key);
    }
}

// void BstCNode_remove(BstC *tree, signed int key) {
//     BstCNode *node_to_delete = BstC_search(tree, key);

//     if(node_to_delete->left_child == NULL) {
//         BstC_transplant(tree, node_to_delete, node_to_delete->right_child);
//     }
//     else if (node_to_delete->right_child == NULL) {
//         BstC_transplant(tree, node_to_delete, node_to_delete->left_child);
//     }
//     else {
//         BstCNode *y =
//     }
// }