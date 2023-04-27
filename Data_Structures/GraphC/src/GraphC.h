#ifndef GRAPHC_H
#define GRAPHC_H
/**
 * @file GraphC.h
 * @author Kevin Pluas (kpluas21@gmail.com)
 * @brief Interface for GraphC
 * @version 0.1
 * @date 2023-04-25
 * 
 * @copyright Copyright (c) 2023
 * 
 * This is GraphC, an undirected, unweighted graph. This graph will be represented using an adjacency list through the use of linked lists. 
 * 
 * GraphC stores a contiguous array of Vertexs which serve as heads to a linked list of adjacent neighbors. 
 */

#include<stdlib.h>

typedef struct Vertex Vertex;

typedef struct Vertex {
    char key; //The actual name of the vertex
    Vertex *next_adj_vertex; //The neighbors adjacent to this vertex
}Vertex;

typedef struct GraphC {
    size_t num_of_edges;
    size_t num_of_vertices;
    Vertex *vertices;
}GraphC;

/**
 * @brief Initializes a graph containing no vertices, and by extension, no edges.
 * 
 * @return GraphC* 
 */
GraphC *GraphC_init(void);

/**
 * @brief Adds a vertex, x, to the graph.
 * 
 * @param graph Our graph pointer
 * @param x The label/key of the vertex to be added
 * @return int A non zero value on error
 */
int GraphC_add_vertex(GraphC* graph, char x);

/**
 * @brief Adds an edge from vertex x to vertex y if it does not exist already
 * 
 * @param graph 
 * @param x 
 * @param y 
 */
void GraphC_add_edge(GraphC *graph, char x, char y);

/**
 * @brief Searches for the vertex in the graph, returning its index in the list, -1 otherwise.
 * 
 * @param graph 
 * @param key 
 * @return size_t 
 */
int GraphC_vertex_exists(GraphC *graph, char key);

/**
 * @brief Prints a list of all vertices and their adjacent neighbors.
 * 
 * @param graph 
 */
void GraphC_print(GraphC *graph);

/**
 * @brief Frees up all memory associated with the graph and destroys all
 * associated objects 
 * 
 * @param graph 
 */
void GraphC_destroy(GraphC **graph);

#endif //_GRAPHC_H