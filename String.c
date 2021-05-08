#include "./headers/String.h"

str constructStr(char *s){
    int i;
    while (s[i] != 0)
    {
        i++;
    }
    str ret;
    ret.addr = s;
    ret.length = i;
    return ret;
}