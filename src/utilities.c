#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#include "utilities.h"

/*
    this function will convert an integer to a character or string
    ex: 0   -> A
        26  -> AA
        702 -> AAA
    this will be useful for naming the vertex of a random graph
    with a great number of vertices
*/

const char* ALPHAPHET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

char* int2char(int n)
{
    if(n < 26){
        char* c = (char* ) malloc(sizeof(char));
        *c = n + 'A';
        return c;
    }
    else{
        int length = (int) (log(n) / log(26) + 1);
        char* c = (char* ) malloc(sizeof(char) * length);
        for(int i = 0; i < length - 1; i++){
           c[i] = ALPHAPHET[n / (int) pow(26, length - i - 1) - 1];
           n %= (int) pow(26, length - i - 1);
        }
        c[length - 1] = ALPHAPHET[n % 26];
        return c;
    }
}

void find_path(L_Graph*g, int src, int dest, int* prev)
{
    int count = 2;
    char** path = (char **) malloc(sizeof(char *) * count);
    for(int i = 0; i < count; i++)
    {
        path[i] = (char *) malloc(sizeof(char));
    }
    path[0] = g->Names[dest];

    bool arrived = (dest == src);
    if(dest == src)
    {
        printf("the path is %s %s", g->Names[src], g->Names[dest]);
    }else
    {
        printf("the path is");
        while(!arrived)
        {
            path[count - 1] = g->Names[prev[dest]];
            dest = prev[dest];
            arrived = (dest == src);
            count++;
            path = realloc(path, sizeof(char **) * count);
            path[count - 1] = (char *) malloc(sizeof(char));
        }
        for(int j = count - 1; j >= 0; j--)
        {
            printf("%s ", path[j]);
        }
    }
}

void findpath(M_Graph* g, int src, int dest, int* prev)
{
    int count = 2;
    char** path = (char **) malloc(sizeof(char *) * count);
    for(int i = 0; i < count; i++)
    {
        path[i] = (char *) malloc(sizeof(char));
    }
    path[0] = g->Names[dest];

    bool arrived = (dest == src);
    if(dest == src)
    {
        printf("the path is %s %s", g->Names[src], g->Names[dest]);
    }else
    {
        //printf("%d", dest);
        printf("the path is");
        while(!arrived)
        {
            path[count - 1] = g->Names[prev[dest]];
            dest = prev[dest];
            arrived = (dest == src);
            count++;
            path = realloc(path, sizeof(char **) * count);
            path[count - 1] = (char *) malloc(sizeof(char));
        }
        for(int j = count - 1; j >= 0; j--)
        {
            printf("%s ", path[j]);
        }
    }
}

void Dijkstra_resultat_compare(M_Graph* g, int src, double* dist1, int* prev1, double* dist2, int* prev2){
    printf("\ndijkstra without min heap(%s): \t dijkstra min heap(%s)\n", g->Names[src], g->Names[src]);
    for(int i = 0; i < g->N_vertex; i++){
        
        printf("shortest(%s, %s)=%f\tshortest(%s, %s)=%f\n", g->Names[src], g->Names[i], dist1[i], g->Names[src], g->Names[i], dist2[i]);
        findpath(g, src, i, prev1);
        printf("\n");
        findpath(g, src, i, prev2);
        printf("\n");
    }
}


void Dijkstra_resultat_compare2(L_Graph* g, int src, double* dist1, int* prev1, double* dist2, int* prev2){
    printf("\ndijkstra without min heap(%s): \t dijkstra min heap(%s)\n", g->Names[src], g->Names[src]);
    for(int i = 0; i < g->N_vertex; i++){
        
        printf("shortest(%s, %s)=%f\tshortest(%s, %s)=%f\n", g->Names[src], g->Names[i], dist1[i], g->Names[src], g->Names[i], dist2[i]);
        find_path(g, src, i, prev1);
        printf("\n");
        find_path(g, src, i, prev2);
        printf("\n");
    }
}

void print_result(M_Graph*g, int src, double* dist, int* prev)
{
    for(int i = 0; i < g->N_vertex; i++){
        printf("shortest(%s, %s)=%f\n", g->Names[src], g->Names[i], dist[i]);
        findpath(g, src, i, prev);
        //printf("%lf\t%d", dist[i], prev[i]);
        printf("\n\n");
    }
}

void printresult(L_Graph*g, int src, double* dist, int* prev)
{
    for(int i = 0; i < g->N_vertex; i++){
        printf("shortest(%s, %s)=%f\n", g->Names[src], g->Names[i], dist[i]);
        find_path(g, src, i, prev);
        //printf("%lf\t%d", dist[i], prev[i]);
        printf("\n\n");
    }
}

bool compare_result(int n, double* dist1, double* dist2, int* prev1, int* prev2)
{
    for(int i = 0; i < n; i++)
    {
        if( (dist1[i] == INFINITY && dist2[i] == INFINITY) || (fabs(dist1[i] - dist2[i]) < 1e-9)  || (prev1[i] != prev2[i]))
        {
            printf("prev1[%d] = %d, prev2[%d] = %d\n", i, prev1[i], i, prev2[i]);
            printf("dist1[%d] = %f, dist2[%d] = %f\n", i, dist1[i], i, dist2[i]);
            printf("%d %d %d\n", !(dist1[i] == INFINITY && dist2[i] == INFINITY), !(fabs(dist1[i] - dist2[i]) < 1e-9), (prev1[i] != prev2[i]));
            return false;
        }
        
    }
    return true;
}