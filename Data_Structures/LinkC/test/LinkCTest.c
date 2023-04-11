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
void test_LinkC_delete(void);

void setUp(void);
void tearDown(void);

/**
 * @brief Static globals for our tests
 * 
 */
static LinkC *intList;
static LinkC *charList;
static LinkC *floatList;
static LinkC *doubleList;
static LinkC *stringList;


int main(void) {
    RUN_TEST(test_LinkC_init);
    RUN_TEST(test_LinkC_delete);

    return 0;
}

void setUp(void) {
    int i = 5;
    char a = 'a';
    float f = 3.14;
    double d = 0.073902;
    const char* s = "Kevin Pluas";

    intList = LinkC_init(INT, &i);
    charList = LinkC_init(CHAR, &a);
    floatList = LinkC_init(FLOAT, &f);
    doubleList = LinkC_init(DOUBLE, &d);
    stringList = LinkC_init(STRING, &s);
}

void test_LinkC_init(void) {
    TEST_ASSERT_NOT_NULL(intList);
    TEST_ASSERT_NOT_NULL(charList);
    TEST_ASSERT_NOT_NULL(floatList);
    TEST_ASSERT_NOT_NULL(doubleList);
    TEST_ASSERT_NOT_NULL(stringList);
}


void test_LinkC_delete(void) {
    LinkC_delete(&intList);
    LinkC_delete(&charList);
    LinkC_delete(&floatList);
    LinkC_delete(&doubleList);
    LinkC_delete(&stringList);

    TEST_ASSERT_NULL(intList);
    TEST_ASSERT_NULL(charList);
    TEST_ASSERT_NULL(floatList);
    TEST_ASSERT_NULL(doubleList);
    TEST_ASSERT_NULL(stringList);
}

void tearDown(void) {
    LinkC_delete(&intList);
    LinkC_delete(&charList);
    LinkC_delete(&floatList);
    LinkC_delete(&doubleList);
    LinkC_delete(&stringList);
}