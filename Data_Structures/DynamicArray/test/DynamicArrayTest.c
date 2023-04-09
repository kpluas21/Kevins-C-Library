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

/**
 * @brief Our main test function.

 */
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_DynamicArray_init);
    RUN_TEST(test_DynamicArray_delete);
    RUN_TEST(test_DynamicArray_get);
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

}

void tearDown(void) {

}

/**
 * @brief Testing the initialization of vectors for all the datatypes.
 * Checks for the correct size and capacity
 * 
 */
void test_DynamicArray_init(void) {


    int intArray[5] = {1,2,3,4,5};
    char charArray[5] = {'a', 'b', 'c', 'd', 'e'};
    float floatArray[5];
    double doubleArray[5];

    for (size_t i = 0; i < 5; i++)
    {
        floatArray[i] = generate_rand_float(3.14);
        doubleArray[i] = generate_double_inRange(0.00, 1.00);
    }
    

    DynamicArray *intVector = DynamicArray_init(INT, intArray, 5);
    DynamicArray *charVector = DynamicArray_init(CHAR, charArray, 5);
    DynamicArray *floatVector = DynamicArray_init(FLOAT, floatArray, 5);
    DynamicArray *doubleVector = DynamicArray_init(DOUBLE, doubleArray, 5);

    TEST_ASSERT_EQUAL_INT(5, intVector->size);
    TEST_ASSERT_EQUAL_INT(5, charVector->size);
    TEST_ASSERT_EQUAL_INT(5, floatVector->size);
    TEST_ASSERT_EQUAL_INT(5, doubleVector->size);

    TEST_ASSERT_EQUAL_INT(10, intVector->capacity);
    TEST_ASSERT_EQUAL_INT(10, charVector->capacity);
    TEST_ASSERT_EQUAL_INT(10, floatVector->capacity);
    TEST_ASSERT_EQUAL_INT(10, doubleVector->capacity);

    DynamicArray_delete(&intVector);
    DynamicArray_delete(&charVector);
    DynamicArray_delete(&floatVector);
    DynamicArray_delete(&doubleVector);
}

/**
 * @brief Testing the delete functions. On both initialized and uninitialized 
 * vectors.
 * Also tests double deletes
 */
void test_DynamicArray_delete(void) {
    int intArray[5] = {1,2,3,4,5};
    char charArray[5] = {'a', 'b', 'c', 'd', 'e'};
    float floatArray[5];
    double doubleArray[5];

    for (size_t i = 0; i < 5; i++)
    {
        floatArray[i] = generate_rand_float(3.14);
        doubleArray[i] = generate_double_inRange(0.00, 1.00);
    }
    

    DynamicArray *intVector = DynamicArray_init(INT, intArray, 5);
    DynamicArray *charVector = DynamicArray_init(CHAR, charArray, 5);
    DynamicArray *floatVector = DynamicArray_init(FLOAT, floatArray, 5);
    DynamicArray *doubleVector = DynamicArray_init(DOUBLE, doubleArray, 5);

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
    int intArray[5] = {1,2,3,4,5};
    char charArray[5] = {'a', 'b', 'c', 'd', 'e'};
    // float floatArray[5];
    // double doubleArray[5];

    // for (size_t i = 0; i < 5; i++)
    // {
    //     floatArray[i] = generate_rand_float(3.14);
    //     doubleArray[i] = generate_double_inRange(0.00, 1.00);
    // }
    

    DynamicArray *intVector = DynamicArray_init(INT, intArray, 5);
    DynamicArray *charVector = DynamicArray_init(CHAR, charArray, 5);
    // DynamicArray *floatVector = DynamicArray_init(FLOAT, floatArray, 5);
    // DynamicArray *doubleVector = DynamicArray_init(DOUBLE, doubleArray, 5);

    TEST_ASSERT_EQUAL(3, *(int*)DynamicArray_get(intVector, 2));
    TEST_ASSERT_EQUAL('c', *(char*)DynamicArray_get(charVector, 2));


}

void test_DynamicArray_insert(void)
{
}
