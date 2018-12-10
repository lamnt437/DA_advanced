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
	JRB jrb_ptr = jrb_find_str(g.vertices, key);
	if(jrb_ptr == NULL) return NULL;

	char output[2][CHAR_TYPES];
	// output[0] = (char *)malloc(sizeof(char) * CHAR_TYPES);
	// output[1] = (char *)malloc(sizeof(char) * CHAR_TYPES);

	int number_of_out = outdegree(g, key, output);

	if(number_of_out == 0) return NULL;

	int edgeValue = getEdgeValue(g, key, output[0]);

	if(edgeValue == 0)
		return strdup(output[0]);
	return strdup(output[1]);
}

char * traverse_right(Graph g, char *key){
	JRB jrb_ptr = jrb_find_str(g.vertices, key);
	if(jrb_ptr == NULL) return NULL;

	char output[2][CHAR_TYPES];
	// output[0] = (char *)malloc(sizeof(char) * CHAR_TYPES);
	// output[1] = (char *)malloc(sizeof(char) * CHAR_TYPES);

	int number_of_out = outdegree(g, key, output);

	if(number_of_out == 0) return NULL;

	int edgeValue = getEdgeValue(g, key, output[0]);

	if(edgeValue == 1)
		return strdup(output[0]);
	return strdup(output[1]);
}

HuffmanTreeArray tree2array(HuffmanTree tree){
	HuffmanTreeArray huffman;

	int *huffmanArray = (int *)malloc(sizeof(int) * ARRAY_LENGTH);
	Dllist index_queue = new_dllist();
	Dllist key_queue = new_dllist();

	int index = 0;
	int size = 1;
	char *key = jval_s(tree.root->key);

	//enqueue
	dll_append(index_queue, new_jval_i(index));
	dll_append(key_queue, new_jval_s(strdup(key)));

	while(!dll_empty(index_queue)){

		/* dequeue */

		Dllist dll_node = dll_first(index_queue);
		index = jval_i(dll_node->val);
		dll_delete_node(dll_node);

		dll_node = dll_first(key_queue);
		key = strdup(jval_s(dll_node->val));
		dll_delete_node(dll_node);

		// printf("%s\n", key);

		/* end dequeue */


		/* write array */

		if(strlen(key) == 1){	//is leaf
			huffmanArray[index] = key[0];
			continue;
		}
		else{	//not leaf (has children)
			huffmanArray[index] = -1;

			int left_index = index * 2 + 1;
			dll_append(index_queue, new_jval_i(left_index));
			char *left_key = traverse_left(tree.graph, key);
			dll_append(key_queue, new_jval_s(strdup(left_key)));
		
			int right_index = left_index + 1;
			dll_append(index_queue, new_jval_i(right_index));
			char *right_key = traverse_right(tree.graph, key);
			dll_append(key_queue, new_jval_s(strdup(right_key)));	

			size = right_index + 1;		
		}

		/* end write array */
	}

	huffman.size = size;
	huffman.nodes = huffmanArray;

	return huffman;
}

int main(){
	char s[100];
	
	printf("Enter a string: ");
	fgets(s, 99, stdin);
	if(s[strlen(s) - 1] == '\n')
		s[strlen(s) - 1] = '\0';

	HuffmanTree tree = contruct_huffman_tree(s);
	getCode(tree, jval_s(tree.root->key));	

	// for(int i = 0; i < 256; i++){
	// 	if(strcmp(huffmanTable[i].bits, "") != 0)
	// 		printf("%c: %s\n", i, huffmanTable[i].bits);
	// }

	HuffmanTreeArray huffmanArray = tree2array(tree);
	int size = huffmanArray.size;
	for(int i = 0; i < size; i++){
		printf("%d ", huffmanArray.nodes[i]);
	}

	return 0;
}