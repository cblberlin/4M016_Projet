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
    size is the maximum number of queue allowed
    tail is the position of the last item in heap
    data is the array of weights with size n
*/
typedef struct min_heap_{
    double* data;
    int size;
    int tail;
}min_heap;

void swap(double* n1, double* n2);

void init_heap(min_heap* heap, int n);

void free_heap(min_heap* heap);

void heap_push(min_heap* heap, double val);

bool heap_empty(min_heap* heap);

double extractMin(min_heap* heap);

#endif