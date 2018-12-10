#include "jrb_dgraph.h"
#include "libfdr/jrb.h"
#include "libfdr/dllist.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INFINITIVE_VALUE 1000000
#define CHAR_TYPES 50

typedef struct {
   Graph graph;
   JRB root;
} HuffmanTree;

typedef struct {
	int size;
	char bits[9];
} Coding;
Coding huffmanTable[256];

void getCode(HuffmanTree tree, char *root_key);
HuffmanTree contruct_huffman_tree(char *string);

