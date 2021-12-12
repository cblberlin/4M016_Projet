#include <stdbool.h>
#include <math.h>
#include "Dijkstra.h"
#include "min_heap.h"

#define DEBUG 0

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
    bool* flag = (bool *) malloc(sizeof(bool) * g->N_vertex);
    for(int i = 0; i < g->N_vertex; i++){
        prev[i] = -1;
        dist[i] = INFINITY;
        flag[i] = false;
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
        flag[u.index] = true;
        for(int i = 0; i < g->N_vertex; i++){
            if(g->weights[u.index][i] != INFINITY && i != u.index){
                node v;
                v.index = i;
                v.prev = prev[i];
                v.weight = dist[i];
                if(flag[v.index] == false){
                    double temp = dist[u.index] + g->weights[u.index][v.index];
                    if(temp < dist[v.index]){
                        dist[v.index] = temp;
                        prev[v.index] = u.index;
                        DecreaseKey(heap, &v, dist[v.index]);
                        v.prev = u.index;
                    }
                }      
            }
        }
    }
    printf("dijkstra(%s): \n", g->Names[src]);
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