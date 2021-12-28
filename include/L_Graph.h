#ifndef L_GRAPHE_H
#define L_GRAPHE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "osm_parser.h"

#ifdef INFINITY

#endif

typedef struct adjacency_list_node_ {  // Represents edges between nodes
  int nodeID;  // Other end of the edge
  double weight;  // Weight of the edge
  struct adjacency_list_node_ *next;  // Pointer to next item in the adjacency linked list
} adjacency_list_node;

typedef struct adjacency_list_ {  // Represents a node
  int nb_members;  // Number of members in the adjacency list
  adjacency_list_node *head;  // Head of the adjacency linked list
} adjacency_list;

typedef struct L_graph_ {
  int N_vertex;  // Number of vertices
  int N_edge;    // Number of edges
  char** Names;  // Name of node
  adjacency_list *adjacency_list_array;  // An array of adjacency lists
} L_Graph;

void Create_L_Graph(L_Graph* g, int n);

void free_L_Graph(L_Graph* g);

void addEdge(L_Graph* g, int src, int dest, double weight);

void printNode(L_Graph* g, int n);

void printGraph(L_Graph* g);

void create_L_graph_random(L_Graph* g, int n, int e, double max_wweight);

double get_weight(L_Graph* g, int i, int j);

L_Graph* readGraph(char* filename);
#endif