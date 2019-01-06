#include "str_weight_dgraph.h"
#include "libfdr/jrb.h"
#include "libfdr/dllist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Graph createGraph(){
	Graph g;
    g.vertices = make_jrb();
    g.edges = make_jrb();
    return g;
}

int addVertex(Graph graph, char *id, char *name){
	JRB node = jrb_find_str(graph.vertices, id);
	//ADD SUCCESS
	if(node == NULL){
		jrb_insert_str(graph.vertices, strdup(id), new_jval_s(strdup(name)));
		return 1;
	}
	//ADD FAIL
	return 0;
}

char *getVertex(Graph graph, char *id){
	JRB node = jrb_find_str(graph.vertices, id);
	if(node != NULL)
		return jval_s(node->val);
	return NULL;
}

int addEdge(Graph graph, char *v1, char *v2, double weight){
	//CHECK IF VERTICES EXIST
	JRB node = jrb_find_str(graph.vertices, v1);
	if(node == NULL) return 0;
	node = jrb_find_str(graph.vertices, v2);
	if(node == NULL) return 0;

	//ADD EDGE
	JRB tree;
	node = jrb_find_str(graph.edges, v1);
	if(node == NULL){
		tree = make_jrb();
		jrb_insert_str(graph.edges, strdup(v1), new_jval_v(tree));
	}
	else{
		tree = (JRB)jval_v(node->val);
	}

	node = jrb_find_str(tree, v2);
	if(node != NULL)
		return 0;
	jrb_insert_str(tree, strdup(v2), new_jval_d(weight));
	return 1;
}

double getEdgeValue(Graph graph, char *v1, char *v2){
	JRB node = jrb_find_str(graph.edges, v1);
	if(node == NULL)
		return INFINITIVE_VALUE;

	JRB tree = (JRB) jval_v(node->val);
	node = jrb_find_str(tree, v2);
	if(node == NULL)
		return INFINITIVE_VALUE;
	return jval_d(node->val);
}

int outdegree(Graph graph, char *v, char output[][ID_LENGTH]){
	int counter = 0;

	JRB node = jrb_find_str(graph.edges, v);
	if(node != NULL){
		JRB tree = (JRB) jval_v(node->val);
		JRB jrb_ptr;
		jrb_traverse(jrb_ptr, tree){
			char *id = jval_s(jrb_ptr->key);
			strcpy(output[counter], id);
			counter++;
		}
	}

	return counter;
}
int indegree(Graph graph, char *v, char output[][ID_LENGTH]){
	int counter = 0;

	JRB jrb_ptr, tree, find_v;
	jrb_traverse(jrb_ptr, graph.edges){
		tree = (JRB) jval_v(jrb_ptr->val);
		find_v = jrb_find_str(tree, v);
		if(find_v != NULL){
			char *id = jval_s(jrb_ptr->key);
			strcpy(output[counter], id);
			counter++;
		}
	}

	return counter;
}

void BFS(Graph graph, char * start, char * stop, void (*func)(char *)){
    //init
    JRB visited = make_jrb();
    Dllist queue = new_dllist();

    //find if start node exists
    JRB find_start = jrb_find_str(graph.vertices, start);
    if(find_start == NULL) return;

    //enqueue start
    dll_append(queue, new_jval_s(strdup(start)));
    while(!dll_empty(queue)){
        Dllist dequeued_node = dll_first(queue);
        char *node_id = strdup(jval_s(dequeued_node->val));
        dll_delete_node(dequeued_node);

        if(jrb_find_str(visited, node_id) == NULL){
            func(node_id);
            jrb_insert_str(visited, strdup(node_id), new_jval_i(1));
        }

        if(strcmp(node_id, stop) == 0)
        	break;

        char outList[100][ID_LENGTH];
        int n = outdegree(graph, node_id, outList);
        for(int i = 0; i < n; i++){
            char * child_id = outList[i];

            if(jrb_find_str(visited, child_id) == NULL)
                dll_append(queue, new_jval_s(strdup(child_id)));
        }
    }
}

void DFS(Graph graph, char * start, char * stop, void (*func)(char *)){
    //init
    JRB visited = make_jrb();
    Dllist stack = new_dllist();

    //find if start node exists
    JRB find_start = jrb_find_str(graph.vertices, start);
    if(find_start == NULL) return;

    //push start
    dll_prepend(stack, new_jval_s(strdup(start)));
    while(!dll_empty(stack)){
        Dllist popped_node = dll_first(stack);
        char *node_id = strdup(jval_s(popped_node->val));
        dll_delete_node(popped_node);

        if(jrb_find_str(visited, node_id) == NULL){
            func(node_id);
            jrb_insert_str(visited, strdup(node_id), new_jval_i(1));
        }

        if(strcmp(node_id, stop) == 0)
        	break;

        char outList[100][ID_LENGTH];
        int n = outdegree(graph, node_id, outList);
        for(int i = 0; i < n; i++){
            char * child_id = outList[i];

            if(jrb_find_str(visited, child_id) == NULL)
                dll_prepend(stack, new_jval_s(strdup(child_id)));
        }
    }
}

