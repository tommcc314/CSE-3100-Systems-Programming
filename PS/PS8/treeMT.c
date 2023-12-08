#include "treeMT.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

Tree* makeEmptyTree()
{
    /* TODO: 
     * Create a new Tree, setting the root to NULL. Initialize any necessary mutexes. 
     * Return Tree*.
    */
   Tree* nt = malloc(sizeof(Tree));
   nt->root = NULL;
   pthread_mutex_init(&nt->lock,NULL);
   return nt;
}
void insertIntoTree(Tree* t, int val)
{
    /* TODO: 
     * This function should construct a new Node, traverse the BST to find the correct insertion location, and insert it. 
     * If there is already a node with that value, nothing needs to be inserted.
     * Use mutexes to prevent threads from interfering with one another. 
     * Read the description in the pdf for more instructions.  
    */
    TNode* newnode = malloc(sizeof(TNode));
    newnode->val = val;
    pthread_mutex_init(&newnode->lock,NULL);
    newnode->left = NULL, newnode->right = NULL;
    pthread_mutex_lock(&t->lock); // lock tree to get root safely
    TNode *cur = t->root, *next = NULL;
    if (!cur) {
        t->root = newnode;
        pthread_mutex_unlock(&t->lock);
        return;
    }
    pthread_mutex_lock(&cur->lock); // lock root node, then unlock tree
    pthread_mutex_unlock(&t->lock);
    while (1) {
        // if empty spot is found for newnode, insert node and unlock cur
        if (val < cur->val) {
            if (!cur->left) {
                cur->left = newnode;
                pthread_mutex_unlock(&cur->lock);
                return;
            }
            else next = cur->left;
        }
        else {
            if (!cur->right) {
                cur->right = newnode;
                pthread_mutex_unlock(&cur->lock);
                return;
            }
            else next = cur->right;
        }
        // otherwise, lock the child node then unlock the parent
        pthread_mutex_lock(&next->lock);
        pthread_mutex_unlock(&cur->lock);
        cur = next;
    }
}


void printTreeAux(TNode* root)
{
    if (root == NULL)
        return;
    else {
        printf("(");
        printTreeAux(root->left);
        printf(" %d ",root->val);
        printTreeAux(root->right);
        printf(")");      
    }
}

void printTree(Tree* t)
{
    printTreeAux(t->root);
}

void destroyTreeAux(TNode* root)
{
    if(root != NULL){
        destroyTreeAux(root->left);
        destroyTreeAux(root->right);
        pthread_mutex_destroy(&root->lock);
        free(root);
    }
}

void destroyTree(Tree* t)
{
    destroyTreeAux(t->root);
    pthread_mutex_destroy(&t->lock);
    free(t);
}


