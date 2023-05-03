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
void test_GraphC_add_edge(void);

void test_GraphC_remove_vertex(void);

void test_GraphC_destroy(void);

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_GraphC_init);
    RUN_TEST(test_GraphC_add_vertex);
    RUN_TEST(test_GraphC_add_edge);
    printf("\n\n");
    RUN_TEST(test_GraphC_remove_vertex);
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
    TEST_ASSERT_EQUAL_INT(0, GraphC_add_vertex(graph, 'a'));
    TEST_ASSERT_EQUAL_INT(0, GraphC_add_vertex(graph, 'b'));

    TEST_ASSERT_EQUAL_INT(-1, GraphC_add_vertex(graph, 'b'));
    for (size_t i = 'a'; i <= 'z'; i++)
    {
        GraphC_add_vertex(graph, i);
    }

    TEST_ASSERT_EQUAL_size_t(26, graph->num_of_vertices);
    

}

void test_GraphC_add_edge(void) {
    for (size_t i = 'a'; i <= 'z'; i++) {
        GraphC_add_vertex(graph, i);
    }

    for (size_t i = 'b'; i <= 'z'; i++)
    {
        GraphC_add_edge(graph, 'a', i);
    }    
    
    GraphC_print(graph);

    TEST_ASSERT_EQUAL_size_t(25, graph->num_of_edges);
}

void test_GraphC_remove_vertex(void) {
    for (size_t i = 'a'; i <= 'z'; i++) {
        GraphC_add_vertex(graph, i);
    }

    //Beginning
    GraphC_remove_vertex(graph, 'a');
    //Middle
    GraphC_remove_vertex(graph, 'o');
    //End
    GraphC_remove_vertex(graph, 'z');

    TEST_ASSERT_EQUAL_size_t(23, graph->num_of_vertices);

    GraphC_add_edge(graph, 'b', 'c');
    GraphC_add_edge(graph, 'b', 'd');

    GraphC_print(graph);
    GraphC_remove_vertex(graph, 'c');
    GraphC_print(graph);

    GraphC_remove_vertex(graph, 'd');
    GraphC_print(graph);

    
}

void test_GraphC_destroy(void) {
    GraphC_destroy(&graph);
    TEST_ASSERT_NULL(graph);
}
