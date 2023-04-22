/**
 * @file HashCTest.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include<stdio.h>
#include<stdlib.h>
#include"../src/HashC.h"

#include"../../lib/unity.h"

static HashC_table *table;

void setUp(void);
void tearDown(void);

void test_HashC_init(void);
void test_HashC_insert(void);
void test_HashC_delete(void);

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_HashC_init);
    RUN_TEST(test_HashC_insert);
    RUN_TEST(test_HashC_delete);
    return UNITY_END();
}

void setUp(void) {
    table = HashC_init();
}

void tearDown(void) {
    HashC_delete(&table);
}

void test_HashC_init(void) {
    TEST_ASSERT_NOT_NULL(table);
}

void test_HashC_insert(void) {
    HashC_insert(table, "Kevin Pluas", 27);

}

void test_HashC_delete(void) {
    HashC_delete(&table);
    TEST_ASSERT_NULL(table);
}
