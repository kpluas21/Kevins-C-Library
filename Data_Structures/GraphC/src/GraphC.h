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

/**
 * @struct Vertex
 * 
 * @brief The main nodes that make up the graph. Contains a pointer to another
 * vertex as it's neighbor, if one exists.
 * 
 * @var Vertex::key
 * Key is simply a label for the vertex to ensure no duplicates exist.
 * 
 * @var Vertex::next_adj_vertex
 * next_adj_vertex is a pointer to another Vertex object adjacent to this one. The pointers are structured
 * as a linked list.
 * 
 */
typedef struct Vertex Vertex;

typedef struct Vertex {
    char key; //The actual name of the vertex
    Vertex *next_adj_vertex; //The neighbors adjacent to this vertex
}Vertex;

/**
 * @struct GraphC
 * 
 * @brief The main data structure used to interact and interface with the graph.
 * 
 * @var GraphC::num_of_edges
 * The number of edges contained in our graph. A single edge is defined as a connection between a pair of vertices.
 * 
 * @var GraphC::num_of_vertices
 * The number of vertices contained in our graph. A single vertex is defined as a data node or point that make up a graph.
 * 
 * @var GraphC::vertices
 * A pointer to the first vertex in our graph. Every unique instance of a vertex is stored in a contiguous array. It's easier to think of 
 * the graph as an array of linked lists. 
 */
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
int GraphC_add_vertex(GraphC *graph, char x);

/**
 * @brief Removes vertex x from the graph if it exists.
 * 
 * @param graph 
 * @param x The vertex to remove.
 * @return int 0 if successful. Non zero otherwise
 */
int GraphC_remove_vertex(GraphC *graph, char x);

/**
 * @brief Adds an edge from vertex x to vertex y if it does not exist already
 * 
 * @param graph 
 * @param x 
 * @param y 
 */
void GraphC_add_edge(GraphC *graph, char x, char y);

/**
 * @brief Removes the edge from x to y, if it exists.
 * 
 * @param graph 
 * @param x 
 * @param y 
 * @return int 0 if successful, Non zero otherwise.
 */
int GraphC_remove_edge(GraphC *graph, char x, char y);

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