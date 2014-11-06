/*
 * =====================================================================================
 *
 *       Filename:  tree.c 
 *
 *    Description:  Generates an binary Tree with usage of the famous graphviz toolkit
 *    		            	
 *        Version:  
 *        Created:   
 *       Compiler:  gcc
 *
 *         Author:  Dr4k3   
 *
 * =====================================================================================
 */

//uncomment next line to avoid compilation of assert()

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "tree.h"

//Initialize new tree
TREE*
initTree(char *name1,int length)
{
    TREE* tree = malloc(sizeof(TREE));
    if(tree != NULL){
        //Copy string
        for(int i=0;i<MAX && i<length;i++)
        {
            tree->name[i] = name1[i];
        }
        tree->root = NULL;
        tree->gvc = gvContext();
        tree->graph = agopen(tree->name,Agdirected,NULL);
        agsafeset(tree->graph, "rankdir", "TB", "");
        agsafeset(tree->graph, "overlap", "false", "");
        agsafeset(tree->graph, "packmode", "graph", "");
        agsafeset(tree->graph, "nodesep", "0.5", "");
        agsafeset(tree->graph, "ranksep", "1.5", "");
        agsafeset(tree->graph, "splines", "false", "");
        return tree;
    }
    return NULL;
}

//create new leaf  -- returns NULL on error
LEAF*
newLeaf(CONTENT *v)
{
    LEAF* l = malloc(sizeof(LEAF));
    if(l != NULL){
        l->value = *v;
        l->up = l->left = l->right = NULL;
        return l;
    }
    #ifndef NDEBUG
        fprintf(stderr,"\n --> No valid memory address from malloc() at leaf: %s\n",v->label);
    #endif
    return NULL;
}

//find a specific leaf in the tree. Or find a place for an new one
DIRECTION
findContent(LEAF *root,LEAF **leaf_addr,CONTENT *v,DIRECTION compare(CONTENT neu, CONTENT old))
{

    LEAF *l;
    LEAF *l_old;
    l = root;
    DIRECTION d;

    while(l){
        l_old = l;
        if(compare(*v,l->value) == SELF)
        {
            *leaf_addr = l;
            return SELF;
        }
        else if(compare(*v,l->value) == LEFT)
        {
            l = l->left;
            d = LEFT;
        }
        else if(compare(*v,l->value) == RIGHT)
        {
            l = l->right;
            d = RIGHT;
        }
    }
    *leaf_addr = l_old;
    return d;
}

//Alphabetical sortfuntion
DIRECTION
compare_label(CONTENT neu,CONTENT old)
{
    if(strcmp(neu.label,old.label) == 0)
    {
        return SELF;
    }
    else if(strcmp(neu.label,old.label) < 0)
    {
        return LEFT;
    }
    return RIGHT;
}

//Integervalue based sortfuntion
DIRECTION
compare_integer(CONTENT neu,CONTENT old)
{
    if(atoi(neu.label) == atoi(old.label))
    {
        return SELF;
    }
    else if(atoi(neu.label) < atoi(old.label))
    {
        return LEFT;
    }
    return RIGHT;
}

//Append a leaf in the tree
void
appendLeaf(LEAF *newLeaf, LEAF *where, DIRECTION dir)
{
    if(dir == LEFT)
    {
        where->left = newLeaf;
    }
    else if(dir == RIGHT)
    {
        where->right = newLeaf;
    }
    newLeaf->up = where;
}

// insert a leaf in the tree
int
insertLeaf(TREE *tree, CONTENT *v,DIRECTION compare(CONTENT neu, CONTENT old))
{
    
    LEAF *root = tree->root;

    //Set leaf as root of the tree, if no root exists 
    if(root == NULL)
    {
        if((root = newLeaf(v)) == NULL)
        {
            fprintf(stderr,"\n --> No memory available for leaf\n");
            return 1;
        }
        tree->root = root;
        return 0;
    }
    else
    {
        //else, search for position and append leaf in tree
        LEAF *where;
        DIRECTION d;
        if(((d = findContent(root,&where,v,compare)) != SELF))
        {
            LEAF *new = newLeaf(v);
            if(new != NULL)
            {
                appendLeaf(new,where,d);
                return 0;
            }
            else
            {
                fprintf(stderr,"\n --> No memory available for leaf\n");
                return 1;
            }
        }
        else
        {
            #ifndef NDEBUG
                fprintf(stderr,"\n --> Leaf %s already exists in tree\n",v->label);
            #endif
            return 0;
        }
    }
}

//vanish the tree from memory
void 
eraseTree(TREE *tree)
{
   
    LEAF *root = tree->root;
    free(tree);
    eraseLeafs(root);
}

//Erase a leaf from memory
void 
eraseLeafs(LEAF *root)
{

    //Schaue ob links noch etwas gelöscht werden muss
    if(root->left != NULL)
    {
       eraseLeafs(root->left); 
    }
    
    //Schaue ob rechts noch etwas gelöscht werden muss
    if(root->right != NULL)
    {
        eraseLeafs(root->right); 
    }
    
    //Lösche das aktuelle Element
    #ifndef NDEBUG    
    fprintf(stderr,"\n --> delete: %s\n",root->value.label);
    #endif
    
    free(root);
    root = NULL;

}
