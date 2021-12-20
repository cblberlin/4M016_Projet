#include "M_Graph.h"
#include "min_heap.h"
#include "Dijkstra.h"
#include "osm_parser.h"
#include "utilities.h"


int main(){
    /*
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
    //printf("test\n");
    g = create_graph_random(g, n, e, max_weight);
    //printf("The adjacency matrix of graph is: \n");

    //print_graph(g);
    double* dist = (double *) malloc(g->N_vertex * sizeof(double));
    int* prev = (int *) malloc(g->N_vertex * sizeof(int));
    printf("\nresult without min heap\n");
    int src;
    printf("Enter the index of starting point (from 0 to number of vertices - 1):\n");
    scanf("%d", &src);
    single_source_dijkstra(g, src, dist, prev);
    
    double* dist_min_heap = (double *) malloc(g->N_vertex * sizeof(double));
    int* prev_min_heap = (int *) malloc(g->N_vertex * sizeof(int));
    printf("\nresult with min heap\n");
    single_source_dijkstra_min_heap(g,src, dist_min_heap, prev_min_heap);
    
    Dijkstra_resultat_compare(g, src, dist, prev, dist_min_heap, prev_min_heap);
    
    
    free(dist);
    free(dist_min_heap);
    free(prev);
    free(prev_min_heap);
    */
    
    
    int n = 15;
    test_heap(n);
    
    return 0;
}