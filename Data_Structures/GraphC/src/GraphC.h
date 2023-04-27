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
 * Each node will contain a key in the form of a char, followed by a list of VertexNodes adjacent to this vertex
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
 * @return Vertex* A pointer to the newly created vertex. Can be safely discarded. NULL
 * on error.
 */
Vertex *GraphC_add_vertex(GraphC* graph, char x);

/**
 * @brief Adds an edge from vertex x to vertex y if it does not exist already
 * 
 * @param graph 
 * @param x 
 * @param y 
 */
void GraphC_add_edge(GraphC *graph, char x, char y);

/**
 * @brief Frees up all memory associated with the graph and destroys all
 * associated objects 
 * 
 * @param graph 
 */
void GraphC_destroy(GraphC **graph);

#endif //_GRAPHC_H