#ifndef UTILITIES_H
#define UTILITIES_H

#include "M_Graph.h"

char* int2char(int n);

void Dijkstra_resultat_compare(M_Graph* g, int src, double* dist1, int* prev, double* dist2, int* prev2);

#endif