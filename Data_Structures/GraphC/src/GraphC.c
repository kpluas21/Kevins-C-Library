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

Vertex *GraphC_add_vertex(GraphC *graph, char x) {

    if(graph->vertices == NULL) {
        //Empty graph
        graph->vertices = malloc(sizeof(Vertex));
        if(!graph->vertices) {
            return NULL;
        }

        graph->vertices->key = x;
        graph->vertices->next_adj_vertex = NULL;
        graph->num_of_vertices++;
        return graph->vertices;
    }
    
    //Checking for duplicate vertex, return if found spitting out an error
    for (size_t i = 0; i < graph->num_of_vertices; i++) {
        if(graph->vertices[i].key == x) {
            printf("Error: Cannot insert duplicate vertex\n");
            return NULL;
        }
    }
    Vertex *new_vertex = malloc(sizeof(Vertex));
    if(new_vertex == NULL) {
        printf("Error allocating memory for new_vertex\n");
        return NULL;
    }
    new_vertex->key = x;
    new_vertex->next_adj_vertex = NULL;

    //Not NULL and No duplicates found. Append a new vertex to the tail end of the array.
    graph->vertices = realloc(graph->vertices, sizeof(Vertex) * graph->num_of_vertices + 1);
    memcpy(&graph->vertices[graph->num_of_vertices], new_vertex, sizeof(Vertex));
    graph->num_of_vertices++;

    return new_vertex;

}

void GraphC_destroy(GraphC **graph) {
    if(graph == NULL || (*graph) == NULL) {
        return;
    }

    //TODO: Destroy_node to be implemented once adding edges is good. 
    // Vertex *current_node = (*graph)->vertices;
    // Vertex *next_node;
    for (size_t i = 0; i < (*graph)->num_of_vertices; i++) {
        //For each Vertex whose adj_nabors is NOT NULL, go through them and free every node along the way
        if((*graph)->vertices[i].next_adj_vertex != NULL) {
            //FREE THE NABORS
        }
    }
    free((*graph)->vertices);
    free((*graph));
    (*graph) = NULL;
}
