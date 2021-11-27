#include <assert.h>
#include <string.h>
#include <time.h>
#include "M_Graph.h"


/*
create empty graph with n vertices
*/
M_Graph* init_graph(int n){
    M_Graph* g;
    g = (M_Graph*) malloc(sizeof(M_Graph));
    g->N_vertex = n;
    g->N_edge = 0;
    g->Names = (char**) malloc(n * sizeof(char*));
    g->weights = (double**) malloc(n * sizeof(double*));
    for(int i = 0; i < g->N_vertex; i++){
        g->Names[i] = (char*) malloc(sizeof(char));
        g->weights[i] = (double*) malloc(n * sizeof(double));
    }

    /* initialise as no edge in this graph*/
    for(int i = 0; i < g->N_vertex; i++){
        char c = i + '0';
        g->Names[i] = &c;
        for(int j = 0; j < g->N_vertex; j++){
            if(i == j){
                g->weights[i][j] = 0.;
            }
            else{
                g->weights[i][j] = INFINITY;
            }
            
        }
    }
    return g;
}

/*
destroy a graph
*/
void free_graph(M_Graph* g){
    for(int i = 0; i < g->N_vertex; i++){
        free(g->Names[i]);
        free(g->weights[i]);
    }
    free(g->Names);
    free(g->weights);
    free(g);
}

/*
add an edge in graph manually
*/
void add_Edge(M_Graph* g, unsigned int i, unsigned int j, double weight){
    assert(i < g->N_vertex && j < g->N_vertex);
    g->weights[i][j] = weight;
    g->N_edge++;
}

void print_graph(M_Graph *g){
    for(int i = 0; i < g->N_vertex; i++){
        for(int j = 0; j < g->N_vertex; j++){
            printf("%.3f\t", g->weights[i][j]);
        }
        printf("\n");
    }
}

/*
return a graph with n vertices and v edges with random weight of type double
this will be an undirected and connected graph without cycle
*/
M_Graph* create_graph_random(int n, int e, double max_weight){
    assert(e <= n * (n - 1) / 2);
    M_Graph* g = init_graph(n);
    g->N_edge = e;
    srand(time(NULL));
    int count;
    for(count = 0; count < e;){
        int i = rand()%n;
        int j = rand()%n;

        if (i == j){
            continue;
        }
        if(g->weights[i][j] == INFINITY){
            double temp = (max_weight / RAND_MAX) * rand();
            g->weights[i][j] = temp;
            g->weights[j][i] = temp;
            count++;
            //printf("%f\n", temp);
        }
    }

    for(int i = 0; i < n; i++){
        char c = i + '0';
        g->Names[i] = &c;
    }
    return g;
}

int* neihbors(M_Graph* g, int n){
    int* neihbor = (int *) malloc(g->N_vertex * sizeof(int));
    int count = 0;
    for(int i = 0; i < g->N_vertex; i++){

        if(i != n && (g->weights[i][n] != INFINITY)){
            neihbor[count] = i;
            count++;
        }
    }
    return neihbor;
}