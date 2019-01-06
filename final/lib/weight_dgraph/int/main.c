#include "int_weight_dgraph.h"
#include "stdio.h"
#include "stdlib.h"

void printValue(Graph g, int v){
	printf("%d ", v);
}

int main(){
	Graph g = createGraph();
	addVertex(g, 1, "s");
	addVertex(g, 2, "2");
	addVertex(g, 3, "3");
	addVertex(g, 4, "4");
	addVertex(g, 5, "5");
	addVertex(g, 6, "6");
	addVertex(g, 7, "7");
	addVertex(g, 8, "t");

	addEdge(g, 1, 2, 9);
	addEdge(g, 1, 6, 14);
	addEdge(g, 1, 7, 15);

	addEdge(g, 2, 3, 24);

	addEdge(g, 6, 3, 18);
	addEdge(g, 6, 5, 30);
	addEdge(g, 6, 7, 5);

	addEdge(g, 7, 5, 20);
	addEdge(g, 7, 8, 44);

	addEdge(g, 3, 5, 2);
	addEdge(g, 3, 8, 19);

	addEdge(g, 5, 4, 11);
	addEdge(g, 5, 8, 16);

	addEdge(g, 4, 3, 6);
	addEdge(g, 4, 8, 6);

	int path[100];
	int length;
	int weight = shortestPath(g, 1, 8, &length, path);

	printf("Shortest path from s to t: %d\n", weight);
	for(int i = 0; i < length; i++){
		printf("%d", path[i]);
		if(i != length - 1)
			printf("=>");
	}
	printf("\n");

	BFS(g, 1, 5, printValue);
	printf("\n");
	DFS(g, 1, 5, printValue);
	printf("\n");

	return 0;
}