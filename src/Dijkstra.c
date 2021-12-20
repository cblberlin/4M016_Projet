#include <stdbool.h>
#include <math.h>
#include "Dijkstra.h"
#include "min_heap.h"

#define DEBUG 1

/*
with given single source vertex and single destination vertex,
return the minimum length of path with algo dijkstra
without using min-heap
*/
void single_source_dijkstra(M_Graph* g, int src, double* dist, int* prev){
    int i, j, k;
    double min;
    double temp;
    int* flag = (int *) malloc(sizeof(int) * g->N_vertex);

    //dist = malloc(sizeof(double) * g->N_vertex);
    //prev = malloc(sizeof(int) * g->N_vertex);
    for(i = 0; i < g->N_vertex; i++){
        //printf("test1\n");
        flag[i] = 0;
        prev[i] = 0;
        dist[i] = g->weights[src][i];
    }
    //printf("test1\n");
    flag[src] = 1;
    dist[src] = 0;
    //printf("test1\n");
    for(i = 0; i < g->N_vertex; i++){
        min = INFINITY;
        for(j = 0; j < g->N_vertex; j++){
            //printf("%d\n", flag[i]);
            if(flag[j] == 0 && dist[j] < min){
                //printf("test1\n");
                min = dist[j];
                k = j;
                //printf("test1\n");
            }
        }
        flag[k] = 1;

        for(j = 0; j < g->N_vertex; j++){
            temp = (g->weights[k][j] == INFINITY ? INFINITY : (min + g->weights[k][j]));
            if(flag[j] == 0 && (temp < dist[j])){
                dist[j] = temp;
                prev[j] = k;
            }
        }
    }
    
    printf("\ndijkstra(%s): \n", g->Names[src]);
    for(i = 0; i < g->N_vertex; i++){
        int temp = i;
        bool arrived = (temp == src);
        printf("shortest(%s, %s)=%f\n", g->Names[src], g->Names[i], dist[i]);
        if(temp == src){
            printf("the path is %s -> %s\n", g->Names[src], g->Names[temp]);
        }else{
            printf("the path is\t");
            while(!arrived){
                printf("%s -> %s\t", g->Names[temp], g->Names[prev[temp]]);
                temp = prev[temp];
                arrived = (temp == src);
                //printf("\n");
            }
            printf("\n");
        }
    }
}

void single_source_dijkstra_min_heap(M_Graph* g, int src, double* dist, int* prev){
    min_heap* heap = init_heap(g->N_vertex);
    if(DEBUG){
        printf("The min heap has been succefully allocated\n");
        printf("The capacity of the min heap is %d\n", heap->capacity);
        printf("The current index of the min heap is %d\n", heap->index);
        //printf("The first node of the min heap is %.3f\n", heap->weights[0]);

    }
    bool* flag = (bool *) malloc(sizeof(bool) * g->N_vertex);
    for(int i = 0; i < g->N_vertex; i++){
        prev[i] = -1;
        dist[i] = INFINITY;
        flag[i] = false;
    }
    dist[src] = 0.;
    
    // Enqueue all the nodes
    for(int i = 0; i < g->N_vertex; i++){
        node x;
        x.index = i;
        x.weight = dist[i];
        Insert(heap, x);
    }

    //print_heap(heap);
    
    while(!heap_empty(heap)){
        if(DEBUG) {
            printf("\tIndex\tNode\tDist\n");
                for (int i = 0; i < heap->index; i++) {
                printf("\t%d\t%s\t%.3f\n", heap->nodes[i].index, g->Names[heap->nodes[i].index], heap->nodes[i].weight);
            }
            print_heap(heap);
        }
        node u = ExtractMin(heap);
        if(DEBUG) {
            printf("\t -> Exploration in %s.\n", g->Names[u.index]);
        }
        flag[u.index] = true;
        //int* index = index_heap(heap);
        for(int i = 0; i < g->N_vertex; i++){
            // for all node that's ajacent with u and still in min heap
            if(g->weights[u.index][i] < INFINITY && i != u.index && flag[i] == false){
                /*
                node v;
                v.index = i;
                v.weight = dist[i];
                */
                if(DEBUG) {
                    printf("\t\tExaminating the edge %s->%s and the weight is\t%.3f\n\n", g->Names[u.index], g->Names[i], g->weights[u.index][i]);
                }
                double temp = dist[u.index] + g->weights[u.index][i];
                if(temp < dist[i]){
                    if(DEBUG) {
                        printf("\t\tBefore update the adjacent node %s has the weight %.3f and his previous node is %s\n", g->Names[i], dist[i], g->Names[prev[i]]);
                    }
                    dist[i] = temp;
                    prev[i] = u.index;
                    DecreaseKey(heap, i, dist[i]);
                    if(DEBUG) {
                        printf("\t\tAfter update the adjacent node %s has the weight %.3f and his previous node is %s\n\n", g->Names[i], dist[i], g->Names[prev[i]]);
                    }
                }
                   
            }
            
        }
    }

    free_heap(heap);

    
    printf("\ndijkstra(%s): \n", g->Names[src]);
    for(int i = 0; i < g->N_vertex; i++){
        int temp = i;
        bool arrived = (temp == src);
        printf("shortest(%s, %s)=%f\n", g->Names[src], g->Names[i], dist[i]);
        if(temp == src){
            printf("the path is %s -> %s\n", g->Names[src], g->Names[temp]);
        }else{
            printf("the path is\t");
            while(!arrived){
                printf("%s -> %s\t", g->Names[temp], g->Names[prev[temp]]);
                temp = prev[temp];
                arrived = (temp == src);
                //printf("\n");
            }
            printf("\n");
        }
    }
    
}