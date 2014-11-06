/*
 * =====================================================================================
 *
 *       Filename:  dot.c
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
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dotfile.h"

//generate Graph with graphviz
void
generateGraph(TREE *tree, LEAF *curpos)
{
    LEAF *l;
    Agedge_t *e;

    //create left
    if(curpos->left != NULL)
    {
        l = curpos->left;
        e = agedge(tree->graph, curpos->value.node, l->value.node,NULL,TRUE);
        agsafeset(e, "color", "red", "");
        agsafeset(e, "tailport", "l", "");
        agsafeset(e, "headport", "n", "");
    }

    //create right
    if(curpos->right != NULL)
    {
        l = curpos->right;
        e = agedge(tree->graph, curpos->value.node, l->value.node,NULL,TRUE);
        agsafeset(e, "color", "blue", "");
        agsafeset(e, "tailport", "r", "");
        agsafeset(e, "headport", "n", "");
    }

    //go to left leaf
    if(curpos->left != NULL)
    {
        generateGraph(tree,curpos->left);
    }

    //go to right leaf
    if(curpos->right != NULL)
    {
        generateGraph(tree,curpos->right);
    }
}

//write tree to file
void
writeGraphtoDot(TREE *tree,FILE **fp)
{
    gvLayout (tree->gvc, tree->graph, "dot");
    gvRender (tree->gvc, tree->graph, "dot",*fp);
}

//delete dotfile
int
del_DotFile(char *filename)
{
    char delname[MAX];

    strncpy(delname,filename,MAX);

    if(remove(delname) != 0)
    {
        fprintf(stderr,"\n  --> Could not delete %s \n",delname);
        return 1;
    }
    return 0;
}

//call graph via xlib
void*
callGraph(void *name)
{
    char *filename = (char *)name;
    if(system(NULL) == 0)
    {
        fprintf(stderr,"\n  --> No commandline processor available *sry*\n");
        return (void *)1;
    }

    char execute[MAX] = "dot -Txlib ";

    //build execute string
    strcat(execute, filename);
    
    //execute
    if(system(execute) == -1)
    {
        return (void *)0;
    }
    else
    {
        fprintf(stderr,"\n  --> No commandline processor available.\n");
        return (void *)1;
    }
}
