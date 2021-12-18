#include <string.h>
#include <stdlib.h>
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

char* int2char(int n){
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

void Dijkstra_resultat_compare(M_Graph* g, int src, double* dist1, int* prev1, double* dist2, int* prev2){
    printf("\ndijkstra without min heap(%s): \t dijkstra min heap(%s)\n", g->Names[src], g->Names[src]);
    for(int i = 0; i < g->N_vertex; i++){
        int temp = i;
        bool arrived1 = (temp == src);
        bool arrived2 = (temp == src);
        printf("shortest(%s, %s)=%f\tshortest(%s, %s)=%f\n", g->Names[src], g->Names[i], dist1[i], g->Names[src], g->Names[i], dist2[i]);
        if(temp == src){
            printf("the path is %s -> %s\n", g->Names[src], g->Names[temp]);
            printf("the path is %s -> %s\n", g->Names[src], g->Names[temp]);
        }else{
            printf("the path is\t");
            while(!arrived1){
                printf("%s -> %s\t", g->Names[temp], g->Names[prev1[temp]]);
                temp = prev1[temp];
                arrived1 = (temp == src);
                //printf("\n");
            }
            printf("\n");
            printf("the path is\t");
            while(!arrived2){
                printf("%s -> %s\t", g->Names[temp], g->Names[prev2[temp]]);
                temp = prev2[temp];
                arrived2 = (temp == src);
                //printf("\n");
            }
            printf("\n");
        }
    }
}