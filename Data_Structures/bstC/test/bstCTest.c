/**
 * @file bstCTest.c
 * @author Kevin Pluas (kpluas21@gmail.com)
 * @brief Unit testing for BstC.h
 * @version 0.1
 * @date 2023-04-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<time.h>

#include"../src/bstC.h"
#include"../../lib/unity.h"
#include"../../lib/helper_functions.h"

static BstC *intTree;

void setUp(void);
void tearDown(void);

void test_BstCNode_insert(void);
void test_BstCNode_init(void);
void test_BstCNode_minmax(void);
void test_BstCNode_height(void);

int main(void) {
    srand(time(NULL));

    UNITY_BEGIN();
    RUN_TEST(test_BstCNode_init);
    RUN_TEST(test_BstCNode_insert);
    RUN_TEST(test_BstCNode_minmax);
    RUN_TEST(test_BstCNode_height);
    return UNITY_END();
}

void setUp(void) {
    intTree = BstCNode_init();
}

void tearDown(void) {   
    BstCNode_delete(&intTree);
}

void test_BstCNode_insert(void) {
    int *vector = generate_unique_ints();
    for(int i = 0; i < 100; i++) {
        BstCNode_insert(intTree, *(vector+i));
    }
    TEST_ASSERT_EQUAL(100, intTree->size);
    free(vector);
}

void test_BstCNode_init(void) {
    TEST_ASSERT_NOT_NULL(intTree);
}

void test_BstCNode_minmax(void) {
    int *vector = generate_unique_ints();
    for(int i = 0; i < 100; i++) {
        BstCNode_insert(intTree, *(vector+i));
    }

    BstCNode_print_inOrder(intTree);

    printf("The minimum value is: %d\n", BstCNode_min(intTree));
    printf("The maximum value is: %d\n", BstCNode_max(intTree));

    free(vector);
}

void test_BstCNode_height(void) {
    int *vector = generate_unique_ints();
    for(int i = 0; i < 100; i++) {
        BstCNode_insert(intTree, *(vector+i));
    }

    printf("Height of the tree: %zu\n", BstCNode_height(intTree));
    free(vector);
}
