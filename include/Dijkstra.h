#include <stdio.h>
#include <stdlib.h>
#include "M_Graph.h"
#include "binary_heap.h"

void single_source_dijkstra(M_Graph* g, int src, double* dist, int* prev);