/**
 * @file DynamiCTest.c
 * @author Kevin Pluas (kpluas21@gmail.com)
 * @brief Unit testing for DynamiC.h
 * @version 0.0.3
 * @date 2023-04-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include<stdio.h>
#include<assert.h>
#include<time.h>
#include<stdlib.h>
#include<time.h>
#include<float.h>

#include"../src/DynamiC.h"
#include"../../lib/unity.h"

void setUp(void);
void tearDown(void);

void test_DynamiC_append_1000(void);
void test_DynamiC_append_100000(void);

void test_DynamiC_stats(void);
void test_DynamiC_get(void);


static DynamiC *intArray;
static DynamiC *charArray;
static DynamiC *floatArray;


int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_DynamiC_stats);
    RUN_TEST(test_DynamiC_append_1000);
    RUN_TEST(test_DynamiC_append_100000);
    RUN_TEST(test_DynamiC_get);

    return UNITY_END();
}

void setUp(void) {
    int arr[0];
    char chArr[0];
    float fltArr[0];

    intArray = DynamiC_init(arr, sizeof(int), 0);
    charArray = DynamiC_init(chArr, sizeof(char), 0);
    floatArray = DynamiC_init(fltArr, sizeof(float), 0);
}

void tearDown(void) {
    DynamiC_delete(&intArray);
    DynamiC_delete(&charArray);
    DynamiC_delete(&floatArray);
}

void test_DynamiC_append_1000(void) {
    for (size_t i = 0; i < 1000; i++) {
        DynamiC_append(intArray, &i);
        DynamiC_append(charArray, &i);
        DynamiC_append(floatArray, &i);
    }
    TEST_ASSERT_EQUAL(1000, DynamiC_size(intArray));
    TEST_ASSERT_EQUAL(1000, DynamiC_size(charArray));
    TEST_ASSERT_EQUAL(1000, DynamiC_size(floatArray));
}

void test_DynamiC_append_100000(void) {
    for (size_t i = 0; i < 100000; i++) {
        DynamiC_append(intArray, &i);
        DynamiC_append(charArray, &i);
        DynamiC_append(floatArray, &i);
        
    }
    TEST_ASSERT_EQUAL(100000, DynamiC_size(intArray));
    TEST_ASSERT_EQUAL(100000, DynamiC_size(charArray));
    TEST_ASSERT_EQUAL(100000, DynamiC_size(floatArray));
}

void test_DynamiC_stats(void) {
    printf("DynamiC stats\n");
    printf("intArray : \n");
    printf("Size of each elem: %zu\n", intArray->data_size);
    printf("Bytes allocated: %zu\n", intArray->alloc_data);
    printf("Capacity: %zu\n\n", intArray->capacity);
    printf("charArray : \n");
    printf("Size of each elem: %zu\n", charArray->data_size);
    printf("Bytes allocated: %zu\n", charArray->alloc_data);
    printf("Capacity: %zu\n\n", charArray->capacity);
    printf("floatArray : \n");
    printf("Size of each elem: %zu\n", floatArray->data_size);
    printf("Bytes allocated: %zu\n", floatArray->alloc_data);
    printf("Capacity: %zu\n", floatArray->capacity);
}

void test_DynamiC_get(void) {
    for (size_t i = 0; i < 3; i++) {
        DynamiC_append(intArray, &i);
        DynamiC_append(charArray, &i);
    }

    for (float i = 0.50; i < 3.00; i += 0.50) {
        DynamiC_append(floatArray, &i);
    }
    

    TEST_ASSERT_EQUAL(0, *(int*)DynamiC_get(intArray, 0));
    TEST_ASSERT_EQUAL(1, *(int*)DynamiC_get(intArray, 1));
    TEST_ASSERT_EQUAL(2, *(int*)DynamiC_get(intArray, DynamiC_size(intArray) - 1));

    TEST_ASSERT_EQUAL(0, *(char*)DynamiC_get(charArray, 0));
    TEST_ASSERT_EQUAL(1, *(char*)DynamiC_get(charArray, 1));
    TEST_ASSERT_EQUAL(2, *(char*)DynamiC_get(charArray, DynamiC_size(charArray) - 1));

    TEST_ASSERT_EQUAL_FLOAT(0.50, *(float*)DynamiC_get(floatArray, 0));
    TEST_ASSERT_EQUAL_FLOAT(1, *(float*)DynamiC_get(floatArray, 1));
    TEST_ASSERT_EQUAL_FLOAT(2.5, *(float*)DynamiC_get(floatArray, DynamiC_size(floatArray) - 1));
}