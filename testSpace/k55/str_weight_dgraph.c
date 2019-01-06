#include "str_weight_dgraph.h"
#include "libfdr/jrb.h"
#include "libfdr/dllist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double longestPath(Graph graph, char *start, char *stop, int *length, char path[][ID_LENGTH]);
char *pdequeue(Dllist pqueue, JRB value_map);


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

int hasEdge(Graph graph, char * v1, char * v2){
    JRB node = jrb_find_str(graph.edges, v1);
    if(node == NULL)
        return 0;
    JRB tree = (JRB)jval_v(node->val);
    node = jrb_find_str(tree, v2);
    if(node == NULL)
        return 0;
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

void DFS(Graph graph, char * start, char * stop, void (*func)(Graph, char *)){
    JRB visited = make_jrb();
    Dllist stack = new_dllist();
    JRB start_node = jrb_find_str(graph.edges, start);
    if(start_node != NULL){
        dll_prepend(stack, new_jval_s(strdup(start)));
        while(!dll_empty(stack)){
            Dllist node = dll_first(stack);
            char * v = strdup(jval_s(node->val));
            dll_delete_node(node);

            if(jrb_find_str(visited, v) == NULL){
                func(graph, v);
                jrb_insert_str(visited, strdup(v), new_jval_i(1));
            }

            if(strcmp(v, stop) == 0)
                break;

            char output[100][ID_LENGTH];
            int n = outdegree(graph, v, output);
            int i;
            for(i = 0; i < n; i++){
                if(jrb_find_str(visited, output[i]) == NULL)
                    dll_prepend(stack, new_jval_s(strdup(output[i])));
            }
        }
    }
    jrb_free_tree(visited);
    free_dllist(stack);
}

void BFS(Graph graph, char * start, char * stop, void (*func)(Graph, char *)){
    JRB visited = make_jrb();
    Dllist queue = new_dllist();
    JRB start_node = jrb_find_str(graph.edges, start);

    if(start_node != NULL){
        dll_append(queue, new_jval_s(strdup(start)));
        while(!dll_empty(queue)){
            Dllist node = dll_first(queue);
            char *v = strdup(jval_s(node->val));
            dll_delete_node(node);

            if(jrb_find_str(visited, v) == NULL){
                func(graph, v);
                jrb_insert_str(visited, strdup(v), new_jval_i(1));
            }

            if(strcmp(v, stop) == 0)
                break;
            char output[100][ID_LENGTH];
            int n = outdegree(graph, v, output);
            int i;
            for(i = 0; i < n; i++){
                if(jrb_find_str(visited, output[i]) == NULL)
                    dll_append(queue, new_jval_s(strdup(output[i])));
            }
        }
    }
    jrb_free_tree(visited);
    free_dllist(queue);
}

/* topological sort */

char * dag_start = NULL;
int dag_check = 0;

void dag_visit(Graph g, char * v){
    dag_check = hasEdge(g, v, dag_start);
}

int DAG(Graph graph){
    JRB node;
    dag_check = 0;
    jrb_traverse(node, graph.vertices){
        dag_start = strdup(jval_s(node->key));
        DFS(graph, dag_start, "", dag_visit);
        if(dag_check != 0)
            return 0;
    }
    return 1;
}

void topologicalSort(Graph graph, char output[][ID_LENGTH], int *n){
    //create indegree table
    JRB indegreeTable = make_jrb();
    Dllist queue = new_dllist();
    
    JRB ptr;
    int inNumber;
    char inList[100][ID_LENGTH];
    int outNumber;
    char outList[100][ID_LENGTH];
    int i;

    jrb_traverse(ptr, graph.vertices){
        char * verticeIndex = strdup(jval_s(ptr->key));
        inNumber = indegree(graph, verticeIndex, inList);
        jrb_insert_str(indegreeTable, strdup(verticeIndex), new_jval_i(inNumber));
        if(inNumber == 0){
            dll_append(queue, new_jval_s(strdup(verticeIndex)));
        }
    }

    //sort
    int counter = 0;
    while(!dll_empty(queue)){
        Dllist dequeuedNode = dll_first(queue);
        char * visitingVertice = strdup(jval_s(dll_val(dequeuedNode)));
        dll_delete_node(dequeuedNode);

        // output[counter] = visitingVertice;
        strcpy(output[counter], visitingVertice);
        counter++;

        outNumber = outdegree(graph, visitingVertice, outList);
        for(i = 0; i < outNumber; i++){
            JRB decreaseIndegreeNode = jrb_find_str(indegreeTable, outList[i]);
            int newIndegree = jval_i(decreaseIndegreeNode->val) - 1;
            decreaseIndegreeNode->val = new_jval_i(newIndegree);

            if(newIndegree == 0)
                dll_append(queue, new_jval_s(strdup(outList[i])));
        }
    }

    *n = counter;
    jrb_free_tree(indegreeTable);
    free_dllist(queue);
}

/* end topo */

/* find shortest path */

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