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

#include"../src/DynamiC.h"
#include"../../lib/unity.h"

double generate_double_inRange(double min, double max);
float generate_rand_float(float max);

void DynamiCTest_print_all_debug(DynamiC **arrayOfVectors);
void DynamiCTest_empty_all(DynamiC **arrayOfVectors);

void setUp(void);
void tearDown(void);

void test_DynamiC_init(void);
void test_DynamiC_delete(void);
void test_DynamiC_get(void);
void test_DynamiC_insert(void);
void test_DynamiC_find(void);
void test_DynamiC_empty(void);
void test_DynamiC_print(void);
void test_DynamiC_swap(void);
void test_DynamiC_cmp(void);
void test_DynamiC_sort(void);

//setUp() will initilize these objs before every test
static DynamiC *intVector;
static DynamiC *charVector;
static DynamiC *floatVector;
static DynamiC *doubleVector;
//tearDown() _delete's them after every test.

/**
 * @brief Our main test function.
 */
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_DynamiC_init);
    RUN_TEST(test_DynamiC_print);
    RUN_TEST(test_DynamiC_delete);
    RUN_TEST(test_DynamiC_get);
    RUN_TEST(test_DynamiC_find);
    RUN_TEST(test_DynamiC_empty);
    RUN_TEST(test_DynamiC_swap);
    RUN_TEST(test_DynamiC_sort);
    return UNITY_END();
}

float generate_rand_float(float max) {
    return ((float)rand()/(float)(RAND_MAX)) * max;
}

