#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
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
           //printf("%c\n", c[i]);
           n %= (int) pow(26, length - i - 1);
        }
        c[length - 1] = ALPHAPHET[n % 26];
        return c;
    }
}
 
int main()
{
    int n;
 
    scanf("%d", &n);
    char* res = (char* ) malloc(sizeof(char));
    //res = int2char(n);
    //printf("%s\n", res);
    printf("%d\n", (int) (log(n) / log(26) + 1));
    char** names = (char**) malloc(n * sizeof(char*));
    for(int i = 0; i < n; i++){
       names[i] = (char*) malloc(sizeof(char));
       names[i] = int2char(i);
       printf("%s\n", names[i]);
    }
    res = int2char(n);
    //printf("%s\n", res);
    return 0;
}