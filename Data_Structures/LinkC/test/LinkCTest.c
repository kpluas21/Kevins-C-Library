/**
 * @file LinkCTest.c
 * @author Kevin Pluas (kpluas21@gmail.com)
 * @brief Unit testing for LinkC.h
 * @version 0.1
 * @date 2023-04-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#include<stdio.h>
#include<stdlib.h>

#include"../src/LinkC.h"

#include"../../lib/unity.h"


void test_LinkC_init(void);

void test_LinkC_get(void);

void test_LinkC_insert_at_end(void);
void test_LinkC_insert_at_index(void);

void test_LinkC_find(void);

void test_LinkC_remove(void);

//Automatically sets up a single linked list containing a single node with an int.
void setUp(void);
void tearDown(void);

/**
 * @brief Static globals for our tests
 * 
 */
static LinkC *intList;

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_LinkC_init);
    RUN_TEST(test_LinkC_get);
    RUN_TEST(test_LinkC_insert_at_end);
    RUN_TEST(test_LinkC_find);
    RUN_TEST(test_LinkC_remove);
    return UNITY_END();
}

void test_LinkC_init(void) {
    TEST_ASSERT_NOT_NULL(intList);
}

void test_LinkC_get(void) {
    //Correct inputs
    TEST_ASSERT_EQUAL_INT(0, *(int*)LinkC_get(intList, 0));

    //Incorrect inputs
    TEST_ASSERT_NULL(LinkC_get(intList, 5));
}

void test_LinkC_insert_at_end(void) {
    for (int i = 2; i < 101; i++) {
        LinkC_insert_at_end(intList, &i);
    }
    
    TEST_ASSERT_EQUAL_size_t(100, LinkC_size(intList));
}

void test_LinkC_find(void) {
    for (int i = 2; i < 101; i++) {
        LinkC_insert_at_end(intList, &i);
    }
    
    //Correct input
    int i = 35;
    TEST_ASSERT_EQUAL_INT(34, LinkC_find(intList, &i));

    i = 200;
    //Incorrect
    TEST_ASSERT_EQUAL_INT(-1, LinkC_find(intList, &i));
}

void test_LinkC_remove(void) {
    for (int i = 1; i < 100; i++)
    {
        LinkC_insert_at_end(intList, &i);
    }
    TEST_ASSERT_EQUAL_size_t(100, LinkC_size(intList));
    //Testing head removal
    LinkC_remove_at_middle(intList, 0);

    //Testing middle removal
    LinkC_remove_at_middle(intList, LinkC_size(intList)/2);

    //Testing tail removal
    LinkC_remove_at_middle(intList, LinkC_size(intList) - 1);

    TEST_ASSERT_EQUAL_size_t(97, LinkC_size(intList));
    
}

void test_LinkC_insert_at_index(void) {
    
}

void setUp(void) {
    int i = 0;

    intList = LinkC_init(sizeof(int), &i);

}

void tearDown(void) {
    LinkC_delete(&intList);
}