double generate_double_inRange(double min, double max) {
    double range = max - min;
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

void DynamiCTest_print_all_debug(DynamiC **arrayOfVectors) {
    for (size_t i = 0; i < 4; i++) {
        DynamiC_debug_info(arrayOfVectors[i]);
    }
    
}

void DynamiCTest_empty_all(DynamiC **arrayOfVectors) {
    for (size_t i = 0; i < 4; i++) {
        DynamiC_empty(arrayOfVectors[i]);
    }
    
}

void setUp(void) {
    srand((unsigned int)time(NULL));

    int intArray[5] = {1,2,3,4,5};
    char charArray[5] = {'a', 'b', 'c', 'd', 'e'};
    float floatArray[5];
    double doubleArray[5];

    for (size_t i = 0; i < 5; i++)
    {
        floatArray[i] = generate_rand_float(3.14);
        doubleArray[i] = generate_double_inRange(0.00, 1.00);
    }
    

    intVector = DynamiC_init(INT, intArray, 5);
    charVector = DynamiC_init(CHAR, charArray, 5);
    floatVector = DynamiC_init(FLOAT, floatArray, 5);
    doubleVector = DynamiC_init(DOUBLE, doubleArray, 5);

}

void tearDown(void) {
    DynamiC_delete(&intVector);
    DynamiC_delete(&charVector);
    DynamiC_delete(&floatVector);
    DynamiC_delete(&doubleVector);
}

/**
 * @brief Testing the initialization of vectors for all the datatypes.
 * Checks for the correct size and capacity
 * 
 */
void test_DynamiC_init(void) {
    TEST_ASSERT_EQUAL_INT(5, intVector->size);
    TEST_ASSERT_EQUAL_INT(5, charVector->size);
    TEST_ASSERT_EQUAL_INT(5, floatVector->size);
    TEST_ASSERT_EQUAL_INT(5, doubleVector->size);

    TEST_ASSERT_EQUAL_INT(10, intVector->capacity);
    TEST_ASSERT_EQUAL_INT(10, charVector->capacity);
    TEST_ASSERT_EQUAL_INT(10, floatVector->capacity);
    TEST_ASSERT_EQUAL_INT(10, doubleVector->capacity);
}

/**
 * @brief Testing the delete functions. On both initialized and uninitialized 
 * vectors.
 * Also tests double deletes
 */
void test_DynamiC_delete(void) {
    DynamiC_delete(&intVector);
    DynamiC_delete(&charVector);
    DynamiC_delete(&floatVector);
    DynamiC_delete(&doubleVector);

    TEST_ASSERT_NULL(intVector);
    TEST_ASSERT_NULL(charVector);
    TEST_ASSERT_NULL(floatVector);
    TEST_ASSERT_NULL(doubleVector);
}

void test_DynamiC_get(void) {
    float f = 3.14;
    double d = 5.3892;
    DynamiC_insert(floatVector, &f, 4);
    DynamiC_insert(doubleVector, &d, 4);

    TEST_ASSERT_EQUAL(3, *(int*)DynamiC_get(intVector, 2));
    TEST_ASSERT_EQUAL('c', *(char*)DynamiC_get(charVector, 2));
    TEST_ASSERT_EQUAL(3.14, *(float*)DynamiC_get(floatVector, 4));
    TEST_ASSERT_EQUAL(5.3892, *(double*)DynamiC_get(doubleVector, 4));

    //Incorrect input
    TEST_ASSERT_NULL(DynamiC_get(intVector, -1));
    TEST_ASSERT_NULL(DynamiC_get(intVector, intVector->size));

    //Testing false positives
    TEST_ASSERT_NOT_EQUAL('b', *(char*)DynamiC_get(charVector, 0));

}



void test_DynamiC_insert(void) {

}

void test_DynamiC_find(void) {
    for (size_t i = 1; i < 6; i++) {
        TEST_ASSERT_EQUAL_INT(i - 1, DynamiC_find(intVector, &i));
    }

    for (size_t i = 'a'; i < 'f'; i++) {
        TEST_ASSERT_EQUAL(i - 'a', DynamiC_find(charVector, &i));
    }
    
    //Testing value not found
    int i = 32;
    TEST_ASSERT_EQUAL(-1, DynamiC_find(intVector, &i));
    
    char c = 't';
    TEST_ASSERT_EQUAL_INT(-1, DynamiC_find(charVector, &c));
}

void test_DynamiC_empty(void) {
    DynamiC_empty(intVector);
    DynamiC_empty(charVector);
    DynamiC_empty(floatVector);
    DynamiC_empty(doubleVector);

    TEST_ASSERT_EQUAL_INT(0 , DynamiC_isEmpty(intVector));
    TEST_ASSERT_EQUAL_INT(0 , DynamiC_isEmpty(charVector));
    TEST_ASSERT_EQUAL_INT(0 , DynamiC_isEmpty(floatVector));
    TEST_ASSERT_EQUAL_INT(0 , DynamiC_isEmpty(doubleVector));

    //Testing for NULL on an empty array 
    TEST_ASSERT_NULL((int*)DynamiC_get(intVector, 2));
    TEST_ASSERT_NULL((char*)DynamiC_get(charVector, 2));
    TEST_ASSERT_NULL((float*)DynamiC_get(floatVector, 2));
    TEST_ASSERT_NULL((double*)DynamiC_get(doubleVector, 2));
}

void test_DynamiC_print(void) {
    DynamiC_print(intVector);
    DynamiC_print(charVector);
    DynamiC_print(floatVector);
    DynamiC_print(doubleVector);
}

void test_DynamiC_swap(void) {
    DynamiC_swap(INT, DynamiC_get(intVector, 1), DynamiC_get(intVector,2));
    DynamiC_print(intVector);
}

void test_DynamiC_cmp(void) {
    
}

void test_DynamiC_sort(void) {
    int randInt;
    double randDouble;
    //First, we empty the arrays and fill them with random numbers.
    DynamiC_empty(intVector);
    DynamiC_empty(doubleVector);
    for (int i = 0; i < 1001; i++)
    {
        randDouble = generate_double_inRange(0.0, 1.0);
        randInt = rand() % 1000;
        DynamiC_append(intVector, &randInt);
        DynamiC_append(doubleVector, &randDouble);
    }
    puts("Before _sort: \n");
    DynamiC_print(intVector);
    DynamiC_print(doubleVector);

    DynamiC_sort(intVector);
    DynamiC_sort(doubleVector);
    
    puts("After _sort: \n");
    DynamiC_print(intVector);
    DynamiC_print(doubleVector);
    
}
