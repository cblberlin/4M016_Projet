#ifndef QUEUE_H
#define QUEUE_H

#include "M_Graph.h"

/*
quick define left(right) child and parent node function
*/
#define CHILD_LEFT(i) (2*i + 1)
#define CHILD_RIGHT(i) (2*i + 2)
#define PARENT(i) ((i-1) / 2)

typedef struct node_{
    double data;
    int position;
}node;

/*
size is the maximum number of queue allowed
tail is the position of the 
*/
typedef struct binary_heap_{
    node* nodes;
    int size;
    int tail;
}binary_heap;

void swap(node* n1, node* n2);

void init_heap(M_Graph* g);

void heap_push(binary_heap* q, double val);

void heapify(binary_heap* heap, int i);

double heap_pop(binary_heap* q);    


#endif