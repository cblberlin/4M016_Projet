#ifndef M_GRAPHE_H
#define M_GRAPHE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef INFINITY

#endif

#define MAX_WEIGHT 10.

#define LENGTH()

typedef struct M_Graph_{
    char** Names;       // the array of characters which represente the name of each vertex;
    int N_vertex;       // the number of vertex
    int N_edge;         // the number of edge
    double** weights;    // the adjacency matrix of graph, indexing like M(i,j) = weights(i*N_vertex + j)
}M_Graph;

M_Graph* init_graph(int n);

void free_graph(M_Graph* g);

void add_Edge(M_Graph* g, unsigned int i, unsigned int j, double weight);

void print_graph(M_Graph *g);

M_Graph* create_graph_random(int n, int v, double max_weight);

int* neihbors(M_Graph* g, int n);

#endif