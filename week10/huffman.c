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

void jrb_increment_val(JRB ptr){
	int old_val = jval_i(ptr->val);
	int new_val = old_val + 1;
	ptr->val = new_jval_i(new_val);
}

void getCode(HuffmanTree tree, char *root_key){
	Dllist node_queue = new_dllist();
	JRB current_string_map = make_jrb();

	//enqueue root
	dll_append(node_queue, new_jval_s(strdup(root_key)));
	jrb_insert_str(current_string_map, root_key, new_jval_s(""));

	while(!dll_empty(node_queue)){
		/* dequeue */

		Dllist dll_node = dll_first(node_queue);
        char *key = strdup(jval_s(dll_node->val));
        dll_delete_node(dll_node);

        /* end dequeue */


        /* save current code to temp */

        JRB jrb_ptr = jrb_find_str(current_string_map, key);
        char temp[CHAR_TYPES];
        strcpy(temp, jval_s(jrb_ptr->val));

        /* end save */


        //get children
        char output[2][CHAR_TYPES];
        int number_of_out_nodes = outdegree(tree.graph , key, output);

        //if leaf, insert to huffmanTable
        if(number_of_out_nodes == 0){
        	char c = key[0];
        	huffmanTable[c].size = strlen(temp);
        	strcpy(huffmanTable[c].bits, temp);
        }
        //else, create code for children then enqueue
        else{
        	for(int i = 0; i < number_of_out_nodes; i++){
				//enqueue child
        		dll_append(node_queue, new_jval_s(strdup(output[i])));
        		//save child's code to current_string_map
        		int edge_value = getEdgeValue(tree.graph, key, output[i]);
        		char *new_cur_string = (char *)malloc(sizeof(char) * CHAR_TYPES);
        		sprintf(new_cur_string, "%s%d", temp, edge_value);
        		jrb_insert_str(current_string_map, strdup(output[i]), new_jval_s(new_cur_string));
        	}
        }
	}
}

char * pdequeue(Dllist pqueue, JRB valueMap){
    int minValue = INFINITIVE_VALUE;
    int temp;

    Dllist ptr, minNodePtr;
    char *minNode = (char *)malloc(sizeof(char) * CHAR_TYPES);

    dll_traverse(ptr, pqueue){
        char * currentNode = jval_s(ptr->val);
        JRB jrb_ptr = jrb_find_str(valueMap, currentNode);
        temp = jval_i(jrb_val(jrb_ptr));
        if(temp < minValue){
            minValue = temp;
            minNodePtr = ptr;
            strcpy(minNode, currentNode);
        }
    }

    dll_delete_node(minNodePtr);
    return minNode;
}

void test_pdequeue(Dllist pqueue, JRB valueMap){
	while(!dll_empty(pqueue)){
		char *s = pdequeue(pqueue, valueMap);
		printf("%s\n", s);
	}
}

HuffmanTree contruct_huffman_tree(char *string){
	//BUILT FREQUENCY MAP
	JRB freqMap = make_jrb();
	Dllist pqueue = new_dllist();

	int length = strlen(string);
	for(int i = 0; i < length; i++){
		char *temp = (char *)malloc(sizeof(char) * 50);
		sprintf(temp, "%c", string[i]);
		JRB char_search = jrb_find_str(freqMap, temp);
		if(char_search == NULL){
			jrb_insert_str(freqMap, temp, new_jval_i(1));
			dll_append(pqueue, new_jval_s(strdup(temp)));
		}
		else{
			jrb_increment_val(char_search);
		}
	}

	//CREATE HUFFMAN GRAPH
	Graph huffman = createGraph();
	
	Dllist dllist_ptr;
	JRB jrb_ptr;

	//ADD VERTICES
	dll_traverse(dllist_ptr, pqueue){
		char *key = jval_s(dllist_ptr->val);
		jrb_ptr = jrb_find_str(freqMap, key);
		addVertex(huffman, key, jval_i(jrb_ptr->val));
	}

	//ADD EDGES
	char *first = NULL, *second = NULL;
	int first_val, second_val;
	char new_node_key[100];
	int end_ptr;
	Dllist dll_ptr1;
	
	while(!dll_empty(pqueue)){
		/* get value for left child */

		first = pdequeue(pqueue, freqMap);
		jrb_ptr = jrb_find_str(freqMap, first);
		first_val = jval_i(jrb_ptr->val);

		if(dll_empty(pqueue))
			break;

		/* end left child */


		/* get value for right child */

		second = pdequeue(pqueue, freqMap);
		jrb_ptr = jrb_find_str(freqMap, second);
		second_val = jval_i(jrb_ptr->val);

		/* end right child */


		/* write key for parent node */

		strcpy(new_node_key, first);
		end_ptr = strlen(new_node_key);
		strcpy(&new_node_key[end_ptr], second);

		/* end write key */


		//insert new parent node to graph
		addVertex(huffman, new_node_key, first_val + second_val);
		
		// add left and right edges
		addEdge(huffman, new_node_key, first, 0);
		addEdge(huffman, new_node_key, second, 1);

		// add value of new parent node to freqMap
		jrb_insert_str(freqMap, strdup(new_node_key), new_jval_i(first_val + second_val));
 
		//enqueue new parent node
		dll_append(pqueue, new_jval_s(strdup(new_node_key)));
	}

	//CONSTRUCT TREE

	HuffmanTree new_tree;
	new_tree.root = NULL;

	if(first != NULL){
		jrb_ptr = jrb_find_str(huffman.vertices, first);
		new_tree.root = jrb_ptr;
		new_tree.graph = huffman;
	}

	return new_tree;
}

int main(){
	char s[100];
	
	printf("Enter a string: ");
	fgets(s, 99, stdin);
	if(s[strlen(s) - 1] == '\n')
		s[strlen(s) - 1] = '\0';

	HuffmanTree tree = contruct_huffman_tree(s);
	getCode(tree, jval_s(tree.root->key));

	for(int i = 0; i < 256; i++){
		if(strcmp(huffmanTable[i].bits, "") != 0)
			printf("%c: %s\n", i, huffmanTable[i].bits);
	}

	return 0;
}