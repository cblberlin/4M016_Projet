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
    // initialisation of min heap
    min_heap* h = malloc(sizeof(min_heap));
    h = init_heap(g->N_vertex);

    // initialisation of array of distance and array of previous node
    // initialise dist as all node have distance infinity except the starting point src is 0.
    // initialise prev as all node have prev node -1 except the starting point src is 0;
    
    for(int i = 0; i < g->N_vertex; i++){
        dist[i] = INFINITY;
        prev[i] = -1;
    }

    // Insert the first node src in the heap
    node s;
    s.index = src;
    s.weight = 0.;
    Insert(h, s);
    //print_heap(h);
    while (!heap_empty(h))
    {
        // delete the min node on the heap
        node u = ExtractMin(h);
        //printf("\n%s has been extracted, current weight is %.3f, in array dist the value is %.3f\n", g->Names[u.index], u.weight, dist[u.index]);
        if(u.weight <= dist[u.index])
        {
            dist[u.index] = u.weight;

            // for all node v who has edge from u to v, and v is still not visited yet
            // here we suppose our graph is undirected
            for(int i = 0; i < g->N_vertex; i++)
            {
                if(g->weights[u.index][i] < INFINITY && u.index != i)
                {
                    if(dist[u.index] + g->weights[u.index][i] < dist[i])
                    {
                        node v;
                        v.index = i;
                        v.weight = dist[u.index] + g->weights[u.index][i];
                        Insert(h, v);
                        //printf("%s has been inserted to heap, the weight is %.3f.\n", g->Names[i], dist[i]);
                        //print_heap(h);
                        dist[i] = dist[u.index] + g->weights[u.index][i];
                        prev[i] = u.index;
                        //printf("%s has been inserted to heap, the weight is %.3f.\n\n", g->Names[i], dist[i]);
                        //print_heap(h);
                    }
                }
            }
        }
    }
    
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