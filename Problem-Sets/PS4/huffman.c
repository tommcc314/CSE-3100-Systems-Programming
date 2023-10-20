#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "huffman.h"
#include "heap.h"

void extractCodesAux(Node* node, Code* codes,unsigned long long path, char nbits)
{
    /* TODO: extract code for all symbols
    * If the node is internal, recursively call the function on left and right nodes. Do not forget to update the path and nbits value.
    * If the node is a leaf, update the nbits and bits value in codes for the corresponding symbol.
    * 
    * HINT: The bits value is set by the path followed. The left shift operator will come in handy to set the path as you traverse the tree.
    */
    if (!node)
        return;
    if (!node->left && !node->right) {
        codes[node->c].nbits = nbits;
        codes[node->c].bits = path;
        return;
    }
    if (node->left)
        extractCodesAux(node->left, codes, path << 1, nbits + 1);
    if (node->right)
        extractCodesAux(node->right, codes, (path << 1) + 1, nbits + 1);
}

Code* extractCodes(Node* root)
{
    /* TODO: extract the code for each symbol
    * To do this, allocate memory to store codes for NUM_SYMBOLS number of characters
    * Call the extractCodesAux function to recursively extract codes for all leaves. The call begins from the root node.
    */
    Code* codes = calloc(NUM_SYMBOLS, sizeof(Code));
    extractCodesAux(root, codes, 0, 0);
    return codes;
}

char* codeToString(Code code)
{
    /* TODO: convert the code into a string
    * To do this, read the bits value and convert nbits number of bits into a char*
    */
    char* string = malloc((code.nbits + 1) * sizeof(char));
    string[code.nbits] = 0;
    for (int i = 0; i < code.nbits; ++i) {
        string[code.nbits - i - 1] = (char)(code.bits & 1) + '0';
        code.bits >>= 1;
    }
    printf("#bits: %d\n", code.nbits);
    return string;
}

void freeHuffmanTree(Node* root)
{
    /* TODO: free the huffman tree
    * To do this, recursively free each node of the tree.
    */
    if (root->left) {
        freeHuffmanTree(root->left);
        root->left = NULL;
    }
    if (root->right) {
        freeHuffmanTree(root->right);
        root->right = NULL;
    } 
    free(root);
}

Node* createHuffmanTree(unsigned long* freq)
{
  /* TODO: create a huffman tree. this includes the following steps
   * Create a heap (PQ) using the makeheap function 
   * Create a node for each symbol with frequency > 1 and insert the node in the PQ. 
   * While there is more than 1 node in PQ, extract min 1 and min 2, combine the nodes to create an internal node and insert it into the PQ.
   * When only one node remains, assign it as the root and return it.
   *
   * Note: do not forget to free memory that you no longer need.
   */
    Heap* huffmanHeap = makeHeap(NUM_SYMBOLS);
    for (int i = 0; i < 128; ++i) {
        if (freq[i] > 0) {
            Node* newNode = malloc(sizeof(Node));
            newNode->left = NULL;
            newNode->right = NULL;
            newNode->c = i;
            newNode->freq = freq[i];
            insertHeap(huffmanHeap, newNode);
        }
    }
    while (huffmanHeap->sz > 1) {
        Node* a = extractMin(huffmanHeap);
        Node* b = extractMin(huffmanHeap);
        Node* parent = malloc(sizeof(Node));
        parent->left = a;
        parent->right = b;
        parent->c = 0;
        parent->freq = a->freq + b->freq;
        insertHeap(huffmanHeap, parent);
    }
    Node* root = extractMin(huffmanHeap);
    freeHeap(huffmanHeap);
    return root;
}
