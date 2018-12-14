#include "huffmanArray.h"

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

void compressFile(FILE* in, FILE *out){
	if(in == NULL){
		return;
	}

	HuffmanTree tree = makeHuffman(in);
	createHuffmanTable(tree, huffmanTable);
	HuffmanTreeArray treeArray = tree2array(tree);

	fprintf(out, "HM ");							//huffman prefix
	fprintf(out, "%d ", treeArray.size);			
	for(int i = 0; i < treeArray.size; i++){
		fprintf(out, "%d ", treeArray.nodes[i]);
	}

	char data[100000];
	char c;
	int get_status;
	int size_counter = 0;
	int end_ptr = 0;
	
	rewind(in);
	while((get_status = fscanf(in, "%c", &c)) > 0){
		char *encoded_temp = huffmanTable[c].bits;
		size_counter += huffmanTable[c].size;
		printf("%s\n", encoded_temp);
		sprintf(&data[end_ptr], "%s", encoded_temp);
		end_ptr = strlen(data);
	}

	fprintf(out, "%d ", size_counter);
	fprintf(out, "%s", data);
}

void decompressFile(FILE *in, FILE *out){
	//read huffman tree array
	char stream[10];
	fscanf(in, "%s", stream);
	
	if(strcmp(stream, "HM") != 0)
		return;

	int size;
	int value;
	fscanf(in, "%d", &size);

	int *treeArray = (int *)malloc(sizeof(int) * size);
	for(int i = 0; i < size; i++){
		fscanf(in, "%d", &value);
		treeArray[i] = value;
	}

	//decode
	char c;
	char temp[2];
	fscanf(in, "%d", &size);
	int ptr = 0;

	fscanf(in, "%c", &c);
	for(int i = 0; i < size; i++){
		fscanf(in, "%c", &c);
		sprintf(temp, "%c", c);
		value = atoi(temp);

		//0 - go left
		if(value == 0)
			ptr = ptr * 2 + 1;

		//1 - go right
		else
			ptr = ptr * 2 + 2;

		//check if is leaf
		if(treeArray[ptr] != 0 && treeArray[ptr] != -1){
			printf("%c", treeArray[ptr]);
			fprintf(out, "%c", treeArray[ptr]);
			ptr = 0;
		}
	}
}