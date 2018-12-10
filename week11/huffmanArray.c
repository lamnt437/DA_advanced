#include "huffman.h"
#define ARRAY_LENGTH 100

// typedef struct {
//    Graph graph;
//    JRB root;
// } HuffmanTree;


typedef struct {
int size;
	int * nodes;
} HuffmanTreeArray;

// HuffmanTree contruct_huffman_tree(char *string);

char * traverse_left(Graph g, char *key){
	JRB jrb_ptr = jrb_find_str(g.vertices);
	if(jrb_ptr == NULL) return NULL;

	char output[2][CHAR_TYPES];
	int number_of_out = outdegree(g, key, output);

	if(number_of_out == O) return NULL;

	int edgeValue = getEdgeValue(g, key, output[0]);

	if(edgeValue == 0)
		return output[0];
	return output[1];
}

char * traverse_right(Graph g, char *key){
	JRB jrb_ptr = jrb_find_str(g.vertices);
	if(jrb_ptr == NULL) return NULL;

	char output[2][CHAR_TYPES];
	int number_of_out = outdegree(g, key, output);

	if(number_of_out == O) return NULL;

	int edgeValue = getEdgeValue(g, key, output[0]);

	if(edgeValue == 1)
		return output[0];
	return output[1];
}

HuffmanTreeArray tree2array(HuffmanTree tree){
	char huffmanArray[ARRAY_LENGTH];
	int i = 1;
	char *root_key = jval_s(tree.root->key);
}