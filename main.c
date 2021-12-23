#include "M_Graph.h"
#include "L_Graph.h"
#include "min_heap.h"
#include "Dijkstra.h"
#include "osm_parser.h"
#include "utilities.h"

int main(){
    // test dijkstra naive for 

    /*
    int n, e;
    
    double max_weight;
    printf("Enter the number of vertex: ");
    scanf("%d", &n);
    printf("Enter the number of edge, beware this number is between 0 and n(n-1)/2 included: ");
    scanf("%d", &e);

    printf("Enter the max weight of edge: ");
    scanf("%lf", &max_weight);
    */

    /*
    M_Graph* g = (M_Graph*) malloc(sizeof(M_Graph));
    g = init_graph(n);
    g = create_graph_random(g, n, e, max_weight);
    */
    
    
    M_Graph* g = (M_Graph*) malloc(sizeof(M_Graph));
    int n = 16;
    g = init_graph(n);
    
    add_Edge(g, 0, 2, 5.); add_Edge(g, 2, 0, 5.);
    add_Edge(g, 1, 5, 2.); add_Edge(g, 5, 1, 2.);
    add_Edge(g, 1, 4, 3.); add_Edge(g, 4, 1, 3.);
    add_Edge(g, 1, 3, 4.); add_Edge(g, 3, 1, 4.);
    add_Edge(g, 1, 7, 5.); add_Edge(g, 7, 1, 5.);
    add_Edge(g, 4, 5, 1.); add_Edge(g, 5, 4, 1.);
    add_Edge(g, 4, 7, 2.); add_Edge(g, 7, 4, 2.);
    add_Edge(g, 4, 8, 7.); add_Edge(g, 8, 4, 7.);
    add_Edge(g, 3, 8, 16.); add_Edge(g, 8, 3, 16.);
    add_Edge(g, 2, 3, 11.); add_Edge(g, 3, 2, 11.);
    add_Edge(g, 2, 5, 2.); add_Edge(g, 5, 2, 2.);
    add_Edge(g, 2, 6, 3.); add_Edge(g, 6, 2, 3.);
    add_Edge(g, 2, 14, 5.); add_Edge(g, 14, 2, 5.);
    add_Edge(g, 10, 11, 10.); add_Edge(g, 11, 10, 10.);
    add_Edge(g, 11, 12, 2.); add_Edge(g, 12, 11, 2.);
    add_Edge(g, 12, 13, 3.); add_Edge(g, 13, 12, 3.);
    add_Edge(g, 13, 14, 2.); add_Edge(g, 14, 13, 2.);
    add_Edge(g, 14, 15, 3.); add_Edge(g, 15, 14, 3.);
    add_Edge(g, 15, 8, 1.); add_Edge(g, 8, 15, 1.);
    add_Edge(g, 15, 9, 2.); add_Edge(g, 9, 15, 2.);
    
    //printf("The adjacency matrix of graph is: \n");

    //print_graph(g);

    double* dist1 = (double *) malloc(g->N_vertex * sizeof(double));
    int* prev1 = (int *) malloc(g->N_vertex * sizeof(int));

    single_source_dijkstra_min_heap(g, 0, dist1, prev1);

    /*
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
    */

    /*
    free(dist);
    free(dist_min_heap);
    free(prev);
    free(prev_min_heap);
    */
    
    //printf("test adjacency list\n");
    L_Graph* g2 = (L_Graph *) malloc(sizeof(L_Graph *));
    Create_L_Graph(g2, 16);
    //create_L_graph_random(g, n, e, max_weight);
    
    addEdge(g2, 0, 2, 5.); addEdge(g2, 2, 0, 5.);
    addEdge(g2, 1, 5, 2.); addEdge(g2, 5, 1, 2.);
    addEdge(g2, 1, 4, 3.); addEdge(g2, 4, 1, 3.);
    addEdge(g2, 1, 3, 4.); addEdge(g2, 3, 1, 4.);
    addEdge(g2, 1, 7, 5.); addEdge(g2, 7, 1, 5.);
    addEdge(g2, 4, 5, 1.); addEdge(g2, 5, 4, 1.);
    addEdge(g2, 4, 7, 2.); addEdge(g2, 7, 4, 2.);
    addEdge(g2, 4, 8, 7.); addEdge(g2, 8, 4, 7.);
    addEdge(g2, 3, 8, 16.); addEdge(g2, 8, 3, 16.);
    addEdge(g2, 2, 3, 11.); addEdge(g2, 3, 2, 11.);
    addEdge(g2, 2, 5, 2.); addEdge(g2, 5, 2, 2.);
    addEdge(g2, 2, 6, 3.); addEdge(g2, 6, 2, 3.);
    addEdge(g2, 2, 14, 5.); addEdge(g2, 14, 2, 5.);
    addEdge(g2, 10, 11, 10.); addEdge(g2, 11, 10, 10.);
    addEdge(g2, 11, 12, 2.); addEdge(g2, 12, 11, 2.);
    addEdge(g2, 12, 13, 3.); addEdge(g2, 13, 12, 3.);
    addEdge(g2, 13, 14, 2.); addEdge(g2, 14, 13, 2.);
    addEdge(g2, 14, 15, 3.); addEdge(g2, 15, 14, 3.);
    addEdge(g2, 15, 8, 1.); addEdge(g2, 8, 15, 1.);
    addEdge(g2, 15, 9, 2.); addEdge(g2, 9, 15, 2.);
    
    
    //printGraph(g2);

    double* dist2 = (double *) malloc(g2->N_vertex * sizeof(double));
    int* prev2 = (int *) malloc(g2->N_vertex * sizeof(int));

    single_source_dijkstra_adj_list_min_heap(g2, 0, dist2, prev2);
    
    return 0;
}