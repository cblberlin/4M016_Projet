#include <stdio.h>
#include <stdlib.h>
#include "min_heap.h"

void swap(node* x1, node* x2){
    node temp = *x1;
    *x1 = *x2;
    *x2 = temp;
}

/*
    normally this n will be the number of vertices
    and the size of the min heap will be n.
    we start the index by 0;
*/
min_heap* init_heap(int n){
    min_heap* h = malloc(sizeof(min_heap));
    h->nodes = malloc(sizeof(node) * n);
    h->size = n;
    h->tail = 0;
    return h;
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

void heapifyUP(min_heap*h ,int n){
    if(n == 0) return;
    int parent = PARENT(n);
    if(h->nodes[n].weight >= h->nodes[parent].weight) return;
    swap(&h->nodes[n], &h->nodes[parent]);
    heapifyUP(h, parent);
}

void heapifyDown(min_heap*h, int n){
    int smallest = n;
    for(int i = n * 2 + 1; i <= n * 2 + 2; i++){
        if(i < h->tail - 1 && h->nodes[i].weight < h->nodes[smallest].weight){
            smallest = i;
        }
    }
    if(smallest == n) return;
    swap(&h->nodes[n], &h->nodes[smallest]);
    heapifyDown(h, smallest);
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
        /*
        int temp = heap->nodes[x->index].index;
        heap->nodes[x->index].index = heap->nodes[PARENT(x->index)].index;
        heap->nodes[PARENT(x->index)].index = temp;
        */
    }
}

/*
    insert a val to the heap and the heap maintain min-heap properties
*/
void Insert(min_heap* h, node x){
    // add element at the end of array
    h->nodes[h->tail] = x;
    //printf("%d\n", h->nodes[h->tail].index);
    // maintain min heap property
    heapifyUP(h, h->tail);
    h->tail++;
}

/*
    delete the node with minimum key in the heap and maintain the min heap property
*/
node ExtractMin(min_heap* h){
    node u = h->nodes[0];
    swap(&h->nodes[h->tail - 1], &h->nodes[0]);
    heapifyDown(h, 0);
    h->tail--;
    return u;
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
	printf("%.3f\n", heap->nodes[0].weight);
    //printf("0\n");
	for(int i = 1; i < n; i++){
		for(int j = pow(2,i) - 1; j < pow(2, i + 1) - 1; j++){
			if(j < heap->tail){
				printf("%.3f\t", heap->nodes[j].weight);
                //printf("%d\t", j);
			}
		}
		printf("\n");
	}
}

int* index_heap(min_heap* heap){
    int* index = (int*) malloc(sizeof(int) * heap->tail);  
    for(int i = 0; i < heap->tail; i++){
        index[i] = heap->nodes[i].index;
    }
    return index;
}