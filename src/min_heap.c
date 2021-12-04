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
    //heap = (min_heap*)malloc(sizeof(min_heap));
    heap->size = n;
    if(heap == NULL){
        printf("Memory Error!\n");
        return;
    }
    heap->nodes = (node*)malloc(sizeof(node) * n);
    for(int i = 0; i < n; i++){
        heap->nodes[i].prev = 0;
    }
    heap->size = n;
    heap->tail = 0; 
}
/*
    Initialisation of a node
*/
void init_node(node* n){
    n->index = 0;
    n->weight = 0.;
    n->prev = 0;
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
    The following algorithm can be used to “fix” an array not necessarily
    satisfying the heap property.
*/
void Heapify(min_heap* heap, int i){
    int smallest = (CHILD_LEFT(i) < heap->size && heap->nodes[CHILD_LEFT(i)].weight < heap->nodes[i].weight) ? CHILD_LEFT(i) : i ;
    if(CHILD_RIGHT(i) < heap->size && heap->nodes[CHILD_RIGHT(i)].weight < heap->nodes[smallest].weight) {
        smallest = CHILD_RIGHT(i) ;
    }
    if(smallest != i) {
        swap(&(heap->nodes[i]), &(heap->nodes[smallest])) ;
        Heapify(heap, smallest) ;
    }
}

/*
    Decrease the key of current node and maintain the property of min heap
*/
void DecreaseKey(min_heap* heap, node* x, double val){
    if (val > heap->nodes[x->index].weight){
        return;
    }
    heap->nodes[x->index].weight = val;
    while(x->index > 0 && heap->nodes[PARENT(x->index)].weight > heap->nodes[x->index].weight){
        swap(&heap->nodes[x->index], &heap->nodes[PARENT(x->index)]);
        heap->nodes[x->index] = heap->nodes[PARENT(x->index)];
    }
}

/*
    insert a val to the heap and the heap maintain min-heap properties
*/
void Insert(min_heap* heap, node* x){
    heap->tail++;
    x->index = heap->tail;
    heap->nodes[1] = *x;
    DecreaseKey(heap, x, x->weight);
}

/*
    delete the node with minimum key in the heap and maintain the min heap property
*/
node ExtractMin(min_heap* heap){
    if(heap->tail < 0){
        fprintf(stderr, "Heap underflow");
    }
    node min = heap->nodes[0];
    heap->nodes[0] = heap->nodes[heap->tail];
    heap->tail--;
    Heapify(heap, 0);
    return min;
}

/*
    update the weight of v to w + u->weight 
    in the heap and maintain the min heap property
*/
void Relax(min_heap* heap, node* u, node* v, double w){
    if(v->weight > u->weight + w){
        DecreaseKey(heap, v, u->weight + w);
        v->prev = u->index;
    }
}

/*
    print heap with value
*/
void print_heap(min_heap* heap){
    int n = (int) log2(heap->tail) + 1;
	printf("Heap is:\n");
	printf("%f\n", heap->nodes[0].weight);
	for(int i = 1; i < n; i++){
		for(int j = pow(2,i) - 1; j < pow(2, i + 1) - 1; j++){
			if(j < heap->tail){
				printf("%f\t", heap->nodes[j].weight);
			}
		}
		printf("\n");
	}
}

