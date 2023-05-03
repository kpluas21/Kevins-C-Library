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

/**
 * @brief Helper function: Destroys ALL adjacent vertices of a given head(unique) Vertex. Mainly used by GraphC.h::GraphC_remove_vertex() 
 * 
 * @param head_node A pointer to the Vertex node in the contiguous array located in GraphC
 */
static void GraphC_destroy_list(Vertex *head_node);

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

int GraphC_add_vertex(GraphC *graph, char x) {

    if(graph->vertices == NULL) {
        //Empty graph
        graph->vertices = malloc(sizeof(Vertex));
        if(!graph->vertices) {
            return -1;
        }

        graph->vertices->key = x;
        graph->vertices->next_adj_vertex = NULL;
        graph->num_of_vertices++;
        return 0;
    }
    
    //Checking for duplicate vertex, return if found spitting out an error

    if(GraphC_vertex_exists(graph, x) != -1) {
        printf("Error: Cannot insert duplicate vertex\n");
        return -1;
    }

    Vertex new_vertex;
    new_vertex.key = x;
    new_vertex.next_adj_vertex = NULL;

    graph->num_of_vertices++;
    graph->vertices = realloc(graph->vertices, sizeof(Vertex) * graph->num_of_vertices);
    graph->vertices[graph->num_of_vertices - 1] = new_vertex;


    return 0;

}

/* Like any dynamic array , the contents of .vertices will have to be shifted over to close the gap left when removing a vertex */
/* And when a vertex gets removed, the associated edge must also be removed.  */

int GraphC_remove_vertex(GraphC *graph, char x) {
    for (size_t i = 0; i < graph->num_of_vertices; i++) {
        //We found the "root" vertex to be removed
        if(x == (graph->vertices + i)->key) {
            //destroy this root vertex's whole list of neighbors
            GraphC_destroy_list( graph->vertices + i );

            //overwrite the root vertex's spot in memory
            memmove(graph->vertices + i, graph->vertices + i + 1, (sizeof(Vertex) * (graph->num_of_vertices - i)));
            graph->num_of_vertices--;

        }
        //Go through all of the adj_vertices to the root vertex and remove all instances of the 
        //removed vertex.
        else {
            Vertex *head = (graph->vertices + i)->next_adj_vertex;
            if(head == NULL) {
                //Skip over this vertex. No neighbors
            }

            //Handle the case where the head adj_vertex is the key.
            else if(head->key == x) {
                Vertex *temp = head;
                (graph->vertices + i)->next_adj_vertex = head->next_adj_vertex;
                free(temp);
                graph->num_of_edges--;
            }


            else {
                while(head->next_adj_vertex != NULL) {
                    if(head->next_adj_vertex->key == x) {
                        Vertex *temp = head->next_adj_vertex;
                        head->next_adj_vertex = head->next_adj_vertex->next_adj_vertex;
                        free(temp);
                        graph->num_of_edges--;
                        continue;
                    }
                    head = head->next_adj_vertex;
                }
            }

        }
    }
    return 0;
    
}

void GraphC_add_edge(GraphC *graph, char x, char y) { 
    int iX, iY; //Indices for our keys to be used for insertion

    iX = GraphC_vertex_exists(graph, x);
    iY = GraphC_vertex_exists(graph, y);

    if(iX == -1 || iY == -1) {
        printf("Invalid vertices inputted\n");
        return;
    }

    //Both vertices exists, add them to each other's adj_list
    Vertex *newVertex_X = malloc(sizeof(Vertex));
    Vertex *newVertex_Y = malloc(sizeof(Vertex));

    if(newVertex_X == NULL || newVertex_Y == NULL) {
        printf("Error: Cannot malloc newVertex in %s\n", __func__);
        return;
    }

    //This linked list is unordered, so to keep it fast, simply insert these new
    //vertices to the head of the list. 

    Vertex *tempNode;

    newVertex_X->key = x;
    newVertex_Y->key = y;

    tempNode = graph->vertices[iY].next_adj_vertex;
    graph->vertices[iY].next_adj_vertex = newVertex_X;
    newVertex_X->next_adj_vertex = tempNode;


    tempNode = graph->vertices[iX].next_adj_vertex;
    graph->vertices[iX].next_adj_vertex = newVertex_Y;
    newVertex_Y->next_adj_vertex = tempNode;

    graph->num_of_edges++;
}

// int GraphC_remove_edge(GraphC *graph, char x, char y) {
//     return 0;
// }

int GraphC_vertex_exists(GraphC *graph, char key)
{
    for (size_t i = 0; i < graph->num_of_vertices; i++) {
        if(graph->vertices[i].key == key) {
            return i;
        }
    }
    return -1;
}

void GraphC_print(GraphC *graph) {
    Vertex *traversalPtr;
    for (size_t i = 0; i < graph->num_of_vertices; i++)
    {
        printf("%c | ", graph->vertices[i].key);
        traversalPtr = graph->vertices[i].next_adj_vertex;
        
        while(traversalPtr != NULL) {
            printf("%c ", traversalPtr->key);
            traversalPtr = traversalPtr->next_adj_vertex;
        }
        printf("\n");
    }
    printf("\n");
    
}

void GraphC_destroy(GraphC **graph)
{
    if(graph == NULL || (*graph) == NULL) {
        return;
    }
 
    Vertex *current_node;
    Vertex *next_node;

    for (size_t i = 0; i < (*graph)->num_of_vertices; i++) {
        current_node = (*graph)->vertices[i].next_adj_vertex;
        //For each Vertex whose adj_nabors is NOT NULL, go through them and free every node along the way
        if(current_node != NULL) {
            next_node = current_node->next_adj_vertex;
            free(current_node);
            current_node = next_node;
        }
    }
    free((*graph)->vertices);
    free((*graph));
    (*graph) = NULL;
}

//We pass the "node" thats inside the ARRAY, not the node pointed to by the array.
void GraphC_destroy_list(Vertex *head_node) {
    if(head_node->next_adj_vertex == NULL) {
        return; //Covers vertices without any neighbors
    }

    //If there are neighbors
    Vertex *current_node = head_node->next_adj_vertex;
    Vertex *next_node;
    while(current_node != NULL) {
        next_node = current_node->next_adj_vertex;
        free(current_node);
        current_node = next_node;
    }

    return;
}
