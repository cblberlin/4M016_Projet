#include <stdio.h>
#include <stdlib.h>
#include "min_heap.h"

void swap(node* n1, node* n2){
    node temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}

/*
    normally this n will be the number of vertices
    and the size of the min heap will be n.
    we start the index by 0;
*/
void init_heap(min_heap* heap, int n){
    heap = (min_heap *) malloc(sizeof(min_heap));
    heap->size = n;
    if(heap == NULL){
        printf("Memory Error!\n");
        return;
    }
    heap->nodes = malloc(sizeof(node) * n);
    heap->size = n;
    heap->tail = 0; 
}

void free_heap(min_heap* heap){
    free(heap->nodes);
    free(heap);
}

/*
    determine if the heap is empty or not
*/
bool heap_empty(const min_heap* heap){
    if(heap->tail == 0){
        return true;
    }
    return false;
}

/*
    insert a val to the heap and the heap maintain min-heap properties
*/
void heap_push(min_heap* heap, double val){

}

/*double extractMin(min_heap* heap){
    double min = INFINITY;

    for(int i = 0; i < heap->size; i++){
        if( heap->data[i] )
    }
}*/

