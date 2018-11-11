#include <stdio.h>
#include <stdlib.h>
#include "jrb_dgraph.h"
#include "libfdr/dllist.h"

void main(){
	// Graph g = createGraph();
	// int x;
	// int n;
	// int output[100];

 //    addVertex(g, 0, "V0");
 //    addVertex(g, 1, "V1");
 //    addVertex(g, 2, "V2");
 //    addVertex(g, 3, "V3");
 //    addEdge(g, 0, 1);
 //    addEdge(g, 1, 2);
 //    addEdge(g, 2, 0);
 //    addEdge(g, 1, 3);
 //    if (DAG(g)) printf("The graph is acycle\n");
 //    else printf("Have cycles in the graph\n");
 //    // printf("Find number of outdegree: ");
 //    // scanf("%d", &x);
 //    // n = outdegree(g, x, output);
 //    // int i;
 //    // printf("\n%d:\n", n);
 //    // for(i = 0; i < n; i++){
 //    // 	printf("%d ", output[i]);
 //    // }
 //    // printf("\n");

 //    // printf("Find number of indegree: ");
 //    // scanf("%d", &x);
 //    // n = indegree(g, x, output);
 //    // printf("\n%d:\n", n);
 //    // for(i = 0; i < n; i++){
 //    // 	printf("%d ", output[i]);
 //    // }
 //    // printf("\n");

    int n, i;
    int output[100];
    Graph g = createGraph();
    addVertex(g, 0, "CS102"); addVertex(g, 1, "CS140");
    addVertex(g, 2, "CS160"); addVertex(g, 3, "CS302");
    addVertex(g, 4, "CS311"); addVertex(g, 5, "MATH300");
    addEdge(g, 0, 1); addEdge(g, 0, 2);
    addEdge(g, 1, 3); addEdge(g, 5, 4); addEdge(g, 3, 4);
    if(DAG(g)){
        topologicalSort(g, output, &n);
        printf("The topological order:\n");
        for (i=0; i<n; i++)
             printf("%s\n", getVertex(g, output[i]));
    }
    else{
        printf("Can not make topological sort\n"); 
    }
}