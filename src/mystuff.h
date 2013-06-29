/*
 * =====================================================================================
 *
 *       Filename:  mystuff.h
 *
 *    Description:  Some helpfully functions
 *    			
 *        Version:  
 *        Created:   
 *       Compiler:  gcc
 *
 *         Author:  Dr4k3
 *
 * =====================================================================================
 */
#ifndef mystuff_INCLUDED
#  define mystuff_INCLUDED

// Delete STDIN buffer 
void lstdin(void);

//Initialise a array with 0 or spaces
void ainit(void *a,int size_of_array,int size_of_typ);

//Print array
int aout(void *array,int size_of_array,int size_of_typ);

//print integer matrix
void mout(int *matrix,int zeilenl,int spaltenl);

#endif /* mystuff_INCLUDED */
