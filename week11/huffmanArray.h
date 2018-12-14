#ifndef _huffmanArray_h_
#define _huffmanArray_h_ 

#include "huffman.h"
#include "jrb_dgraph.h"
#define ARRAY_LENGTH 100

Coding huffmanTable[256];


typedef struct {
	int size;
	int * nodes;
} HuffmanTreeArray;

void compressFile(FILE* in, FILE *out);
void decompressFile(FILE *in, FILE *out);

#endif