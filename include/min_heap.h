/*
    implementation of priority queue using min-heap
*/


#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <stdbool.h>
#include "M_Graph.h"
#include "utilities.h"

/*
quick define left(right) child and parent node function
*/
#define CHILD_LEFT(i) (2*i + 1)
#define CHILD_RIGHT(i) (2*i + 2)
#define PARENT(i) ((i-1) / 2)

typedef struct node_{
    double weight;
    int index;
}node;

/*
    size is the maximum number of queue allowed
    tail is the position of the next item can be inserted, ex: 
    min heap
    size = 6
    nodes =
    x0     x1     x2     x3      x4
    0      1      2      3       4
    wo     w1     w2     w3      w4
    then the index of next node inserted will be 5, the maximum value of tail is size - 1
    nodes is the array of node with size n
*/
typedef struct min_heap_{
    node* nodes;
    int capacity;
    int index;
}min_heap;

void swap(node* x, node* y);

min_heap* init_heap(int Max_capacity);

bool heap_empty(const min_heap* heap);

bool heap_full(const min_heap* heap);

void free_heap(min_heap* heap);

void heapify(min_heap*h, int index);

void Insert(min_heap* h, node x);

void DecreaseKey(min_heap* heap, int i, double val);

node ExtractMin(min_heap* h);

int* index_heap(min_heap* h);

void print_heap(min_heap* heap);

void test_heap(int n);

#endif