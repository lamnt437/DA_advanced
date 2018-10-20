#ifndef _graph_h_
#define _graph_h_
#include <stdlib.h>
#include <stdio.h>

typedef struct {
	int * matrix;
	int sizemax;
} Graph;


Graph createGraph(int sizemax);
int *accessGraphEdgeAddress(Graph graph, int i, int j);
void addEdge(Graph graph, int v1, int v2);
int adjacent(Graph graph, int v1, int v2);
int getAdjacentVertices(Graph graph, int vertex, int* output); // return the number of adjacent vertices.
void dropGraph(Graph graph);
void printGraph(Graph graph);

#endif