/*
 * =====================================================================================
 *
 *       Filename:  tree.h
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

#ifndef tree_INCLUDED
#  define tree_INCLUDED

#ifndef MAX
    #define MAX 50
#endif

#include <graphviz/gvc.h>

#include "md5/md5.h"

#define NDEBUG

// data structure
typedef struct content{
   char label[MAX];
   Agnode_t *node;
   md5_byte_t hash[16];
}CONTENT;

// leaf structure
typedef struct leaf{
   CONTENT value;
   struct leaf *up, *left, *right;
} LEAF;

// tree structure
typedef struct tree{
    char name[MAX];
    GVC_t *gvc;
    Agraph_t *graph;
    LEAF *root;
} TREE;

// Which direction ? 
typedef enum{
   LEFT = -1,
   SELF = 0,
   RIGHT = 1
} DIRECTION;

//Initialize new tree
TREE *initTree(char *name,int length);

//create new leaf  -- returns NULL on error
LEAF *newLeaf(CONTENT *v);

//find a specific leaf in the tree. Or find a place for an new one
DIRECTION findContent(LEAF *root,LEAF **leaf_addr,CONTENT *v,DIRECTION compare(CONTENT neu, CONTENT old));

//Alphabetical sortfuntion
DIRECTION compare_label(CONTENT neu,CONTENT old);

//Integervalue based sortfuntion
DIRECTION compare_integer(CONTENT neu,CONTENT old);

//Append a leaf in the tree
void appendLeaf(LEAF *newLeaf, LEAF *where, DIRECTION dir);

// insert a leaf in the tree
int insertLeaf(TREE *tree, CONTENT *v,DIRECTION compare(CONTENT neu, CONTENT old));

//vanish the tree from memory
void eraseTree(TREE *tree);

//Erase a leaf from memory
void eraseLeafs(LEAF *root);

#endif /* tree_INCLUDED */
