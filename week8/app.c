#include <stdio.h>
#include <stdlib.h>
#include "jrb_dgraph.h"
#include "libfdr/dllist.h"

void main(){
	Graph g = createGraph();
	int x;
	int n;
	int output[100];

    addVertex(g, 0, "V0");
    addVertex(g, 1, "V1");
    addVertex(g, 2, "V2");
    addVertex(g, 3, "V3");
    addEdge(g, 0, 1);
    addEdge(g, 1, 2);
    addEdge(g, 2, 0);
    addEdge(g, 1, 3);
    if (DAG(g)) printf("The graph is acycle\n");
    else printf("Have cycles in the graph\n");
    // printf("Find number of outdegree: ");
    // scanf("%d", &x);
    // n = outdegree(g, x, output);
    // int i;
    // printf("\n%d:\n", n);
    // for(i = 0; i < n; i++){
    // 	printf("%d ", output[i]);
    // }
    // printf("\n");

    // printf("Find number of indegree: ");
    // scanf("%d", &x);
    // n = indegree(g, x, output);
    // printf("\n%d:\n", n);
    // for(i = 0; i < n; i++){
    // 	printf("%d ", output[i]);
    // }
    // printf("\n");
}