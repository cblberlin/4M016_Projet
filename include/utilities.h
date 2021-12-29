#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdbool.h>

#include "M_Graph.h"
#include "L_Graph.h"

char* int2char(int n);

void find_path(L_Graph* g, int src, int dest, int* prev);

void findpath(M_Graph* g, int src, int dest, int* prev);

void Dijkstra_resultat_compare(M_Graph* g, int src, double* dist1, int* prev1, double* dist2, int* prev2);

void Dijkstra_resultat_compare2(L_Graph* g, int src, double* dist1, int* prev1, double* dist2, int* prev2);

void printresult(L_Graph*g, int src, double* dist, int* prev);

void print_result(M_Graph*g, int src, double* dist, int* prev);

bool compare_result(int n, double* dist1, double* dist2, int* prev1, int* prev2);

#endif