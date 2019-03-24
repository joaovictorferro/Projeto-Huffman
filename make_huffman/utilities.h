#ifndef utilities_huffman
#define utilities_huffman 

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

/*
This function reads the name of
the file given by the user and
opens it in binary read mode. The
/0 is put in the last string position
to exclude the /n character. 
*/
FILE *OpenFile(char name[]);

#endif
