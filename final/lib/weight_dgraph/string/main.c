#include <stdio.h>
#include "str_weight_dgraph.h"

void printValue(char *v){
	printf("%s ", v);
}

int main(){
	Graph g = createGraph();
	addVertex(g, "AB", "AB");
	addVertex(g, "CD", "CD");
	addVertex(g, "EF", "EF");
	addVertex(g, "GH", "GH");
	addVertex(g, "IK", "IK");
	addVertex(g, "LM", "LM");
	addVertex(g, "NO", "NO");

	addEdge(g, "AB", "CD", 8);
	addEdge(g, "AB", "IK", 9);
	addEdge(g, "CD", "LM", 7);
	addEdge(g, "CD", "NO", 4);
	addEdge(g, "CD", "GH", 13);
	addEdge(g, "IK", "NO", 10);
	addEdge(g, "LM", "GH", 2);
	addEdge(g, "NO", "EF", 17);

	char path[100][ID_LENGTH];
	int length;
	double weight = shortestPath(g, "AB", "GH", &length, path);

	printf("path weight: %lf\n", weight);
	for(int i = 0; i < length; i++){
		if(i == length - 1)
			printf("%s\n", path[i]);
		else{
			printf("%s => ", path[i]);
		}
	}

	printf("BFS: ");
	BFS(g, "AB", "", printValue);
	printf("\n");
	printf("DFS: ");
	DFS(g, "AB", "", printValue);

	return 0;
}