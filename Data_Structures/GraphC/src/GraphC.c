/**
 * @file GraphC.c
 * @author Kevin Pluas (kpluas21@gmail.com)
 * @brief Implementation of GraphC, an undirected, unweighted graph stored as an adjacency list
 * @version 0.1
 * @date 2023-04-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include"GraphC.h"

#include<stdlib.h>
#include<stdio.h>
#include<string.h>


GraphC *GraphC_init(void) {
    GraphC *graph = malloc(sizeof(GraphC));
    if(graph == NULL) {
        printf("Error allocating memory for graph\n");
        return NULL;
    }

    graph->num_of_edges = 0;
    graph->num_of_vertices = 0;
    graph->vertices = NULL;

    return graph;
}

void GraphC_add_vertex(GraphC *graph, char x) {
    if(graph->vertices == NULL) {
        //Empty graph
        graph->vertices = malloc(sizeof(Vertex));
        if(!graph->vertices) {
            return;
        }

        graph->vertices->key = x;
        graph->vertices->next_adj_vertex = NULL;
        graph->num_of_vertices++;
        return;
    }
    
    //Checking for duplicate vertex, return if found spitting out an error
    for (size_t i = 0; i < graph->num_of_vertices; i++) {
        if(graph->vertices[i].key == x) {
            printf("Error: Cannot insert duplicate vertex\n");
            return;
        }
    }
    Vertex *new_vertex = malloc(sizeof(Vertex));
    if(new_vertex == NULL) {
        printf("Error allocating memory for new_vertex\n");
        return;
    }
    new_vertex->key = x;
    new_vertex->next_adj_vertex = NULL;

    //Not NULL and No duplicates found. Append a new vertex to the tail end of the array.
    graph->vertices = realloc(graph->vertices, sizeof(Vertex) * graph->num_of_vertices + 1);
    memcpy(&graph->vertices[graph->num_of_vertices], new_vertex, sizeof(Vertex));

}
