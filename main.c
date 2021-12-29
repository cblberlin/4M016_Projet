#include "M_Graph.h"
#include "L_Graph.h"
#include "min_heap.h"
#include "Dijkstra.h"
#include "osm_parser.h"
#include "utilities.h"

int main(int argc, char **argv) 
{
    // test for dijkstra naif approach with adjacency matrix presentation
	if (argc == 1)
    {
        int choice;
        printf("test with testcase or generate random graph? 1 for testcase 0 for random graph\n");
        scanf("%d", &choice);
        if(choice == 0)
        {
            printf("test for Dijkstra algorithm naive approach with adjacency matrix\n\n");

            int nb_vertex, nb_edge;
            double max_weight;

            printf("Enter the number of the vertex in graph\n");
            scanf("%d", &nb_vertex);
            printf("Enter the number of the edge in graph, beware that number should be between 0 and %d\n", nb_vertex * (nb_vertex - 1));
            scanf("%d", &nb_edge);
            printf("Enter the max_weight possible for the edge\n");
            scanf("%lf", &max_weight);

            M_Graph* g = (M_Graph * ) malloc(sizeof(M_Graph));
            g = init_graph(nb_vertex);
            g = create_graph_random(g, nb_vertex, nb_edge, max_weight);
            if(nb_vertex <= 15)
            {
                printf("The adjacency matrix is:\n");
                print_graph(g);
            }
            printf("Run Dijkstra algorithm with naive approach\n");
            double* dist = (double *) malloc(sizeof(double) * nb_vertex);
            int* prev = (int *) malloc(sizeof(int) * nb_vertex);

            printf("Enter the start point index, from 0 to %d \n\n", nb_vertex - 1);
            int src;
            scanf("%d", &src);
            single_source_dijkstra(g, src, dist, prev);
            printf("The result is below:\n\n");

            print_result(g, src, dist, prev);

            free(dist);
            free(prev);
            free_graph(g);
        }
    }
    else if(argc == 2)
    {
        char* docname;
        docname = argv[1];

        L_Graph* g = (L_Graph*) malloc(sizeof(L_Graph));

        readOSM(g, docname);
        if(g->N_edge && g->N_edge)
        {
            printf("the osm file was loaded successfully and the graph have %d vertices and %d edges\n\n", g->N_vertex, g->N_edge);
        }
        double* dist = (double *) malloc(sizeof(double) * g->N_vertex);
        int* prev = (int *) malloc(sizeof(int) * g->N_vertex);

        //single_source_dijkstra_adj_list(g, 0, dist, prev);
        
        single_source_dijkstra_adj_list_min_heap(g, 0, dist, prev);
    }
    return 0;
}