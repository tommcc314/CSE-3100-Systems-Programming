// String BST
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
    FILE* file = fopen(argv[1], "r");
    char word[200];
    size_t length;
    while (fscanf(file, "%s", &word) == 1) {
        tree = insertIntoTree(tree, word);
    }
    fclose(file);
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
