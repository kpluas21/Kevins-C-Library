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

void test_DynamiC_insert_1(void);
void test_DynamiC_insert_1000(void);

void test_DynamiC_remove(void);

void test_DynamiC_stats(void);
void test_DynamiC_get(void);

void test_DynamiC_delete(void);

void helper_print_all_int(DynamiC *array);

void helper_print_all_char(DynamiC *array);

static DynamiC **arrayOfArrays;

static DynamiC *intArray;
static DynamiC *charArray;
static DynamiC *floatArray;
static DynamiC *doubleArray;


int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_DynamiC_stats);
    RUN_TEST(test_DynamiC_insert_1);
    RUN_TEST(test_DynamiC_insert_1000);
    RUN_TEST(test_DynamiC_append_1000);
    RUN_TEST(test_DynamiC_append_100000);
    RUN_TEST(test_DynamiC_remove);
    RUN_TEST(test_DynamiC_get);
    RUN_TEST(test_DynamiC_delete);

    return UNITY_END();
}

void setUp(void) {
    int arr[0];
    char chArr[0];
    float fltArr[0];
    double dbArr[0];

    intArray = DynamiC_init(arr, sizeof(int), 0);
    charArray = DynamiC_init(chArr, sizeof(char), 0);
    floatArray = DynamiC_init(fltArr, sizeof(float), 0);
    doubleArray = DynamiC_init(dbArr, sizeof(double), 0);
}

void tearDown(void) {
    DynamiC_delete(&intArray);
    DynamiC_delete(&charArray);
    DynamiC_delete(&floatArray);
    DynamiC_delete(&doubleArray);
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

void test_DynamiC_insert_1(void) {
    int i = 5;
    char c = 'g';
    float f = 0.50;
    double d = 2.89797;

    DynamiC_insert(intArray, &i, 0);
    DynamiC_insert(charArray, &c, 0);
    DynamiC_insert(floatArray, &f, 0);
    DynamiC_insert(doubleArray, &d, 0);

    //Testing for failure
    TEST_ASSERT_EQUAL_INT(-1, DynamiC_insert(intArray, &i, 4));
    ///


    TEST_ASSERT_EQUAL_INT(5, *(int*)DynamiC_get(intArray, 0));
    TEST_ASSERT_EQUAL_INT('g', *(char*)DynamiC_get(charArray, 0));
    TEST_ASSERT_EQUAL_INT(0.50, *(float*)DynamiC_get(floatArray, 0));
    TEST_ASSERT_EQUAL_INT(2.89797, *(double*)DynamiC_get(doubleArray, 0));
}

void test_DynamiC_insert_1000(void) {
    for(int i = 0; i < 10; i++) {
        DynamiC_insert(intArray, &i, i);
    }

    int i = 0;
    for(char c = 'a'; c < 123; c++) {
        DynamiC_insert(charArray, &c, i);
        i++;
    }

    i = 0;
    for (float f = 0.00; f < 50.0; f += 0.50) {
        DynamiC_insert(floatArray, &f, i);
        i++;
    }

    TEST_ASSERT_EQUAL_INT(10, DynamiC_size(intArray));
    TEST_ASSERT_EQUAL_INT(26, DynamiC_size(charArray));
    TEST_ASSERT_EQUAL_INT(100, DynamiC_size(floatArray));
    


}

void test_DynamiC_remove(void) {
    for (size_t i = 0; i < 11; i++)
    {
        DynamiC_insert(intArray, &i, i);
    }
    helper_print_all_int(intArray);

    DynamiC_remove(intArray, 0);
    helper_print_all_int(intArray);
    DynamiC_remove(intArray, 5);
    helper_print_all_int(intArray);
    DynamiC_remove(intArray, DynamiC_size(intArray) - 1);
    helper_print_all_int(intArray);
}

void test_DynamiC_stats(void) {
    printf("DynamiC stats\n");

    arrayOfArrays = malloc(sizeof(DynamiC) * 3);
    arrayOfArrays[0] = intArray;
    arrayOfArrays[1] = charArray;
    arrayOfArrays[2] = floatArray;

    for (size_t i = 0; i < 3; i++)
    {
        printf("Array %zu:\n", i);
        printf("Size of each elem: %zu\n", arrayOfArrays[i]->data_size);
        printf("Bytes allocated: %zu\n", arrayOfArrays[i]->alloc_data);
        printf("Capacity: %zu\n", arrayOfArrays[i]->capacity);
    }

    free(arrayOfArrays);
    
}

void test_DynamiC_get(void) {
    //Three values for testing _get in the beginning, middle and end

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

void test_DynamiC_delete(void) {
    DynamiC_delete(&intArray);
    DynamiC_delete(&charArray);
    DynamiC_delete(&floatArray);
    DynamiC_delete(&doubleArray);

    TEST_ASSERT_NULL(intArray);
    TEST_ASSERT_NULL(charArray);
    TEST_ASSERT_NULL(floatArray);
    TEST_ASSERT_NULL(doubleArray);
}

void helper_print_all_int(DynamiC *array) {
    printf("[");
    for (size_t i = 0; i < DynamiC_size(array); i++)
    {
        printf("%d, ", *(int*)DynamiC_get(array, i));
    }
    printf("\b\b]\n");
}
void helper_print_all_char(DynamiC *array) {
    printf("[");
    for (size_t i = 0; i < DynamiC_size(array); i++)
    {
        printf("%c, ", *(char*)DynamiC_get(array, i));
    }
    printf("\b\b]\n");
}