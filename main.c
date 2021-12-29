#include <math.h>

#include "M_Graph.h"
#include "L_Graph.h"
#include "min_heap.h"
#include "Dijkstra.h"
#include "osm_parser.h"
#include "utilities.h"

int main(int argc, char **argv) 
{
    // without parsing file
    if (argc == 1)
    {
        int choice;
        
        printf("test with testcase or generate random graph? 2 for very big graph 1 for testcase 0 for random graph\n");
        scanf("%d", &choice);
        if(choice == 0)
        {
            // test for dijkstra naif approach with adjacency matrix presentation
            printf("test for Dijkstra algorithm naive approach with adjacency matrix\n\n");

            int nb_vertex, nb_edge;
            double max_weight;

            printf("Enter the number of the vertex in graph\n");
            scanf("%d", &nb_vertex);
            printf("Enter the number of the edge in graph, beware that number should be between 0 and %d\n", nb_vertex * (nb_vertex - 1) / 2);
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

            printf("The result for dijkstra naive in adjacency matrix is below:\n\n");

            print_result(g, src, dist, prev);

            // test for dijkstra with min heap approach with adjacency matrix presentation

            double* dist2 = (double *) malloc(sizeof(double) * nb_vertex);
            int* prev2 = (int *) malloc(sizeof(int) * nb_vertex);

            single_source_dijkstra_min_heap(g, src, dist2, prev2);
            
            printf("The result for dijkstra with min heap in adjacency matrix is below:\n\n");

            print_result(g, src, dist2, prev2);

            if(compare_result(nb_vertex, dist, dist2, prev, prev2))
            {
                printf("those arrays are the same!\n");
            }else
            {
                printf("those arrays are not the same! you need to debug\n");
            }

            // Test for the dijkstra naif approach with adjacency list presentation
            L_Graph* l_g = (L_Graph *) malloc(sizeof(L_Graph));
            Create_L_Graph(l_g, nb_vertex);
            convert_from_M_Graph(l_g, g);
            
            double* dist3 = (double *) malloc(sizeof(double) * nb_vertex);
            int* prev3 = (int *) malloc(sizeof(int) * nb_vertex); 

            single_source_dijkstra_adj_list(l_g, src, dist3, prev3);
            printf("The result for dijkstra naif in adjacency list is below:\n\n");

            printresult(l_g, src, dist3, prev3);

            // test for the correctness
            if(compare_result(nb_vertex, dist2, dist3, prev2, prev3))
            {
                printf("those arrays are the same!\n");
            }else
            {
                printf("those arrays are not the same! you need to debug\n");
            }

            // Test for the dijkstra with min heap approach with adjacency list presentation
            double* dist4 = (double *) malloc(sizeof(double) * nb_vertex);
            int* prev4 = (int *) malloc(sizeof(int) * nb_vertex); 

            single_source_dijkstra_adj_list_min_heap(l_g, src, dist4, prev4);
            printf("The result for dijkstra with min heap in adjacency list is below:\n\n");

            printresult(l_g, src, dist4, prev4);

            // test for the correctness
            if(compare_result(nb_vertex, dist3, dist4, prev3, prev4))
            {
                printf("those arrays are the same!\n");
            }else
            {
                printf("those arrays are not the same! you need to debug\n");
            }


            free(dist);
            free(prev);
            free(dist2);
            free(prev2);
            free(dist3);
            free(prev3);
            free(dist4);
            free(prev4);
            free_graph(g);
            free_L_Graph(l_g);

        }else if(choice == 1)
        {
            // test for dijkstra naif approach with adjacency matrix presentation
            
            
            printf("test for Dijkstra algorithm naive approach with adjacency matrix\n\n");

            M_Graph* g = (M_Graph * ) malloc(sizeof(M_Graph));
            g = read_graph("test/testfile1.txt");
            
            if(g->N_vertex <= 15)
            {
                printf("The adjacency matrix is:\n");
                print_graph(g);
            }
            printf("Run Dijkstra algorithm with naive approach\n");
            double* dist = (double *) malloc(sizeof(double) * g->N_vertex);
            int* prev = (int *) malloc(sizeof(int) * g->N_vertex);

            printf("Enter the start point index, from 0 to %d \n\n", g->N_vertex - 1);
            int src;
            scanf("%d", &src);
            single_source_dijkstra(g, src, dist, prev);

            printf("The result for dijkstra naive in adjacency matrix is below:\n\n");

            print_result(g, src, dist, prev);

            // test for dijkstra with min heap approach with adjacency matrix presentation

            double* dist2 = (double *) malloc(sizeof(double) * g->N_vertex);
            int* prev2 = (int *) malloc(sizeof(int) * g->N_vertex);

            single_source_dijkstra_min_heap(g, src, dist2, prev2);
            
            printf("The result for dijkstra with min heap in adjacency matrix is below:\n\n");

            print_result(g, src, dist2, prev2);

            if(compare_result(g->N_vertex, dist, dist2, prev, prev2))
            {
                printf("those arrays are the same!\n");
            }else
            {
                printf("those arrays are not the same! you need to debug\n");
            }

            // Test for the dijkstra naif approach with adjacency list presentation
            L_Graph* l_g = (L_Graph *) malloc(sizeof(L_Graph));
            Create_L_Graph(l_g, g->N_vertex);
            convert_from_M_Graph(l_g, g);
            
            double* dist3 = (double *) malloc(sizeof(double) * g->N_vertex);
            int* prev3 = (int *) malloc(sizeof(int) * g->N_vertex); 

            single_source_dijkstra_adj_list(l_g, src, dist3, prev3);
            printf("The result for dijkstra naif in adjacency list is below:\n\n");

            printresult(l_g, src, dist3, prev3);

            // test for the correctness
            if(compare_result(g->N_vertex, dist2, dist3, prev2, prev3))
            {
                printf("those arrays are the same!\n");
            }else
            {
                printf("those arrays are not the same! you need to debug\n");
            }

            // Test for the dijkstra with min heap approach with adjacency list presentation
            double* dist4 = (double *) malloc(sizeof(double) * g->N_vertex);
            int* prev4 = (int *) malloc(sizeof(int) * g->N_vertex); 

            single_source_dijkstra_adj_list_min_heap(l_g, src, dist4, prev4);
            printf("The result for dijkstra with min heap in adjacency list is below:\n\n");

            printresult(l_g, src, dist4, prev4);

            // test for the correctness
            if(compare_result(g->N_vertex, dist3, dist4, prev3, prev4))
            {
                printf("those arrays are the same!\n");
            }else
            {
                printf("those arrays are not the same! you need to debug\n");
            }


            free(dist);
            free(prev);
            free(dist2);
            free(prev2);
            free(dist3);
            free(prev3);
            free(dist4);
            free(prev4);
            free_graph(g);
            free_L_Graph(l_g);
        }
    }
    // parsing osm file
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
        //printGraph(g);
        double* dist = (double *) malloc(sizeof(double) * g->N_vertex);
        int* prev = (int *) malloc(sizeof(int) * g->N_vertex);

        //single_source_dijkstra_adj_list(g, 0, dist, prev);

        double* dist2 = (double *) malloc(sizeof(double) * g->N_vertex);
        int* prev2 = (int *) malloc(sizeof(int) * g->N_vertex);
        
        single_source_dijkstra_adj_list(g, 0, dist, prev);
        //printresult(g, 0, dist, prev);
        single_source_dijkstra_adj_list_min_heap(g, 0, dist2, prev2);
        //printresult(g, 0, dist2, prev2);
        if(compare_result(g->N_vertex, dist, dist2, prev, prev2))
        {
            printf("those arrays are the same!\n");
        }else
        {
            printf("those arrays are not the same! you need to debug\n");
        }
        printf("%d\n", !(fabs(dist[0] - dist2[0]) < 1e-9));
    }

    
    return 0;
}