char *pdequeue(Dllist pqueue, JRB value_map){	//dequeue node with min value
	double min_value = INFINITIVE_VALUE;
	double current_value;

	Dllist dll_ptr, min_node_ptr;
	JRB jrb_ptr;

	dll_traverse(dll_ptr, pqueue){
		char *id = jval_s(dll_ptr->val);
		jrb_ptr = jrb_find_str(value_map, id);
		current_value = jval_d(jrb_ptr->val);
		if(current_value < min_value){
			min_node_ptr = dll_ptr;
			min_value = current_value;
		}
	}

	char *dequeued_id = (char *)malloc(sizeof(char) * ID_LENGTH);
	strcpy(dequeued_id, jval_s(min_node_ptr->val));
	dll_delete_node(min_node_ptr);

	return dequeued_id;
}

int checkInQueue(Dllist pqueue, char *id){
	Dllist dll_ptr;
	dll_traverse(dll_ptr, pqueue){
		char *key = jval_s(dll_ptr->val);
		if(strcmp(key, id) == 0)
			return 1;
	}

	return 0;
}

double shortestPath(Graph graph, char *start, char *stop, int *length, char path[][ID_LENGTH]){
	*length = 0;
	JRB start_ptr = jrb_find_str(graph.vertices, start);
	if(start_ptr == NULL) return INFINITIVE_VALUE;

	//init
	Dllist pqueue = new_dllist();
	JRB visited = make_jrb();
	JRB value_map = make_jrb();
	JRB parent_map = make_jrb();

	//enqueue start node
	jrb_insert_str(value_map, strdup(start), new_jval_d(0));
	jrb_insert_str(parent_map, strdup(start), new_jval_s(start));
	dll_append(pqueue, new_jval_s(strdup(start)));

	char *parent_id;

	while(!dll_empty(pqueue)){
		//get parent id
		parent_id = pdequeue(pqueue, value_map);
		jrb_insert_str(visited, strdup(parent_id), new_jval_i(1));

		if(strcmp(parent_id, stop) == 0) break;

		//get parent value
		JRB parent_value_ptr = jrb_find_str(value_map, parent_id);
		double parent_value = jval_d(parent_value_ptr->val);

		//get outlist of parent node
		char outlist[100][ID_LENGTH];
		int number_of_children = outdegree(graph, parent_id, outlist);

		//enqueue children
		for(int i = 0; i < number_of_children; i++){
			char *child_id = outlist[i];

			//find if child is visited
			JRB find_child = jrb_find_str(visited, child_id);
			if(find_child != NULL) continue;
			
			//enqueue child
			if(!checkInQueue(pqueue, child_id))
				dll_append(pqueue, new_jval_s(strdup(child_id)));

			//relax
			double temp_value = parent_value + getEdgeValue(graph, parent_id, child_id);
			JRB child_value_ptr = jrb_find_str(value_map, child_id);
			if(child_value_ptr == NULL){
				jrb_insert_str(value_map, strdup(child_id), new_jval_d(temp_value));
				jrb_insert_str(parent_map, strdup(child_id), new_jval_s(parent_id));
			}
			else{
				double child_value = jval_d(child_value_ptr->val);
				if(temp_value < child_value){
					child_value_ptr->val = new_jval_d(temp_value);
					JRB child_parent_ptr = jrb_find_str(parent_map, child_id);
					child_parent_ptr->val = new_jval_s(strdup(parent_id));
				}
			}
		}
	}

	if(strcmp(parent_id, stop) != 0) return INFINITIVE_VALUE;

	// //print value map
	// JRB value_ptr;
	// jrb_traverse(value_ptr, value_map){
	// 	printf("%s: %lf\n", jval_s(value_ptr->key), jval_d(value_ptr->val));
	// }

	//get path weight
	JRB find_value = jrb_find_str(value_map, parent_id);
	double path_weight = jval_d(find_value->val);

	//write path
	int counter = 0;
	char *current_id = parent_id;
	while(1){
		strcpy(path[counter], current_id);
		counter++;
		if(strcmp(current_id, start) == 0)
			break;
		current_id = jval_s(jrb_val(jrb_find_str(parent_map, current_id)));
	}

	//reverse path
	int i = 0, j = counter - 1;
	char temp[ID_LENGTH];

	while(i < j){
		strcpy(temp, path[i]);
		strcpy(path[i], path[j]);
		strcpy(path[j], temp);
		i++;
		j--;
	}

	*length = counter;
	return path_weight;
}