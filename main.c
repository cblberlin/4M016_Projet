#include "M_Graph.h"
#include "binary_heap.h"
#include "Dijkstra.h"
#include "osm_parser.h"


int main(){
    //int n = 5;
    /*M_Graph* g = init_graph(n);
    print_graph(g);
    free(g);*/
    int n = 10;
    int e = n * (n - 1) / 2;
    double max_weight = 20.;
    M_Graph* g = create_graph_random(n, e, max_weight);
    printf("The adjacency matrix of graph is: \n");
    print_graph(g);
    double* dist = (double *) malloc(g->N_vertex * sizeof(double));
    int* prev = (int *) malloc(g->N_vertex * sizeof(int));
    single_source_dijkstra(g, 0, dist, prev);
    return 0;
}