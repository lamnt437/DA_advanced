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


/*====QUEUE====*/

// Dllist queue = new_dllist();
// dll_append(queue, new_jval_i(v))
// dll_empty(queue)
// node = dll_first(queue)
// v = jval_i(node->val)
// dll_delete_node(node)

Graph g;

void printVertex(int v){
	// char *name = getVertex(g, v);
	// if(name != NULL)
	// 	printf("%s ", name);
    printf("%d  ", v);
}

int main(){
	g = createGraph();
	addVertex(g, 0, "Kim");
	addVertex(g, 1, "Moc");
	addVertex(g, 2, "Thuy");
	addVertex(g, 3, "Hoa");
	addVertex(g, 4, "Tho");
	addVertex(g, 5, "Plasma");

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

    int path[100];
    int i, n;
    int start, stop;

    printf("Enter start: ");
    scanf("%d", &start);

    printf("Enter stop: ");
    scanf("%d", &stop);

    n = shortestPath(g, start, stop, path);
    for(i = 0; i < n; i++){
        printVertex(path[i]);
    }

    printf("\n");

    return 0;
}