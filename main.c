#include "M_Graph.h"
#include "min_heap.h"
#include "Dijkstra.h"
#include "osm_parser.h"


int main(){

    int n, e;
    double max_weight;
    printf("Enter the number of vertex: ");
    scanf("%d", &n);
    printf("Enter the number of edge, beware this number is between 0 and n(n-1)/2 included: ");
    scanf("%d", &e);

    printf("Enter the max weight of edge: ");
    scanf("%lf", &max_weight);
    M_Graph* g = (M_Graph*) malloc(sizeof(M_Graph));
    g = init_graph(n);
    printf("test\n");
    g = create_graph_random(g, n, e, max_weight);
    //printf("The adjacency matrix of graph is: \n");

    //print_graph(g);
    double* dist = (double *) malloc(g->N_vertex * sizeof(double));
    int* prev = (int *) malloc(g->N_vertex * sizeof(int));
    single_source_dijkstra(g, 0, dist, prev);
    
    return 0;
}