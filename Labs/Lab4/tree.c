#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct TNode{
    char* val;
    struct TNode* left;
    struct TNode* right;
} TNode;

TNode* makeEmptyTree()
{
    return NULL;
}

TNode* insertIntoTree(TNode* root,char* string)
{
    /*
    TODO: Insert the string into the tree. First, check if the root is NULL. If it is, then create a new TNode, copy the string into it, and return the pointer to the new TNode. 

    If root is not NULL, then compare root->val and string using strcmp. If root->val < string, then call insertIntoTree again on root->left. Keep in mind that root->left might be NULL. If root->val > string, then call insertIntoTreeAgain on root->right. Again, root->right might be NULL. If root->val is equal to string, then the string is already in the tree, and you don't need to do anything. In any case, return root.
    */
    if (!root) {
        TNode* newNode = malloc(sizeof(TNode));
        newNode->val = malloc(200 * sizeof(char));
        strcpy(newNode->val, string);
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }
    if (strcmp(string, root->val) <= 0) {
        root->left = insertIntoTree(root->left, string);
        return root;
    }
    else {
        root->right = insertIntoTree(root->right, string);
        return root;
    }
}

TNode* searchTree(TNode* root, char* string)
{
    if(root){
    /*
      TODO: Search the tree for the string. First, use strcmp to compare root->val to string. 

      If string == root->val, return the root. 

      If string < root->val, then call searchTree on the right child of root.

      If string > root->val, then call searchTree on the left child of root.
    */
        int comp = strcmp(string, root->val);
        if (comp == 0)
            return root;
        else if (comp < 0)
            return searchTree(root->left, string);
        else
            return searchTree(root->right, string);
    } else
    return NULL;
}

void printTree(TNode* root)
{
    if (root == NULL)
        return;
    else {
        printf("(");
        printTree(root->left);
        printf(" %s ",root->val);
        printTree(root->right);
        printf(")");      
    }
}

void destroyTree(TNode* root)
{
    /*
    TODO: Free the nodes in the tree, and the strings stored in those nodes. This is easier to do recursively. 
    */
    if (root->left)
        destroyTree(root->left);
    if (root->right)
        destroyTree(root->right);
    free(root->val);
    free(root);
    return;
}




int main(int argc, char* argv[])
{
    if(argc != 2){
        printf("Usage: ./tree wordList\n");
        return 1;
    }
    TNode* tree = makeEmptyTree();
    /*
        TODO: The path to the file containing the words is stored in argv[1]. Call fopen to open it. 
    */
    FILE* file = fopen(argv[1], "r");
    char word[200];
    size_t length;
    /*
        TODO: Use fscanf to read a word at a time from the file, and call insertIntoTree to insert the word into the tree.
    */
    while (fscanf(file, "%s", &word) == 1) {
        insertIntoTree(tree, word);
    }
    /*
        TODO: fclose the file.
    */
    fclose(file);
    //printf("Tree:");
    //printTree(tree);
    while(1){
        printf("word: ");
        int r = scanf("%s", word);
        if(r != 1)
            break;
        length = strlen(word);
        if(length < 1)
            break;
        TNode* node = searchTree(tree, word);
        if(node){
            printf("PRESENT\n");
        } else{
            printf("ABSENT\n");
        }    
    }
    destroyTree(tree);
    return 0;
}
