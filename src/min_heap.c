#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <math.h>
#include <time.h>

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
    // checking for the smallest element
    if(l <= h->capacity && h->nodes[l].weight < h->nodes[i].weight){
        smallest = l;
    }
    if(r <= h->capacity && h->nodes[r].weight < h->nodes[smallest].weight){
        smallest = r;
    }
    // updating the min heap
    if(smallest != i){
        swap(&(h->nodes[i]), &(h->nodes[smallest]));
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
        swap(&(h->nodes[i]), &(h->nodes[PARENT(i)]));
        i = PARENT(i);
    }
}

node ExtractMin(min_heap* h){
    node root;
    if(h->index == 0){
        return h->nodes[0];
    }
    // Store the minimum value, and remove it from heap
    root = h->nodes[0];
    h->nodes[0] = h->nodes[h->index - 1];
    h->index--;
    heapify(h, 0);
    return root;
}

void print_heap(min_heap* heap){
    int n = (int) log2(heap->index) + 1;
	printf("Heap is:\n");
	printf("%.3f\n", heap->nodes[0].weight);
    //printf("0\n");
	for(int i = 1; i < n; i++){
		for(int j = pow(2,i) - 1; j < pow(2, i + 1) - 1; j++){
			if(j < heap->index){
				printf("%.3f\t", heap->nodes[j].weight);
                //printf("%d\t", j);
			}
		}
		printf("\n");
	}
}

void test_heap(int n){
    min_heap* h = init_heap(n);
    double r;
    srand(time(NULL));
    for(int i = 0; i < n; i++){
        node x;
        x.index = i;
        r = (double)rand() / RAND_MAX * n;
        x.weight = r;
        Insert(h, x);
    }
    printf("\tIndex\tNode\tDist\n");
    for (int i = 0; i < h->index; i++) {
        printf("\t%d\t%s\t%.3f\n", h->nodes[i].index, int2char(h->nodes[i].index), h->nodes[i].weight);
    }
    print_heap(h);

    while(!heap_empty(h)){
        node u = ExtractMin(h);
        printf("\t -> Exploration in %s.\n", int2char(u.index));
        for (int i = 0; i < h->index; i++) {
            printf("\t%d\t%s\t%.3f\n", h->nodes[i].index, int2char(h->nodes[i].index), h->nodes[i].weight);
        }
        printf("\n");
        print_heap(h);
        printf("\n");
    }
}