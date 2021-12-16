#include <stdlib.h>
#include <stdio.h>
#include <float.h>

#include "min_heap.h"

void swap(node* n1, node* n2) {
    node temp = *n1 ;
    *n1 = *n2 ;
    *n2 = temp ;
}

min_heap* init_heap(min_heap* h){
    h = (min_heap *) malloc(sizeof(min_heap));
    h->size = 1;
    h->nodes = (node *) malloc(sizeof(node) * h->size);
    h->count = 0;
    return h;
}

bool heap_empty(const min_heap* heap){
    if(heap->count == 0){
        return true;
    }else{
        return false;
    }
}

void free_heap(min_heap* h){
    free(h->nodes);
    free(h);
}

void heapify(min_heap*h, int index){
    int l = CHILD_LEFT(index);
    int r = CHILD_RIGHT(index);
    int smallest = (l < h->size && h->nodes[l].weight < h->nodes[index].weight) ? l : index;
    if(r < h->size && h->nodes[r].weight < h->nodes[smallest].weight) {
        smallest = r ;
    }
    if(smallest != index) {
        swap(&(h->nodes[index]), &(h->nodes[smallest])) ;
        heapify(h, smallest) ;
    }
}

void Insert(min_heap *h, node x) {
    if(h->count) {
        h->nodes = realloc(h->nodes, (h->size + 1) * sizeof(node)) ;
    } else {
        h->nodes = malloc(sizeof(node)) ;
    }

    int i = (h->count)++ ;
    while(i && x.weight < h->nodes[PARENT(i)].weight) {
        h->nodes[i] = h->nodes[PARENT(i)] ;
        i = PARENT(i) ;
    }
    h->nodes[i] = x ;
}

void Pop(min_heap* h){
    if(h->count) {
        //printf("Deleting node %.3f\n\n", h->node[0].weight) ;
        h->nodes[0] = h->nodes[--(h->count)] ;
        h->nodes = realloc(h->nodes, h->count * sizeof(node)) ;
        heapify(h, 0) ;
    } else {
        //printf("\nMin Heap is empty!\n") ;
        free(h->nodes) ;
    }
}

node Top(min_heap* h){
    if(h->count != 0){
        return h->nodes[0];
    }else{
        node x;
        x.weight = DBL_MAX;
        x.index = -1;
        return x;
    }
}

void DecreaseKey(min_heap* heap, int i, double val){
    if(val > heap->nodes[i].weight){
        return;
    }
    heap->nodes[i].weight = val;
    while(i > 0 && heap->nodes[PARENT(i)].weight > heap->nodes[i].weight){
        swap(&heap->nodes[i], &heap->nodes[PARENT(i)]);
        i = PARENT(i);
    }
}