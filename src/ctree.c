/*
 * =====================================================================================
 *
 *       Filename:  ctree.c 
 *
 *    Description:  Generates an binary Tree with usage of the famous graphviz toolkit
 *    		            	
 *        Version:  stable
 *        Created:   
 *       Compiler:  gcc
 *
 *         Author:  Dr4k3   
 *
 * =====================================================================================
 */

//uncomment next line to avoid compilation of assert()
#define NDEBUG

#define MAX 50

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <graphviz/gvc.h>
#include <pthread.h>

#include "mystuff.h"
#include "tree.h"
#include "dotfile.h"
#include "md5/md5.h"


//main
int
main()
{

    char *filename;
    filename = tmpnam(NULL);
    FILE *fp = fopen(filename,"w");
    if(fp != NULL)
    {
        
        //Initialisation MD5 function
        md5_state_t state;
        md5_byte_t digest[16];
        CONTENT value;

        //Initialisation tree
        TREE *tree = initTree("tree",sizeof("tree"));
        if(tree == NULL)
        {
            fprintf(stderr,"    >> Could not initialize tree structure.\n");
        }

        ///////////////////////////////////////////////////////////////
        //  menu  

        int N = 0;
        int sortfunc = 0;

        //return value scanf
        int re;

        //Which sort-function?
        do
        {
            printf("\n========================");
            printf("\n[1] Alphabetical");
            printf("\n[2] Numerous\n");
            printf("\nWhich kind of sort?: ");
            re = scanf("%1d",&sortfunc);
            lstdin();
        }while(re != 1 || sortfunc < 1 || sortfunc > 2);
        assert(re != 1 || sortfunc > 1 || sortfunc < 3);
        printf("\n");

        //Amount of Datasets (Leafs)
        do
        {
            printf("\n========================");
            printf("\nHow many [data]leafs in the tree?: ");
            re = scanf("%5d",&N);
            lstdin();
        }while(re < 1 || N <= 0);
        assert(re > 0 || N > 0);

        ////////////////////////////////////////////////////////////////////////////
        //Read Data from STDIN and build the tree simultaneously
        for(int i=0;i<N;i++)
        {

            printf("\n  Value of the %d. leaf: ",i+1);

            char buf[MAX];
            fgets(buf,MAX,stdin);
            sscanf(buf,"%s",value.label);

            if(sortfunc == 2)
            {
                fprintf(stderr,"    >> Input recognized as \"%d\".\n",atoi(value.label));
            }

            //Generate hash
            md5_init(&state);
            md5_append(&state, (const md5_byte_t *)value.label, strlen(value.label));
            md5_finish(&state, digest);

            //copy hash to string
            for(int j=0;j<16;j++)
            {
                value.hash[j] = digest[j];
            }

            //create new node --> [Should be realized as function]
            value.node = agnode(tree->graph, value.label);
            char pstring[MAX];
            snprintf(pstring,MAX,"{%s | {<l> left | <r> right}}",value.label);
            //printf("%s",pstring);
            agsafeset(value.node, "label", pstring, "");
            agsafeset(value.node, "shape", "record", "");


            switch(sortfunc)
            {

                case 1: re = insertLeaf(tree,&value,&compare_label); break;

                case 2: re = insertLeaf(tree,&value,&compare_integer); break;

                default: printf("\nNo valid input. Will sort by alphabetically.\n"); break;
            }
            if(re > 0)
            {// In case of errors
                printf("\n --> Could not set \"%s\" as leaf.\n",value.label);
                int err=0;
                do
                {
                    printf("\n========================");
                    printf("\n[1] Enter value again an retry");
                    printf("\n[2] Skip current leaf");
                    printf("\n[3] Stop program\n");
                    printf("\nWhich Number?: ");
                    re = scanf("%1d",&err);
                    lstdin();
                }while(re != 1 || err < 1 || err > 3);
                assert(re != 1 || err > 1 || err < 4);
                printf("\n");

                switch(err)
                {

                    case 1: N--;break;

                    case 2: break;

                    case 3: eraseTree(tree); fclose(fp); del_DotFile(filename); exit(EXIT_FAILURE); break;
                }
            }
        }


        //generate graph with graphviz
        generateGraph(tree,tree->root);

        //write graph to file
        writeGraphtoDot(tree,&fp);

        pthread_t thread1; 
        int rc;

        /* create thread 1 */
        rc = pthread_create( &thread1, NULL, &callGraph, filename ); 
        if( rc != 0 )
        {
            printf("Could not generate thread\n");
            return EXIT_FAILURE; 
        }

        //We will come to the end now
        //Clear the memory and delete all files
        pthread_join( thread1, NULL );
        eraseTree(tree);
        fclose(fp);
        del_DotFile(filename);

        printf("BYEBYE!\n");

        exit(EXIT_SUCCESS);
    }
    exit(EXIT_FAILURE);
}//End of main
