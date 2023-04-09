/**
 * @file DynamicArrayTest.c
 * @author Kevin Pluas (kpluas21@gmail.com)
 * @brief Unit testing for DynamicArray.h
 * @version 0.1
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

#include"../src/DynamicArray.h"
#include"unity.h"

double generate_double_inRange(double min, double max);
float generate_rand_float(float max);

void DynamicArrayTest_print_all_debug(DynamicArray **arrayOfVectors);
void DynamicArrayTest_empty_all(DynamicArray **arrayOfVectors);

void setUp(void);
void tearDown(void);

void test_DynamicArray_init(void);
void test_DynamicArray_delete(void);
void test_DynamicArray_get(void);
void test_DynamicArray_insert(void);
void test_DynamicArray_find(void);
void test_DynamicArray_empty(void);
void test_DynamicArray_print(void);

//setUp() will initilize these objs before every test
static DynamicArray *intVector;
static DynamicArray *charVector;
static DynamicArray *floatVector;
static DynamicArray *doubleVector;
//tearDown() _delete's them after every test.

/**
 * @brief Our main test function.
 */
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_DynamicArray_init);
    RUN_TEST(test_DynamicArray_print);
    RUN_TEST(test_DynamicArray_delete);
    RUN_TEST(test_DynamicArray_get);
    RUN_TEST(test_DynamicArray_find);
    RUN_TEST(test_DynamicArray_empty);
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

void DynamicArrayTest_print_all_debug(DynamicArray **arrayOfVectors) {
    for (size_t i = 0; i < 4; i++) {
        DynamicArray_debug_info(arrayOfVectors[i]);
    }
    
}

void DynamicArrayTest_empty_all(DynamicArray **arrayOfVectors) {
    for (size_t i = 0; i < 4; i++) {
        DynamicArray_empty(arrayOfVectors[i]);
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
    

    intVector = DynamicArray_init(INT, intArray, 5);
    charVector = DynamicArray_init(CHAR, charArray, 5);
    floatVector = DynamicArray_init(FLOAT, floatArray, 5);
    doubleVector = DynamicArray_init(DOUBLE, doubleArray, 5);

}

void tearDown(void) {
    DynamicArray_delete(&intVector);
    DynamicArray_delete(&charVector);
    DynamicArray_delete(&floatVector);
    DynamicArray_delete(&doubleVector);
}

/**
 * @brief Testing the initialization of vectors for all the datatypes.
 * Checks for the correct size and capacity
 * 
 */
void test_DynamicArray_init(void) {
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
void test_DynamicArray_delete(void) {
    DynamicArray_delete(&intVector);
    DynamicArray_delete(&charVector);
    DynamicArray_delete(&floatVector);
    DynamicArray_delete(&doubleVector);

    TEST_ASSERT_NULL(intVector);
    TEST_ASSERT_NULL(charVector);
    TEST_ASSERT_NULL(floatVector);
    TEST_ASSERT_NULL(doubleVector);
}

void test_DynamicArray_get(void) {
    float f = 3.14;
    double d = 5.3892;
    DynamicArray_insert(floatVector, &f, 4);
    DynamicArray_insert(doubleVector, &d, 4);

    TEST_ASSERT_EQUAL(3, *(int*)DynamicArray_get(intVector, 2));
    TEST_ASSERT_EQUAL('c', *(char*)DynamicArray_get(charVector, 2));
    TEST_ASSERT_EQUAL(3.14, *(float*)DynamicArray_get(floatVector, 4));
    TEST_ASSERT_EQUAL(5.3892, *(double*)DynamicArray_get(doubleVector, 4));

    //Incorrect input
    TEST_ASSERT_NULL(DynamicArray_get(intVector, -1));
    TEST_ASSERT_NULL(DynamicArray_get(intVector, intVector->size));

    //Testing false positives
    TEST_ASSERT_NOT_EQUAL('b', *(char*)DynamicArray_get(charVector, 0));

}



void test_DynamicArray_insert(void) {

}

void test_DynamicArray_find(void) {
    for (size_t i = 1; i < 6; i++) {
        TEST_ASSERT_EQUAL_INT(i - 1, DynamicArray_find(intVector, &i));
    }

    for (size_t i = 'a'; i < 'f'; i++) {
        TEST_ASSERT_EQUAL(i - 'a', DynamicArray_find(charVector, &i));
    }
    
    //Testing value not found
    int i = 32;
    TEST_ASSERT_EQUAL(-1, DynamicArray_find(intVector, &i));
    
    char c = 't';
    TEST_ASSERT_EQUAL_INT(-1, DynamicArray_find(charVector, &c));
}

void test_DynamicArray_empty(void) {
    DynamicArray_empty(intVector);
    DynamicArray_empty(charVector);
    DynamicArray_empty(floatVector);
    DynamicArray_empty(doubleVector);

    TEST_ASSERT_EQUAL_INT(0 , DynamicArray_isEmpty(intVector));
    TEST_ASSERT_EQUAL_INT(0 , DynamicArray_isEmpty(charVector));
    TEST_ASSERT_EQUAL_INT(0 , DynamicArray_isEmpty(floatVector));
    TEST_ASSERT_EQUAL_INT(0 , DynamicArray_isEmpty(doubleVector));

    //Testing for NULL on an empty array 
    TEST_ASSERT_NULL((int*)DynamicArray_get(intVector, 2));
    TEST_ASSERT_NULL((char*)DynamicArray_get(charVector, 2));
    TEST_ASSERT_NULL((float*)DynamicArray_get(floatVector, 2));
    TEST_ASSERT_NULL((double*)DynamicArray_get(doubleVector, 2));
}

void test_DynamicArray_print(void) {
    DynamicArray_print(intVector);
    DynamicArray_print(charVector);
    DynamicArray_print(floatVector);
    DynamicArray_print(doubleVector);
}
