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

static BstCNode *intTree;

void setUp(void);
void tearDown(void);

void test_BstCNode_insert(void);
void test_BstCNode_init(void);
void test_BstCNode_minmax(void);

int main(void) {
    srand(time(NULL));

    UNITY_BEGIN();
    RUN_TEST(test_BstCNode_insert);
    return UNITY_END();
}

void setUp(void) {
    intTree = BstCNode_init(50);

}

void tearDown(void) {   
    BstCNode_delete(&intTree);
}

void test_BstCNode_insert(void) {
    signed int randomInt;
    for (size_t i = 0; i < 1001; i++)
    {
        randomInt = rand() % 1001;
        BstCNode_insert(intTree, randomInt);
    }
    
}

void test_BstCNode_init(void) {
    TEST_ASSERT_NOT_NULL(intTree);
}

void test_BstCNode_minmax(void) {

}
