#include <assert.h>
#include <string.h>
#include <time.h>
#include "L_Graph.h"
#include "utilities.h"


/*
    Create an empty graph
    input: int n: the number of vertex
*/
void Create_L_Graph(L_Graph* g, int n) 
{

    g->N_vertex = n;
    g->N_edge = 0;

    /* Create an array of adjacency lists*/
    g->adjacency_list_array = (adjacency_list *) malloc(n * sizeof(adjacency_list));
    g->Names = (char **) malloc(sizeof(char *) * n);
    for(int i = 0; i < n; i++) 
    {
        g->adjacency_list_array[i].head = NULL;
        g->adjacency_list_array[i].nb_members = 0;
        g->Names[i] = (char *) malloc(sizeof(char));
        g->Names[i] = int2char(i);
    }
}

/*
    destroy L_graph
*/
void free_L_Graph(L_Graph* g)
{
    if(g != NULL)
    {
        if(g->adjacency_list_array != NULL)
        {
            for(int i = 0; i < g->N_vertex; i++)
            {
                adjacency_list_node* item = g->adjacency_list_array[i].head;

                while (item != NULL)
                {
                    adjacency_list_node* temp = item->next;
                    free(item);
                    item = temp;
                }
                
            }
        }

        free(g->adjacency_list_array);
        free(g);
    }
}

/*
    add an edge to graph, here we suppose that our graph is undirected
*/
void addEdge(L_Graph* g, int src, int dest, double weight)
{
    // Create a new adjacency list node
    adjacency_list_node* newNode = (adjacency_list_node *) malloc(sizeof(adjacency_list_node));
    newNode->nodeID = dest;
    newNode->weight = weight;

    // Add it in place of the head of the list
    newNode->next = g->adjacency_list_array[src].head;

    g->adjacency_list_array[src].head = newNode;
    g->adjacency_list_array[src].nb_members++;
    g->N_edge++;
}

/*
    presentation in linked list of weighted graph
*/
void printNode(L_Graph* g, int n)
{
    adjacency_list_node* l = g->adjacency_list_array[n].head;
    printf("\n%s: ", g->Names[n]);
    while (l != NULL)
    {
        printf("%s (%.3f) -> ", g->Names[l->nodeID], l->weight);
        l = l->next;
    }
    printf("NULL\n");
    
}

/*
    print graph in terminal using linked list form
*/
void printGraph(L_Graph* g) 
{
  for (int i = 0; i < g->N_vertex; i++) 
  {
      printNode(g, i);
  }
}

/*
    create graph using linked list
*/
void create_L_graph_random(L_Graph* g, int n, int e, double max_weight)
{
    assert(e <= n * (n - 1));
    assert(g->N_edge <= e);
    assert(g->N_vertex == n);
    srand(time(NULL));
    // count edge number
    int count;

    // loop to create i, j
    for(count = 0; count < e;)
    {
        int i = rand() % n;
        int j = rand() % n;
        
        // ignore cycle
        if(i == j)
        {
            continue;
        }

        // create random number < max weight and we suppose that's undirected graph
        double temp = (max_weight / RAND_MAX) * rand();
        addEdge(g, i, j, temp);
        addEdge(g, j, i, temp);
        count++;
    }
}

/*
    return the weight between node i and node j
    if there is no such edge between i and j
    return INFINIFY
*/
double get_weight(L_Graph* g, int i, int j)
{
    adjacency_list_node* temp = g->adjacency_list_array[i].head;
    while (temp != NULL)
    {
        //printf("%.3f\n", temp->weight);
        if(j != temp->nodeID )
        {
            temp = temp->next;
        }else{
            return temp->weight;
        }
    }
    return INFINITY;
    
}

L_Graph* readGraph(char* filename)
{
    
}