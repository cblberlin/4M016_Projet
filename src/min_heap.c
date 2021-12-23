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
    h->nodes = (node *) malloc(Max_capacity * sizeof(node));
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
    if(l <= h->index && h->nodes[l].weight < h->nodes[i].weight){
        smallest = l;
    }
    if(r <= h->index && h->nodes[r].weight < h->nodes[smallest].weight){
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
    h->nodes = realloc(h->nodes, h->index * sizeof(node));
    h->capacity *= 2;
    int i = h->index - 1;
    h->nodes[i] = x;
    while (i != 0 && h->nodes[PARENT(i)].weight > h->nodes[i].weight){
        swap(&h->nodes[i], &h->nodes[PARENT(i)]);
        i = PARENT(i);
    }
}

void DecreaseKey(min_heap* h, int i, double val){
    if(val >= h->nodes[i].weight){
        return;
    }
    h->nodes[i].weight = val;
    
    while (i > 0){
        if(h->nodes[i].weight < h->nodes[PARENT(i)].weight){
            swap(&h->nodes[i], &h->nodes[PARENT(i)]);
            i = PARENT(i);
        }else{
            break;
        }
    }
    //heapify(h, i);
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
    //h->nodes = realloc(h->nodes, h->index * sizeof(node));
    heapify(h, 0);
    return root;
}

void print_heap(min_heap* heap){
    if(heap->index == 0){
        printf("Heap is empty\n");
        return;
    }
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

/*
    check if index i in the heap or not
*/
bool is_in_heap(min_heap* h, int i)
{
    for(int i = 0; i < h->index; i++)
    {
        if(i == h->nodes->index)
        {
            return true;
        }
    }
    return false;
}