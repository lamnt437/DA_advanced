#include <stdio.h>
#include <stdlib.h>
#include "jrb_dgraph.h"
#include "libfdr/dllist.h"


/*====GRAPH====*/
// typedef JRB Graph;

// Graph createGraph();
// void addEdge(Graph graph, int v1, int v2);
// int adjacent(Graph graph, int v1, int v2);
// int getAdjacentVertices (Graph graph, int v, int* output);
// void dropGraph(Graph graph);
// JRB jrb_find_int(JRB root, int ikey);


/*====QUEUE====*/

// Dllist queue = new_dllist();
// dll_append(queue, new_jval_i(v))
// dll_empty(queue)
// node = dll_first(queue)
// v = jval_i(node->val)
// dll_delete_node(node)

void BFS(Graph graph, int start, int stop, void (*func)(int));
void DFS(Graph graph, int start, int stop, void (*func)(int));
void printVertex(int v) { printf("%4d", v); }

void main(){
	Graph g = createGraph();
    addEdge(g, 0, 1);
    addEdge(g, 1, 2);
    addEdge(g, 1, 3);
    addEdge(g, 2, 3);
    addEdge(g, 2, 4);
    addEdge(g, 4, 5);
    printf("\nBFS: start from node 1 to 4 : ");
    BFS(g, 1, 4, printVertex);
    printf("\nBFS: start from node 1 to all : ");
    BFS(g, 1, -1, printVertex);

    printf("\nDFS: start from node 1 to 4 : ");
    DFS(g, 1, 4, printVertex);
    printf("\nDFS: start from node 1 to all : ");
    DFS(g, 1, -1, printVertex);

    printf("\n");
}

void BFS(Graph graph, int start, int stop, void (*func)(int)){
	Dllist queue = new_dllist();
	dll_append(queue, new_jval_i(start));
	JRB visited = make_jrb();

	//loop until empty queue or meet stop value
	while(!dll_empty(queue)){
		//dequeue
		Dllist node = dll_first(queue);
		int v = jval_i(node->val);
		dll_delete_node(node);

		if(jrb_find_int(visited, v) == NULL){
			func(v);
			jrb_insert_int(visited, v, new_jval_i(1));
		}

		if(v == stop)
			break;
		int output[100];
		int n = getAdjacentVertices(graph, v, output);
		int i;
		for(i = 0; i < n; i++){
			if(jrb_find_int(visited, output[i]) == NULL)
				dll_append(queue, new_jval_i(output[i]));
		}
	}
	jrb_free_tree(visited);
}

void DFS(Graph graph, int start, int stop, void (*func)(int)){
	JRB visited = make_jrb();
	Dllist stack = new_dllist();
	JRB start_node = jrb_find_int(graph, start);
	if(start_node != NULL){
		dll_prepend(stack, new_jval_i(start));
		while(!dll_empty(stack)){
			Dllist node = dll_first(stack);
			int v = jval_i(node->val);
			dll_delete_node(node);

			if(jrb_find_int(visited, v) == NULL){
				func(v);
				jrb_insert_int(visited, v, new_jval_i(1));
			}

			if(v == stop)
				break;

			int output[100];
			int n = getAdjacentVertices(graph, v, output);
			int i;
			for(i = 0; i < n; i++){
				if(jrb_find_int(visited, output[i]) == NULL)
					dll_prepend(stack, new_jval_i(output[i]));
			}
		}
	}
	jrb_free_tree(visited);
}
