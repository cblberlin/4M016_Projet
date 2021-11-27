#include <stdio.h>
#include <stdlib.h>
#include "binary_heap.h"

// void swap(double *x, double *y){
// 	double temp = 0.0;
// 	temp = *x;
// 	*x = *y;
// 	*y = temp;
// }

// /*
// initialisation of binary heap
// */
// void init_heap(M_Graph*g){
//     binary_heap* heap = (binary_heap*) malloc(sizeof(binary_heap));
//     if(heap == NULL){
//         printf("Memory Error!\n");
//         return;
//     }
//     heap->data = (double *) malloc(sizeof(double) * g->N_vertex);
//     // check if allocation succed
//     if(heap->data == NULL){
//         printf("Memory Error!\n");
//         return;
//     }
//     heap->size = g->N_vertex;
//     heap->tail = 0;
// }

// /*
// insert a key to the heap which maintain min-heap property
// */
// void heap_push(binary_heap* heap, double val){
//     int i = heap->tail++;
//     while(i && val < heap->data[PARENT(i)]){
//         heap->data[i] = heap->data[PARENT(i)];
//         i = PARENT(i);
//     }
//     heap->data[i] = val;

//     /*int index_parent = HEAP_PARENT(index);
//     while(heap->data[index_parent] > heap->data[index]){
//         double temp = heap->data[index_parent];
//         heap->data[index_parent] = heap->data[index];
//         heap->data[index] = temp;
//         int index_temp = 0;
//         index_temp = index_parent;
//         index = index_parent;
//         index_parent = HEAP_PARENT(index_temp);
//     }*/
// }

// void heapify(binary_heap* heap, int i){
//     int smallest = (CHILD_LEFT(i) < heap->size && heap->data[CHILD_LEFT(i)] < heap->data[i]) ? CHILD_LEFT(i) : i;
//     if(CHILD_RIGHT(i) < heap->size && heap->data[CHILD_RIGHT(i)] < heap->data[smallest]){
//         smallest = CHILD_RIGHT(i);
//     }
//     if(smallest != i){
//         swap(&heap->data[i], &heap->data[smallest]);
//         heapify(heap, smallest);
//     }
// }

// /*
// return the minimum key of a heap and maintain the min-heap property
// */
// double heap_pop(binary_heap* heap){
//     double res = heap->data[0];
//     if(heap->size){
//         heap->data[0] = heap->data[--(heap->size)];
//         heap->data = realloc(heap->data, heap->size * sizeof(double));
//         heapify(heap, 0);
//     }else{
//         free(heap->data);
//     }
//     return res;
// }

/*
    To swap data within two nodes of min heap using pointers
*/
void swap(node* n1, node* n2){
    node temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}

void init_heap(M_Graph* g){
    binary_heap* heap = (binary_heap *) malloc(sizeof(binary_heap));
    heap->size = g->N_vertex;
    if(heap == NULL){
        printf("Memory Error!\n");
        return;
    }
    //heap->nodes = 
}