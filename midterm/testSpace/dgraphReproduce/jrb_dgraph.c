#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "libfdr/jval.h"
#include "libfdr/dllist.h"
#include "jrb_dgraph.h"

Graph createGraph(){
	Graph g;
	g.vertices = make_jrb();
	g.edges = make_jrb();
	return g;
}

void addVertex(Graph graph, int id, char *name){
	JRB ptr = jrb_find_int(graph.vertices, id);
	if(ptr == NULL){
		jrb_insert_int(graph.vertices, id, new_jval_s(strdup(name)));
	}
}

char *getVertex(Graph graph, int id){
	JRB ptr = jrb_find_int(graph.vertices, id);
	char *name = NULL;
	if(ptr != NULL)
		name = jval_s(jrb_val(ptr));
	return name;
}

void addEdge(Graph graph, int v1, int v2){
	//edge connect v1 to v2
	JRB ptr = jrb_find_int(graph.vertices, v1);
	if(ptr == NULL) return;
	ptr = jrb_find_int(graph.vertices, v2);
	if(ptr == NULL) return;

	JRB tree;
	ptr = jrb_find_int(graph.edges, v1);
	if(ptr == NULL){
		tree = make_jrb();
		jrb_insert_int(graph.edges, v1, new_jval_v(tree));
	}
	else{
		tree = (JRB)jval_v(jrb_val(ptr));
	}

	ptr = jrb_find_int(tree, v2);
	if(ptr == NULL)
		jrb_insert_int(tree, v2, new_jval_i(1));
}

int hasEdge(Graph graph, int v1, int v2){
	JRB ptr = jrb_find_int(graph.edges, v1);
	if(ptr == NULL) return 0;
	JRB tree = (JRB)jval_v(jrb_val(ptr));
	ptr = jrb_find_int(tree, v2);
	if(ptr == NULL) return 0;
	return 1;
}

int outdegree(Graph graph, int v, int *output){
	int counter = 0;
	JRB ptr = jrb_find_int(graph.edges, v);
	if(ptr != NULL){
		JRB tree = (JRB)jval_v(jrb_val(ptr));
		jrb_traverse(ptr, tree){
			int nextNode = jval_i(ptr->key);
			output[counter] = nextNode;
			counter++;
		}
	}
	return counter;
}

int indegree(Graph graph, int v, int *output){
	int counter = 0;
	JRB ptr, tree, vPtr;
	jrb_traverse(ptr, graph.edges){
		tree = (JRB)jval_v(jrb_val(ptr));
		vPtr = jrb_find_int(tree, v);
		if(vPtr != NULL){
			int previousNode = jval_i(ptr->key);
			output[counter] = previousNode;
			counter++;
		}
	}
	return counter;
}

void DFS(Graph graph, int start, int stop, void (*func)(Graph, int)){
	Dllist stack = new_dllist();
	JRB visitedNodes = make_jrb();
	JRB startNode = jrb_find_int(graph.vertices, start);
	if(startNode == NULL) return;

	//enqueue startNode
	JRB ptr = jrb_find_int(visitedNodes, start);
	if(ptr == NULL)
		dll_prepend(stack, new_jval_i(start));
	while(!dll_empty(stack)){
		Dllist dllNode = dll_first(stack);
		int v = jval_i(dll_val(dllNode));
		dll_delete_node(dllNode);

		ptr = jrb_find_int(visitedNodes, v);
		if(ptr == NULL){
			func(graph, v);
			jrb_insert_int(visitedNodes, v, new_jval_i(1));
		}

		if(v == stop)
			break;

		int i, output[100];
		int n = outdegree(graph, v, output);
		for(i = 0; i < n; i++){
			int currentVertice = output[i];
			ptr = jrb_find_int(visitedNodes, currentVertice);
			if(ptr == NULL)
				dll_prepend(stack, new_jval_i(currentVertice));
		}
	}
	jrb_free_tree(visitedNodes);
	free_dllist(stack);
}

int dag_start;
int not_dag = 0;

void dag_check(Graph graph, int v){
	if(hasEdge(graph, v, dag_start))
		not_dag = 1;
}

