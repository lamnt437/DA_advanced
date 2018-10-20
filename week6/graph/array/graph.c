#include "graph.h"

// typedef struct {
// 	int * matrix;
// 	int sizemax;
// } Graph;


Graph createGraph(int sizemax){
	Graph graph;
	int i;
	graph.matrix = (int *)malloc(sizeof(int) * sizemax);
	graph.sizemax = sizemax;

	for(i = 0; i < sizemax * sizemax; i++){
		graph.matrix[i] = 0;
	}
	return graph;
}

int *accessGraphEdgeAddress(Graph graph, int i, int j){
	int sizemax = graph.sizemax;
	return &graph.matrix[j + i * sizemax];
}
void addEdge(Graph graph, int v1, int v2){
	int *ptr = accessGraphEdgeAddress(graph, v1, v2);
	*ptr = 1;
	ptr = accessGraphEdgeAddress(graph, v2, v1);
	*ptr = 1;
}
int adjacent(Graph graph, int v1, int v2){
	int *ptr1 = accessGraphEdgeAddress(graph, v1, v2);
	int *ptr2 = accessGraphEdgeAddress(graph, v2, v1);
	if(*ptr1 == 1 || *ptr2 == 1)
		return 1;
	return 0;
}
int getAdjacentVertices(Graph graph, int vertex, int* output) // return the number of adjacent vertices.
{
	int counter = 0;
	int size = graph.sizemax;
	int i;
	int j = 0;

	for(i = 0; i < size; i++){
		int *ptr = accessGraphEdgeAddress(graph, vertex, i);
		if(*ptr){
			counter++;
			output[j++] = i;
		}
	}
	return counter;
}
void dropGraph(Graph graph){
	free(graph.matrix);
}

void printGraph(Graph graph){
	int size = graph.sizemax;
	int i, j;
	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){
			int *ptr = accessGraphEdgeAddress(graph, i, j);
			printf("%d ", *ptr);
		}
		printf("\n");
	}
}