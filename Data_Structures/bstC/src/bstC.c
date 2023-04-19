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
#include "bstC.h"


BstCNode *BstCNode_init(signed int elem) {
    BstCNode *head = malloc(sizeof(BstCNode));
    if(head == NULL) {
        printf("Error: Could not allocate memory for head\n");
        return NULL;
    }

    head->data = elem;
    head->parent = NULL;
    head->left_child = NULL;
    head->right_child = NULL;

    return head;
}

void BstCNode_insert(BstCNode *root, signed int elem) {
    BstCNode *y = NULL;
    BstCNode *x = root;
    BstCNode *newNode = malloc(sizeof(BstCNode));
    if(newNode == NULL) {
        fprintf(stderr, "Error: Unable to initialize new node\n");
        return;
    }
    newNode->data = elem;

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
        root = newNode;
    }
    else if(newNode->data < y->data) {
        y->left_child = newNode;
    }
    else {
        y->right_child = newNode;
    }

    return;
}

void BstCNode_print_inOrder(BstCNode *node) {
    if(node != NULL) {
        BstCNode_print_inOrder(node->left_child);
        printf("%d ", node->data);
        BstCNode_print_inOrder(node->right_child);
    }
}

static size_t max_two_values (size_t x, size_t y) {
    if(x > y) {
        return x;
    }
    else return y;
}

void BstCNode_delete(BstCNode **root) {
    if(root == NULL || *root == NULL) {
        return; //Prevents double frees
    }

    BstCNode_delete(&(*root)->left_child);
    BstCNode_delete(&(*root)->right_child);
    free((*root));


}

size_t BstCNode_height(BstCNode *node)
{
    if(node == NULL) {
        return 0;
    }
    size_t left_tree_height = BstCNode_height(node->left_child);
    size_t right_tree_height = BstCNode_height(node->right_child);

    #ifdef DEBUG
        printf("left height: %zu\n", left_tree_height);
        printf("right height: %zu\n", right_tree_height);
    #endif
    
    return max_two_values(left_tree_height, right_tree_height) + 1;
}

signed int BstCNode_min(BstCNode *root) {
    if(root != NULL) {
        return BstCNode_min(root->left_child);
    }
    return root->parent->data;
}