int DAG(Graph graph){
	//return 1 if no cycle, 0 otherwise
	JRB ptr;
	not_dag = 0;
	jrb_traverse(ptr, graph.vertices){
		dag_start = jval_i(ptr->key);
		DFS(graph, dag_start, -1, dag_check);
		if(not_dag != 0)
			return 0;
	}
	return 1;
}

void dropGraph(Graph graph){
	//free vertices
	JRB ptr, tree;
	jrb_traverse(ptr, graph.vertices){
		char *name = jval_s(jrb_val(ptr));
		free(name);
	}
	jrb_free_tree(graph.vertices);

	//free edges
	jrb_traverse(ptr, graph.edges){
		tree = (JRB)jval_v(jrb_val(ptr));
		jrb_free_tree(tree);
	}
	jrb_free_tree(graph.edges);
}

void topologicalSort(Graph graph, int *output, int *n){
	Dllist queue = new_dllist();
	JRB indegreeTable = make_jrb();

	//traverse throught vertices, save indegree to indegreeTable, add to queue if indegree == 0
	JRB ptr;
	int currentVertice;
	int inNumber, outNumber;
	int inList[100], outList[100];

	jrb_traverse(ptr, graph.vertices){
		currentVertice = jval_i(ptr->key);
		inNumber = indegree(graph, currentVertice, inList);

		jrb_insert_int(indegreeTable, currentVertice, new_jval_i(inNumber));
		if(inNumber == 0)
			dll_append(queue, new_jval_i(currentVertice));
	}

	//dequeue, add to output, counter++, decrease indegree of currentVertice's outlist, add to queue if newIndegree == 0
	int counter = 0;
	while(!dll_empty(queue)){
		Dllist dllNode = dll_first(queue);
		currentVertice = jval_i(dll_val(dllNode));
		dll_delete_node(dllNode);

		output[counter] = currentVertice;
		counter++;

		outNumber = outdegree(graph, currentVertice, outList);
		for(int i = 0; i < outNumber; i++){
			int nodeIndex = outList[i];
			ptr = jrb_find_int(indegreeTable, nodeIndex);
			int newIndegree = jval_i(ptr->val) - 1;
			ptr->val = new_jval_i(newIndegree);

			if(newIndegree == 0)
				dll_append(queue, new_jval_i(nodeIndex));
		}
	}

	*n = counter;
	jrb_free_tree(indegreeTable);
	free_dllist(queue);
}

int shortestPath(Graph graph, int start, int stop, int *path){
    Dllist queue = new_dllist();
    JRB visited = make_jrb();
    JRB prevTable = make_jrb();

    JRB startNode = jrb_find_int(graph.vertices, start);
    if(startNode == NULL) return 0;

    int prev = 0;
    int v = start;

    dll_append(queue, new_jval_i(start));
    jrb_insert_int(prevTable, start, new_jval_i(prev));

    while(!dll_empty(queue)){
        //dequeue
        Dllist node = dll_first(queue);
        v = jval_i(node->val);
        dll_delete_node(node);

        if(jrb_find_int(visited, v) == NULL){
            jrb_insert_int(visited, v, new_jval_i(1));
        }

        if(v == stop)
            break;

        prev = v;
        int output[100];
        int n = outdegree(graph, v, output);
        int i;
        for(i = 0; i < n; i++){
            if(jrb_find_int(visited, output[i]) == NULL){
                dll_append(queue, new_jval_i(output[i]));
                jrb_insert_int(prevTable, output[i], new_jval_i(prev));
            }
        }
    }

    //check if the last node visited is stop
    int counter = 0;
    if(v == stop){
    	JRB ptr;
    	int ptrIndex = v;
        path[counter] = ptrIndex;
        counter++;
    	while(ptrIndex != start){
    		ptr = jrb_find_int(prevTable, ptrIndex);
    		ptrIndex = jval_i(ptr->val);
    		path[counter] = ptrIndex;
    		counter++;
    	}

        //reverse path
        int i = 0, j = counter - 1, temp;
        while(i < j){
            temp = path[i];
            path[i] = path[j];
            path[j] = temp;
            i++;
            j--;
        }
    }

    
    jrb_free_tree(visited);
    jrb_free_tree(prevTable);
    free_dllist(queue);

    return counter;
}