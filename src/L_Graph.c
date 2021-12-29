#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "L_Graph.h"
#include "utilities.h"
#include "osm_parser.h"

#ifdef INFINITY

#endif

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
    so when we create file from file don't forget to -1 because the edge number is defined at the beginning
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

/*
    read simple graph file
    nb_vertex nb_edge
    src dest w
    .
    .
    .
    src dest w
*/
L_Graph* readGraph(char* filename)
{
    L_Graph* g = (L_Graph*) malloc(sizeof(L_Graph));
    FILE* f;
    f = fopen(filename, "r");
    if(f == NULL)
    {
        printf("can't open file");
        exit(EXIT_FAILURE);
    }
    char line[255];
    int count = 0;
    //printf("test\n");
    //fgets(line, 255, f)
    while(fgets(line, 255, f) != NULL)
    {

        if(count == 0)
        {
            char *token = strtok(line, " ");
            int n;
            int v;
            n = atoi(token);
            //printf("n = %d", n);
            token = strtok(NULL, " ");
            v = atoi(token);
            //printf("v = %d", v);
            g->N_vertex = n;
            Create_L_Graph(g, n);
            g->N_edge = v;
            count++;
        }else
        {
            int a, b;
            double w;
            char *eptr;
            char *token = strtok(line, " ");
            a = atoi(token);
            token = strtok(NULL, " ");
            b = atoi(token);
            token = strtok(NULL, " ");
            w = strtod(token, &eptr);
            addEdge(g, a, b, w);
            g->N_edge--;

            addEdge(g, b, a, w);
            g->N_edge--;
            count++;
        }
    }
    fclose(f);
    return g;
}

void convert_from_M_Graph(L_Graph* g1, M_Graph* g2)
{
    g1->N_edge = g2->N_edge;
    g1->N_vertex = g2->N_vertex;
    g1->Names = g2->Names;

    for(int i = 0; i < g2->N_vertex; i++)
    {
        for(int j = i; j < g2->N_vertex; j++)
        {
            if(g2->weights[i][j] != INFINITY && i != j)
            {
                //printf("check!\n");
                addEdge(g1, i, j, g2->weights[i][j]);
                g1->N_edge--;
                addEdge(g1, j, i, g2->weights[i][j]);
                g1->N_edge--;
            }
        }
    }
}

/*
    Create L_Graph from an osm file
*/
void readOSM(L_Graph* g, char* filename)
{
    xmlDocPtr doc;

	doc = xmlParseFile(filename);;

    if(doc == NULL)
    {
        fprintf(stderr,"Document not parsed successfully. \n");
        return;
    }

    // get nodes information in osm file
    xml_node_t** nodes = (xml_node_t **) malloc(sizeof(xml_node_t*));
    nodes[0] = (xml_node_t *) malloc(sizeof(xml_node_t));
    int nb_node;
    getAllNodes(doc, nodes, &nb_node);

    // create L_graph with n nodes and fill the name with node id
    
    Create_L_Graph(g, nb_node);

    for(int i = 0; i < nb_node; i++)
    {
        strcpy(g->Names[i], nodes[0][i].id);
    }

    // get edge information in osm file
    xml_way_t** ways = (xml_way_t **) malloc(sizeof(xml_way_t*));

    int nb_way = 0;
    
    getAllWay(doc, ways, &nb_way);

    // create hash table to fill in L_graph
    xml_node_ht *node_temp1, *node_temp2, *nodes_ht = NULL;
    
    for(int i = 0; i < nb_node; i++)
    {
        node_temp1 = (xml_node_ht *) malloc(sizeof(*node_temp1));
        node_temp1->ref = nodes[0][i].id;
        node_temp1->index = i;
        HASH_ADD_KEYPTR( hh, nodes_ht, node_temp1->ref, strlen(node_temp1->ref), node_temp1 );
    }

    // traverse all ways and for each way, get the index of ref in the graph
    for(int i = 0; i < nb_way; i++)
    {
        //printf("way id is %s, nb of ref is %d\n", ways[0][i].id, ways[0][i].nb_ref);
        for(int j = 0; j < ways[0][i].nb_ref - 1; j++)
        {
            node_temp2 = (xml_node_ht *) malloc(sizeof(*node_temp2));
            HASH_FIND_STR( nodes_ht, ways[0][i].ref[j], node_temp1);
            HASH_FIND_STR( nodes_ht, ways[0][i].ref[j + 1], node_temp2);
            if (node_temp1 && node_temp2)
            {
                double w = distance(nodes[0][node_temp1->index], nodes[0][node_temp2->index]);
                addEdge(g, node_temp1->index, node_temp2->index, w);
                addEdge(g, node_temp2->index, node_temp1->index, w);
            }
        }
    }
}