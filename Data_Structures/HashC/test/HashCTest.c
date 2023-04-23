/**
 * @file HashCTest.c
 * @author Kevin Pluas (kpluas21@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"../../lib/unity.h"

#include"../src/HashC.h"

#include"../../lib/helper_functions.h"

static HashC_table *table;

void setUp(void);
void tearDown(void);

void test_HashC_init(void);
void test_HashC_insert(void);
void test_HashC_search(void);
void test_HashC_delete(void);

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_HashC_init);
    RUN_TEST(test_HashC_insert);
    RUN_TEST(test_HashC_search);
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
    
    char **nameArray = get_array_of_strings();
    if(nameArray == NULL) {
        printf("Error: Could not get array of names for testing\n");
        TEST_FAIL();
    }

    for (int i = 0; i < 100; i++)
    {
        // printf("%s", nameArray[i]);
        HashC_insert(table, nameArray[i], i);
    }
    
    TEST_ASSERT_EQUAL_INT(100, HashC_table_size(table));
    free_array_of_strings(nameArray, 100);

}

void test_HashC_search(void) {
    HashC_insert(table, "K", 13);
    HashC_insert(table, "Z", 1000);
    HashC_insert(table, "Kevin Pluas", 27);

    //This should spout an error. Only unique keys are allowed
    HashC_insert(table, "Kevin Pluas", 27);
    //

    HashC_insert(table, "Valerie Ramirez", 54);
    HashC_insert(table, "Teresa Pluas", 41);

    TEST_ASSERT_EQUAL_INT(27, HashC_search(table, "Kevin Pluas"));
    TEST_ASSERT_EQUAL_INT(54, HashC_search(table, "Valerie Ramirez"));
    TEST_ASSERT_EQUAL_INT(41, HashC_search(table, "Teresa Pluas"));
    TEST_ASSERT_EQUAL_INT(13, HashC_search(table, "K"));
    TEST_ASSERT_EQUAL_INT(1000, HashC_search(table, "Z"));
}

void test_HashC_delete(void) {
    HashC_delete(&table);
    TEST_ASSERT_NULL(table);
}
