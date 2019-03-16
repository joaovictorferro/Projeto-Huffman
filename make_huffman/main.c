#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include "hash.h"
#include "p_queue.h"
#include "tree.h"
#include "compress.h"
#include "decompress.h"

void header()
{
  printf("|------------------------------------------------------------------------------------------------|\n");
  printf("| **     **  **    **  ********   ********       **       **               **        ****     ** |\n");
  printf("| **     **  **    **  **         **           ** **    ** **            ** **       ** **    ** |\n");
  printf("| **     **  **    **  **         **          **    ** **   **          **   **      **  **   ** |\n");
  printf("| *********  **    **  ********   ********   **      **      **        *********     **   **  ** |\n");
  printf("| **     **  **    **  **         **        **                **      **       **    **    ** ** |\n");
  printf("| **     **  **    **  **         **       **                  **    **         **   **     **** |\n");
  printf("| **     **  ********  **         **      **                    **  **           **  **       ** |\n");
  printf("|                                                                                                |\n");
  printf("|                       Joao Victor - Lucas Massa - William Philippe                             |\n"); 
  printf("|------------------------------------------------------------------------------------------------|\n");
}

void options(){
  printf("Choose an option by typing the corresponding number:\n");
  printf("(1) -> COMPRESS.\n");
  printf("(2) -> DECOMPRESS.\n");
  printf("(3) -> EXIT PROGRAM.\n");
}

void main()
{

  int choice, loop = 1;
  
  while(loop)
  {

    system("clear || cls");
    header();
    options();

    scanf("%d", &choice);
    getchar();

    switch (choice)
    {

      case 1:
        compressMain();
        break;

      case 2:
        decompressMain();
        break;

      case 3:
        loop = 0;
        break;

      default:
        break;
    }
  }
}