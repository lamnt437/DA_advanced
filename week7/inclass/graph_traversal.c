#include <stdio.h>
#include <stdlib.h>
#include "jrb_graph.h"
#include "libfdr/dllist.h"


/*====GRAPH====*/
// typedef JRB Graph;

// Graph createGraph();
// void addEdge(Graph graph, int v1, int v2);
// int adjacent(Graph graph, int v1, int v2);
// int getAdjacentVertices (Graph graph, int v, int* output);
// void dropGraph(Graph graph);
// JRB jrb_find_int(JRB root, int ikey);
// traverse
	// #define jrb_traverse(ptr, lst) \
	//   for(ptr = jrb_first(lst); ptr != jrb_nil(lst); ptr = jrb_next(ptr))
// insert: JRB jrb_insert_int(JRB tree, int ikey, Jval val);


/*====QUEUE====*/

// Dllist queue = new_dllist();
// dll_append(queue, new_jval_i(v))
// dll_empty(queue)
// node = dll_first(queue)
// v = jval_i(node->val)
// dll_delete_node(node)

void BFS(Graph graph, int start, int stop, void (*func)(int));
void printVertex(int v) { printf("%4d", v); }

void main(){
	Graph g = createGraph();
    addEdge(g, 0, 1);
    addEdge(g, 1, 2);
    addEdge(g, 1, 3);
    addEdge(g, 2, 3);
    addEdge(g, 2, 4);
    addEdge(g, 4, 5);
    printf("\nBFS: start from node 1 to 5 : ");
    BFS(g, 1, 4, printVertex);
    printf("\nBFS: start from node 1 to all : ");
    BFS(g, 1, -1, printVertex);

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
			dll_append(queue, new_jval_i(output[i]));
		}
	}
	jrb_free_tree(visited);
}


//create queue
//create visited

//free visited
