#include <stdio.h>
#include <stdlib.h>
#include "M_Graph.h"
#include "L_Graph.h"
#include "min_heap.h"

void single_source_dijkstra(M_Graph* g, int src, double* dist, int* prev);

void single_source_dijkstra_min_heap(M_Graph* g, int src, double* dist, int* prev);

void single_source_dijkstra_adj_list(L_Graph* g, int src, double* dist, int* prev);

void single_source_dijkstra_adj_list_min_heap(L_Graph* g, int src, double* dist, int* prev);