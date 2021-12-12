/*
    implementation of priority queue using min-heap
*/


#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <stdbool.h>
#include "M_Graph.h"

/*
quick define left(right) child and parent node function
*/
#define CHILD_LEFT(i) (2*i + 1)
#define CHILD_RIGHT(i) (2*i + 2)
#define PARENT(i) ((i-1) / 2)

/*
    index is the index of this node in graph
    prev is the prev visited node for this node
    weight is the weight calculated for this node
*/
typedef struct node_{
    int index;
    int prev;
    double weight;
}node;

/*
    size is the maximum number of queue allowed
    tail is the position of the next item can be inserted, ex: 
    min heap
    size = 6
    nodes
    x0     x1     x2     x3      x4
    0      1      2      3       4
    -1     -1     -1     -3      -4 
    wo     w1     w2     w3      w4
    then the tail will be 5, so the maximum value of tail is size - 1
    data is the array of node with size n
*/
typedef struct min_heap_{
    node* nodes;
    int size;
    int tail;
}min_heap;

void swap(node* n1, node* n2);

min_heap* init_heap(int n);

bool heap_empty(const min_heap* heap);

void free_heap(min_heap* heap);

void heapifyUP(min_heap*h ,int n);

void heapifyDown(min_heap*h, int n);

void DecreaseKey(min_heap* heap, node* x, double val);

void Insert(min_heap* h, node x);

node ExtractMin(min_heap* h);

void Relax(min_heap* heap, node* u, node* v, double w);

void print_heap(min_heap* heap);

int* index_heap(min_heap* heap);

#endif