#include "utilities.h"

FILE *OpenFile(char name[])
{
    printf("Type the input file name:\n");
    fgets(name,100,stdin);
    int l = strlen(name);
    name[l-1] = '\0';

    return fopen(name, "rb");
}