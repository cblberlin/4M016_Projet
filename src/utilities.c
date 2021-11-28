#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "utilities.h"

/*
    this function will convert an integer to a character or string
    ex: 0 -> A
        26 -> AA
*/

const char* ALPHAPHET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

char* int2char(int n){
    if(n < 26){
        char* c = (char* ) malloc(sizeof(char));
        *c = n + 'A';
        return c;
    }
    else{
        int length = (int) (log(n - 26) / log(26) + 1);
        char* c = (char* ) malloc(sizeof(char) * length);
        for(int i = 0; i < length - 1; i++){
           c[i] = ALPHAPHET[n / (int) pow(26, length - i - 1) - 1];
           n %= (int) pow(26, length - i - 1);
        }
        c[length - 1] = ALPHAPHET[n % 26];
        return c;
    }
}

#include "utilities.h"