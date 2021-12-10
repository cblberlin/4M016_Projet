#include <stdbool.h>
#include <math.h>
#include "Dijkstra.h"
#include "min_heap.h"

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
    printf("dijkstra(%s): \n", g->Names[src]);
    for(i = 0; i < g->N_vertex; i++){
        printf("shortest(%s, %s)=%f\n", g->Names[src], g->Names[i], dist[i]);
    }
}

void single_source_dijkstra_min_heap(M_Graph* g, int src, double* dist, int* prev){
    min_heap* heap = init_heap(g->N_vertex);

    for(int i = 0; i < g->N_vertex; i++){
        prev[i] = -1;
        dist[i] = INFINITY;
    }
    dist[src] = 0.;

    // Enqueue all the nodes
    for(int i = 0; i < g->N_vertex; i++){
        node v;
        v.index = i;
        v.prev = -1;
        v.weight = dist[i];
        Insert(heap, v);
    }

    //print_heap(heap);
    
    while(!heap_empty(heap)){
        node u = ExtractMin(heap);

        for(int i = 0; i < g->N_vertex; i++){
            if(g->weights[u.index][i] != INFINITY && i != u.index){
                node v;
                v.index = i;
                v.prev = prev[i];
                v.weight = dist[i];
                if(dist[u.index] + g->weights[u.index][v.index] < dist[v.index]){
                    dist[v.index] = dist[u.index] + g->weights[u.index][v.index];
                    DecreaseKey(heap, &v, dist[v.index]);
                    v.prev = u.index;
                    prev[v.index] = u.index;
                }         
            }
        }
    }
    printf("dijkstra(%s): \n", g->Names[src]);
    for(int i = 0; i < g->N_vertex; i++){
        printf("shortest(%s, %s)=%f\n", g->Names[src], g->Names[i], dist[i]);
        
    }
}