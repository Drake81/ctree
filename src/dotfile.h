/*
 * =====================================================================================
 *
 *       Filename:  dot.h
 *
 *    Description:  All "dot" related functions 
 *    			
 *        Version:  
 *        Created:   
 *       Compiler:  gcc
 *
 *         Author:  Dr4k3
 *
 * =====================================================================================
 */

#ifndef dot_INCLUDED
#  define dot_INCLUDED

#include <graphviz/gvc.h>
#include "md5/md5.h"
#include "tree.h"

//#ifndef MAX 
    #define MAX 50
//#endif

#define NDEBUG

//generate Graph with graphviz
void generateGraph(TREE *tree, LEAF *curpos);

//write tree to file
void writeGraphtoDot(TREE *tree,FILE **fp);

//delete dotfile
int del_DotFile(char *filename);

//call graph via xlib
void *callGraph(void *);

#endif /* dot_INCLUDED */
