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
void single_source_dijkstra(M_Graph* g, int src, double* dist, int* prev)
{
    int i,j,k;
    double min;
    double tmp;
    int* flag = (int *) malloc(sizeof(int) * g->N_vertex);     
    
    // initialisation
    for (i = 0; i < g->N_vertex; i++)
    {
        flag[i] = 0;              
        prev[i] = 0;              
        dist[i] = g->weights[src][i];
    }

    // initialisation for src
    flag[src] = 1;
    dist[src] = 0;

    // 遍历G.vexnum-1次；每次找出一个顶点的最短路径。traverse all nodes, find the minimum distance
    for (i = 1; i < g->N_vertex; i++)
    {
        // for all nodes not visited yet, find the node with shortest distance with src
        min = INFINITY;
        for (j = 0; j < g->N_vertex; j++)
        {
            if (flag[j]==0 && dist[j]<min)
            {
                min = dist[j];
                k = j;
            }
        }
        // mark ad visited
        flag[k] = 1;

        // correct the shortest distance for the rest node
        for (j = 0; j < g->N_vertex; j++)
        {
            tmp = (g->weights[k][j]==INFINITY ? INFINITY : (min + g->weights[k][j])); // 防止溢出
            if (flag[j] == 0 && (tmp  < dist[j]) )
            {
                dist[j] = tmp;
                prev[j] = k;
            }
        }
    }

    // 打印dijkstra最短路径的结果
    //printf("dijkstra(%s): \n", g->Names[src]);
    //for (i = 0; i < g->N_vertex; i++)
        //printf("  shortest(%s, %s)=%.3f\n", g->Names[src], g->Names[i], dist[i]);
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
}

void single_source_dijkstra_adj_list(L_Graph* g, int src, double* dist, int* prev)
{
    int i, j, k;
    double min;
    double temp;
    int* flag = (int *) malloc(sizeof(int) * g->N_vertex);

    for(i = 0; i < g->N_vertex; i++){
        flag[i] = 0;
        prev[i] = 0;
        dist[i] = get_weight(g, src, i);
    }


    flag[src] = 1;
    dist[src] = 0;

    for(i = 0; i < g->N_vertex; i++){
        min = INFINITY;
        for(j = 0; j < g->N_vertex; j++){
            if(flag[j] == 0 && dist[j] < min){
                min = dist[j];
                k = j;
            }
        }
        flag[k] = 1;

        for(j = 0; j < g->N_vertex; j++){
            double w = get_weight(g, k, j);
            temp = (w == INFINITY ? INFINITY : (min + w));
            if(flag[j] == 0 && (temp < dist[j])){
                dist[j] = temp;
                prev[j] = k;
            }
        }
    }
}

void single_source_dijkstra_adj_list_min_heap(L_Graph* g, int src, double* dist, int* prev){
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
            adjacency_list_node*  node_u = malloc(sizeof(adjacency_list_node));
            node_u->next = NULL;
            node_u = g->adjacency_list_array[u.index].head;
            //printNode(g, u.index);
            //printf("\n");

            while(node_u != NULL)
            {
                int v_id = node_u->nodeID;

                // Insert node v to heap if d[u] + w(u, v) < d[v]
                if(node_u->weight + dist[u.index] < dist[v_id])
                {
                    node v;
                    v.index = v_id;
                    v.weight = dist[u.index] + node_u->weight;
                    Insert(h, v);
                    //printf("%s has been inserted to heap, the weight is %.3f.\n", g->Names[v_id], dist[v_id]);
                    //print_heap(h);
                    dist[v_id] = dist[u.index] + node_u->weight;
                    prev[v_id] = u.index;
                    //printf("%s has been inserted to heap, the weight is %.3f.\n", g->Names[v_id], dist[v_id]);
                }
                //print_heap(h);
                node_u = node_u->next;
            }
        }
    }
}