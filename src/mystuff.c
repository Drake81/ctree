/*
 * =====================================================================================
 *
 *       Filename:  mystuff.c
 *
 *    Description:  Eingige hilfreiche Funktionen 
 *    			
 *        Version:  
 *        Created:   
 *       Compiler:  gcc
 *
 *         Author:  Dr4k3
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "mystuff.h"

///////////////////////////////////////////////////////////
// Delete STDIN buffer 
void
lstdin(void)
{
    int zeichen;

    while ((zeichen=getc(stdin)) != EOF)
    {
        if (zeichen == '\n')
        {
            break;
        }
    }
}

//Initialise a array with 0 or spaces
void
ainit(void *a,int size_of_array,int size_of_typ)
{
  if(size_of_typ == sizeof(char))
  {
    memset(a, ' ', size_of_array-1); // ausnullen
  }
  else
  {
    memset(a, 0, size_of_array); // ausnullen
  }
}

//Print array
int
aout(void *array,int size_of_array,int size_of_typ)
{
    int nelements = size_of_array / size_of_typ;

    switch(size_of_typ)
    {
        case (sizeof(int)):
           //printf("INT\n");
           for(int i=0;i<nelements;i++)
           {
                printf("%i ",*(int *)array);
                array+=size_of_typ;
           }
           break;
        
        case (sizeof(short)): 
           //printf("SHORT\n");
           for(int i=0;i<nelements;i++)
           {
                printf("%i ",*(short * )array);
                array+=size_of_typ;
           }
           break;

        case (sizeof(double)): 
           //printf("DOUBLE\n");
           for(int i=0;i<nelements;i++)
           {
                printf("%lf ",*(double *)array);
                array+=size_of_typ;
           }
           break;

        case (sizeof(char)): 
           printf("%s ",(char *)array);
           break;

        default:
           printf("Fehler: Datentyp nicht bekannt!!\n");
           return size_of_typ;
    }
    printf("\n");
    return 0;
}

//print integer matrix
void
mout(int *matrix,int zeilenl,int spaltenl)
{
    for(int i=0;i<zeilenl;i++)
    {
        for(int j=0;j<spaltenl;j++)
        {
            printf("%d ",*matrix);
            matrix++;
        }
        printf("\n");
    }
    printf("\n");
}
