#include <stdlib.h>
#include <stdio.h>
#include <float.h>

#include "min_heap.h"

void swap(node* x, node* y) {
    node temp = *x ;
    *x = *y ;
    *y = temp ;
}

min_heap* init_heap(int Max_capacity){
    min_heap* h = (min_heap *) malloc(sizeof(min_heap));
    h->index = 0;
    h->capacity = Max_capacity;
    h->nodes = (node *) malloc(sizeof(node) * Max_capacity);
    return h;
}

bool heap_empty(const min_heap* heap){
    return (heap->index == 0) ? true : false;
}

bool heap_full(const min_heap* heap){
    return (heap->index == heap->capacity) ? true : false;
}

void free_heap(min_heap* h){
    free(h->nodes);
    free(h);
}

void heapify(min_heap*h, int i){
    int l = CHILD_LEFT(i);
    int r = CHILD_RIGHT(i);
    int smallest = i;
    if (l < h->index && h->nodes[l].weight < h->nodes[i].weight)
        smallest = l;
    if (r < h->index && h->nodes[r].weight < h->nodes[smallest].weight)
        smallest = r;
    if (smallest != i)
    {
        swap(&h->nodes[i], &h->nodes[smallest]);
        heapify(h, smallest);
    }
}

void Insert(min_heap *h, node x) {
    if(h->index == h->capacity){
        printf("heap overflowed !\n");
        return;
    }
    h->index++;
    int i = h->index - 1;
    h->nodes[i] = x;
    while (i != 0 && h->nodes[PARENT(i)].weight > h->nodes[i].weight){
        swap(&h->nodes[i], &h->nodes[PARENT(i)]);
        i = PARENT(i);
    }
}

void DecreaseKey(min_heap* h, int i, double val){
    if(val > h->nodes[i].weight){
        return;
    }
    h->nodes[i].weight = val;
    while (i != 0 && h->nodes[PARENT(i)].weight > h->nodes[i].weight){
        swap(&h->nodes[i], &h->nodes[PARENT(i)]);
        i = PARENT(i);
    }
}

node ExtractMin(min_heap* h){
    node root;
    if(h->index <= 0){
        root.index = -1;
        root.weight = DBL_MAX;
        return root;
    }
    if(h->index == 1){
        h->index--;
        return h->nodes[0];
    }
    // Store the minimum value, and remove it from heap
    root = h->nodes[0];
    h->nodes[0] = h->nodes[h->index - 1];
    h->index--;
    heapify(h, 0);
    return root;
}

int* index_heap(min_heap* h){
    int* res = (int *) malloc(sizeof(int) * h->index + 1);
    int count = 0;
    if(!heap_empty(h)){
        for(int i = 0; i < h->index; i++){
            res[i + 1] = h->nodes[i].index;
            count++;
        }
        res[0] = count;
    }
    return res;
}
