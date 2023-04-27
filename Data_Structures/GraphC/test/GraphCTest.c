/**
 * @file GraphCTest.c
 * @author Kevin Pluas (kpluas21@gmail.com)
 * @brief Unit testing for GraphC.h
 * @version 0.1
 * @date 2023-04-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include"../src/GraphC.h"
#include"../../lib/unity.h"

static GraphC *graph;

void setUp(void);
void tearDown(void);

void test_GraphC_init(void);

void test_GraphC_add_vertex(void);

void test_GraphC_destroy(void);

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_GraphC_init);
    RUN_TEST(test_GraphC_add_vertex);
    RUN_TEST(test_GraphC_destroy);
    return UNITY_END();
}


void setUp(void) {
    graph = GraphC_init();
}

void tearDown(void) {
    GraphC_destroy(&graph);
}

void test_GraphC_init(void) {
    TEST_ASSERT_NOT_NULL(graph);
}

void test_GraphC_add_vertex(void) {
    TEST_ASSERT_NOT_NULL(GraphC_add_vertex(graph, 'a'));
    TEST_ASSERT_NOT_NULL(GraphC_add_vertex(graph, 'b'));

    TEST_ASSERT_NULL(GraphC_add_vertex(graph, 'b'));

}

void test_GraphC_destroy(void) {
    GraphC_destroy(&graph);
    TEST_ASSERT_NULL(graph);
}
